#ifndef PATH_H
#define PATH_H

#include "Object.h"

class Path : public Object {
public:
    Path(FileBase *pFile);

    virtual void save() {

    }

    quint8 mID;
    quint8 _1;
    quint16 mStartNode;
    quint16 mNodeCount;
    quint16 mLoopFlag;
    quint32 _8;
};

#endif // PATH_H
