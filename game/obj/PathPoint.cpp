#include "PathPoint.h"

PathPoint::PathPoint(FileBase *pFile) : Object(pFile) {
    mXPosition = pFile->readS16();
    mYPosition = pFile->readS16();
    mSpeed = pFile->readFloat();
    mAcceleration = pFile->readFloat();
    mDelay = pFile->readU16();
    _E = pFile->readU16();
    _10 = pFile->readU8();
    _11 = pFile->readU8();
    _12 = pFile->readU8();
    _13 = pFile->readU8();
}
