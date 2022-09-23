#ifndef ZONEBOUNDS_H
#define ZONEBOUNDS_H

#include "Object.h"

class ZoneBounds : public Object
{
public:
    ZoneBounds(FileBase *pFile);

    virtual void save() {

    }

    qint32 mYUpper;
    qint32 mYLower;
    qint32 mYUpper_2;
    qint32 mYLower_2;
    quint16 _12;
    quint64 _14;
};

#endif // ZONEBOUNDS_H
