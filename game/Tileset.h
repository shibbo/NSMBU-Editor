#ifndef TILESET_H
#define TILESET_H

#include "io/Filesystem.h"

class Tileset
{
public:
    Tileset(FileBase *pFile);

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
};

#endif // TILESET_H
