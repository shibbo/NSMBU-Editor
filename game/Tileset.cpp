#include "Tileset.h"

Tileset::Tileset(SARCFilesystem *pFile, quint32 layer, quint32 area) {
    mLayer = layer;
    mArea = area;
    QString layer_file_str = QString("course/course%1_bgdatL%2.bin").arg(mArea).arg(mLayer);
    FileBase* layerFile = pFile->openFile(layer_file_str);
    layerFile->open();
    layerFile->seek(0);
    while (true) {
        quint16 type = layerFile->readU16();

        if (type == 0xFFFF) {
            return;
        }

        Tileset::Object* obj = new Tileset::Object();
        obj->mType = type;  // _0
        obj->mXPosition = layerFile->readU16();
        obj->mYPosition = layerFile->readU16();
        obj->mWidth = layerFile->readU16();
        obj->mHeight = layerFile->readU16();
        obj->mTypeOverride = layerFile->readU8();
        layerFile->skip(5);
        mObjects.append(obj);
    }

    delete layerFile;
}
