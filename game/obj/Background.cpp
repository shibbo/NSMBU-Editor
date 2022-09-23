#include "Background.h"

Background::Background(FileBase *pFile) : Object(pFile) {
    mID = pFile->readU16();
    mXOffset = pFile->readS16();
    mYOffset = pFile->readS16();
    _6 = pFile->readS16();
    pFile->ReadString(mName, 16);
    _18 = pFile->readU8();
    _19 = pFile->readU8();
    _1A = pFile->readU8();
    _1B = pFile->readU8();
}
