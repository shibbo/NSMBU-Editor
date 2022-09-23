#include "Location.h"

Location::Location(FileBase *pFile) : Object(pFile) {
    mXPosition = pFile->readS16();
    mYPosition = pFile->readS16();
    mWidth = pFile->readU16();
    mHeight = pFile->readU16();
    mID = pFile->readU8();
    pFile->skip(3);
}
