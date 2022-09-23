#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Object.h"

class Background : public Object
{
public:
    Background(FileBase *pFile);

    virtual void save() {

    }

    quint16 mID;
    quint16 mXOffset;
    quint16 mYOffset;
    quint16 _6;
    QString mName;
    quint8 _18;
    quint8 _19;
    quint8 _1A;
    quint8 _1B;
};

#endif // BACKGROUND_H
