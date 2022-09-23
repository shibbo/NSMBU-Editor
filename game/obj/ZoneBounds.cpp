#include "ZoneBounds.h"

ZoneBounds::ZoneBounds(FileBase *pFile) : Object(pFile) {
    mYUpper = pFile->readS32();
    mYLower = pFile->readS32();
    mYUpper_2 = pFile->readS32();
    mYLower_2 = pFile->readS32();
    _12 = pFile->readU16();
    _14 = pFile->readU64();
}
