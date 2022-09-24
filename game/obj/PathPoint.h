#ifndef PATHPOINT_H
#define PATHPOINT_H

#include "Object.h"

class PathPoint {
public:
    PathPoint(FileBase *pFile);

    virtual void save() {

    }

    qint16 mXPosition;
    qint16 mYPosition;
    float mSpeed;
    float mAcceleration;
    quint16 mDelay;
    quint16 _E;
    quint8 _10;
    quint8 _11;
    quint8 _12;
    quint8 _13;
};

#endif // PATHPOINT_H
