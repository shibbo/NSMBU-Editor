#ifndef TILESET_H
#define TILESET_H

#include <QImage>
#include <QPainter>

#include "io/Filesystem.h"
#include "fmt/GTX.h"

typedef QHash<quint32,quint8> TileGrid;

struct ObjectRow {
    quint8 mSlopeFlags;
    quint8 mXRepeatStart;
    quint8 mXRepeatEnd;
    QList<quint8> mData;

};

class ObjectDef {
public:

    ObjectDef(quint8 width, quint8 height, quint16 rand);
    quint8 mWidth;
    quint8 mHeight;
    quint16 mRand;

    quint8 mSlopeY;
    quint8 mYRepeatStart;
    quint8 mYRepeatEnd;

    QList<ObjectRow> mRows;
};


class Tileset
{
public:
    Tileset(SARCFilesystem* pFilesystem, QString name);

    void drawTile(QPainter &rPainter, TileGrid &rGrid, int num, int x, int y, float zoom, int item);
    void drawRow(QPainter &rPainter, TileGrid &rGrid, ObjectDef &rDef, ObjectRow &rRow, int x, int y, int w, float zoom);

    SARCFilesystem* mFilesystem;
    QString mTilesetName;
    GTX* mImageData;
    QImage mTilesetImage;
    QList<ObjectDef *> mObjectDefs;
};

class BgDatObject {
public:
    BgDatObject(quint16 type, quint16 x, quint16 y, quint16 w, quint16 h, quint16 typeovr, quint8 layer);

    quint8 mLayer;
    quint16 mType;
    quint16 mXPosition;
    quint16 mYPosition;
    quint16 mWidth;
    quint16 mHeight;
    quint8 mTypeOverride;
    quint8 _B;
    quint32 _C;
};

#endif // TILESET_H
