#include "Location.h"

Location::Location(FileBase *pFile) : Object(pFile) {
    mXPosition = util::to64(pFile->readS16());
    mYPosition = util::to64(pFile->readS16());
    mWidth = util::to64(pFile->readU16());
    mHeight = util::to64(pFile->readU16());
    mID = pFile->readU8();
    pFile->skip(3);
}
