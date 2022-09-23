#ifndef OBJECT_H
#define OBJECT_H

#include "io/Filesystem.h"

class Object
{
public:
    Object(FileBase *pFile);

    virtual void save() = 0;
};

#endif // OBJECT_H
