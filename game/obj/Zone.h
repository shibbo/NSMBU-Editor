#ifndef ZONE_H
#define ZONE_H

#include "Object.h"

class Zone : public Object {
public:
    Zone(FileBase *pFile);

    virtual void save() {

    }

    qint16 mXPosition;
    qint16 mYPosition;
    quint16 mWidth;
    quint16 mHeight;
    quint16 mTheme;
    quint16 _A;
    quint8 mID;
    quint8 mBoundID;
    quint8 _E;
    quint8 mZoom;
    quint8 _10;
    quint8 mVisibility;
    quint8 mBackgroundID;
    quint8 _13;
    quint8 _14;
    quint8 _15;
    quint8 mMusicID;
    quint8 _17;
    quint8 _18;
    quint8 _19;
    quint16 _1A;
};

#endif // ZONE_H
