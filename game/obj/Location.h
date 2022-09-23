#ifndef LOCATION_H
#define LOCATION_H

#include "Object.h"

class Location : public Object {
public:
    Location(FileBase *pFile);

    virtual void save() {

    }

    qint16 mXPosition;
    qint16 mYPosition;
    quint16 mWidth;
    quint16 mHeight;
    quint8 mID;
};

#endif // LOCATION_H
