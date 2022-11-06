#include "Tileset.h"

Tileset::Tileset(SARCFilesystem *pFilesystem, QString name) {
    mFilesystem = pFilesystem;
    mTilesetName = name;

    QString tileset_graphics_path = QString("BG_tex/%1.gtx").arg(name);
    mImageData = new GTX(mFilesystem->openFile(tileset_graphics_path), name);
    mTilesetImage = QImage(mImageData->mDecodedData, mImageData->getWidth(), mImageData->getHeight(), QImage::Format::Format_RGB888);

    FileBase* index_file = mFilesystem->openFile("/BG_unt/" + name + "_hd.bin");
    index_file->open();
    index_file->seek(0);

    FileBase* data_file = mFilesystem->openFile("/BG_unt/" + name + ".bin");
    data_file->open();
    data_file->seek(0);

    qint32 obj_count = index_file->size() / 6;

    for (quint32 o = 0; o < obj_count; o++) {
        quint16 offs = index_file->readU16();
        quint8 w = index_file->readU8();
        quint8 h = index_file->readU8();
        quint16 rand = index_file->readU16();

        ObjectDef* def = new ObjectDef(w, h, rand);

        def->mYRepeatStart = 0xFF;
        def->mSlopeY = def->mHeight;

        quint8 b;
        data_file->seek(offs);
        qint32 cur_x = 0, cur_y = 0;

        ObjectRow* row = new ObjectRow();
        row->mSlopeFlags = 0;
        row->mXRepeatStart = 0xFF;

        bool x_repeat = false;
        int unk = 0;
        bool y_repeat = false;

        for (;;) {
            b = data_file->readU8();

            if (b == 0xFF) {
                delete row;
                break;
            }

            if (b == 0xFE) {
                def->mRows.append(*row);
                row = new ObjectRow();
                row->mSlopeFlags = 0;
                row->mXRepeatStart = 0xFF;
                x_repeat = false;
                unk = 0;

                cur_x = 0;
                cur_y++;
                continue;
            }

            if (b & 0x80) {
                if (b == 0x84) {
                    def->mSlopeY = cur_y;
                }

                row->mSlopeFlags = b;
                b = data_file->readU8();
            }

            if (b & 0x4) {
                if (unk == 2) {
                    unk = 3;
                    row->mXRepeatEnd = cur_x;
                }
                else if (!unk) {
                    unk = 1;
                }
            }
            else if (unk == 1) {
                unk = 2;
                row->mXRepeatStart = cur_x;
                row->mXRepeatEnd = w;
            }

            if ((b & 0x1) && !x_repeat) {
                x_repeat = false;
                row->mXRepeatEnd = cur_x;
            }

            if (cur_x == 0) {
                if ((b & 0x2) && !y_repeat) {
                    y_repeat = true;
                    def->mYRepeatStart = cur_y;
                    def->mYRepeatEnd = h;
                }
                else if ((!(b & 0x2)) && y_repeat) {
                    y_repeat = false;
                    def->mYRepeatEnd = cur_y;
                }
            }

            row->mData.append(b);
            b = data_file->readU8();
            row->mData.append(b);
            b = data_file->readU8();
            row->mData.append(b);
            cur_x++;
        }

        mObjectDefs.append(def);

    }

    data_file->close();
    delete data_file;

    index_file->close();
    delete index_file;
}

void Tileset::drawTile(QPainter &rPainter, TileGrid &rGrid, int num, int x, int y, float zoom, int item) {
    quint32 gridid = x | (y << 16);

    if (rGrid[gridid] == rGrid[0xFFFFFFFF]) {
        return;
    }

    int tsize = (int)(64 * zoom);
    x *= tsize;
    y *= tsize;

    QRect rdst(x, y, tsize, tsize);
    QRect rsrc(2 + ((num % 32) * 64), 2 + ((num / 32) * 64), 60, 60);
    rPainter.drawImage(rdst, mTilesetImage, rsrc);

    rGrid[gridid] = rGrid[0xFFFFFFFF];
}

void Tileset::drawRow(QPainter &rPainter, TileGrid &rGrid, ObjectDef &rDef, ObjectRow &rRow, int x, int y, int w, float zoom) {
    int sx = 0, dx = 0;
    int end = rRow.mData.length() / 3;

    if (rRow.mXRepeatStart != 0xFF) {
        int rstart = rRow.mXRepeatStart;
        int rend = w - (rDef.mWidth - rRow.mXRepeatEnd);

        sx = 0;
        while (dx < rstart) {
            if (rRow.mData[sx * 3 + 1] || (rRow.mData[sx * 3 + 2] & 0x6) >> 1) {
                drawTile(rPainter, rGrid, rRow.mData[sx * 3 + 1], x + dx, y, zoom, (rRow.mData[sx * 3 + 2] & 120) >> 3);
            }

            dx++;
            sx++;

            if (sx > rRow.mXRepeatStart) {
                sx = 0;
            }
        }

        sx = rRow.mXRepeatStart;

        while (dx < rend) {
            if (rRow.mData[sx * 3 + 1] || (rRow.mData[sx * 3 + 2] & 6) >> 1) {
                drawTile(rPainter, rGrid, rRow.mData[sx*3 + 1], x+dx, y, zoom, (rRow.mData[sx*3 + 2] & 120) >> 3);
            }

            dx++;
            sx++;

            if (sx >= rRow.mXRepeatEnd) {
                sx = rRow.mXRepeatStart;
            }
        }

        sx = rRow.mXRepeatEnd;
        while (dx < w)
        {
            if (rRow.mData[sx*3 + 1] || (rRow.mData[sx*3 + 2] & 6) >> 1) {
                drawTile(rPainter, rGrid, rRow.mData[sx*3 + 1], x+dx, y, zoom, (rRow.mData[sx*3 + 2] & 120) >> 3);
            }

            dx++;
            sx++;
            if (sx >= end)
                sx = rRow.mXRepeatEnd;
        }
    }
}

BgDatObject::BgDatObject(quint16 type, quint16 x, quint16 y, quint16 w, quint16 h, quint16 typeovr, quint8 layer) {
    mLayer = layer;
    mType = type;
    mXPosition = x;
    mYPosition = y;
    mWidth = w;
    mHeight = h;
    mTypeOverride = typeovr;
}

ObjectDef::ObjectDef(quint8 width, quint8 height, quint16 rand) {
    mWidth = width;
    mHeight = height;
    mRand = rand;
}
