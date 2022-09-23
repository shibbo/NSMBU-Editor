#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Object.h"

class Entrance : public Object
{
public:
    Entrance(FileBase *pFile);

    virtual void save() {

    }

    qint16 mXPosition;
    qint16 mYPosition;
    qint16 mCameraOffsetX;
    qint16 mCameraOffsetY;
    quint8 mID;
    quint8 mDestArea;
    quint8 mDestEntrance;
    quint8 mType;
    quint8 mPlayerEntrance;
    quint8 mZone;
    quint8 _E;
    quint8 mPlayerDistance;
    qint16 mFlags;
    quint8 mBabyYoshiEntrance;
    quint8 mCoinEntrance;
    quint8 mPathID;
    quint8 mPathNode;
    quint8 mTransitionType;
    quint8 _17;
};

#endif // ENTRANCE_H
