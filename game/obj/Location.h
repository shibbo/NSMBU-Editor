#ifndef LOCATION_H
#define LOCATION_H

#include "Object.h"

class Location : public Object {
public:
    Location(FileBase *pFile);

    virtual void save() {

    }

    quint8 getID() const {
        return mID;
    }

    quint8 mID;
};

#endif // LOCATION_H
