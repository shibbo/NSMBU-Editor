#ifndef OBJECT_H
#define OBJECT_H

#include "io/Filesystem.h"
#include "util/units.h"

class Object
{
public:
    Object(FileBase *pFile);

    virtual void save() = 0;

    qint32 getX() const {
        return mXPosition;
    }

    qint32 getY() const {
        return mYPosition;
    }

    qint32 getW() const {
        return mWidth;
    }

    qint32 getH() const {
        return mHeight;
    }

    qint32 getOffsX() const {
        return mOffsetX;
    }

    qint32 getOffsY() const {
        return mOffsetY;
    }

    qint32 mXPosition;
    qint32 mYPosition;
    qint32 mWidth;
    qint32 mHeight;
    qint32 mOffsetX;
    qint32 mOffsetY;
};

#endif // OBJECT_H
