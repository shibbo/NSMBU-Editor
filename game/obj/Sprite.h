#ifndef SPRITE_H
#define SPRITE_H

#include "Object.h"

class Sprite : public Object
{
public:
    Sprite(FileBase *pFile);

    virtual void save() {

    }

    quint16 mSpriteID;
    qint16 mXPosition;
    qint16 mYPosition;
    quint16 mEventID;
    quint64 mSettings;
    quint8 mZoneID;
    quint8 mLayer;
    quint8 mLinkID;
    quint8 mMovementID;
    quint8 mInitialState;
    quint8 _15; // probably padding for alignment
    quint8 _16;
    quint8 _17;
};

#endif // SPRITE_H
