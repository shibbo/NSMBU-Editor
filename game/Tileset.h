#ifndef TILESET_H
#define TILESET_H

#include "io/Filesystem.h"

class Tileset
{
public:
    Tileset(SARCFilesystem *pFile, quint32 layer, quint32 area);

    struct Object {
        quint16 mType;
        quint16 mXPosition;
        quint16 mYPosition;
        quint16 mWidth;
        quint16 mHeight;
        quint8 mTypeOverride;
        quint8 _B;
        quint32 _C;
    };

    QList<Object *> mObjects;
    quint32 mLayer;
    quint32 mArea;
};

#endif // TILESET_H
