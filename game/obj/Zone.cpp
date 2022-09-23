#include "Zone.h"

Zone::Zone(FileBase *pFile) : Object(pFile) {
    mXPosition = pFile->readS16();
    mYPosition = pFile->readS16();
    mWidth = pFile->readU16();
    mHeight = pFile->readU16();
    mTheme = pFile->readU16();
    _A = pFile->readU16();
    mID = pFile->readU8();
    mBoundID = pFile->readU8();
    _E = pFile->readU8();
    mZoom = pFile->readU8();
    _10 = pFile->readU8();
    mVisibility = pFile->readU8();
    mBackgroundID = pFile->readU8();
    _13 = pFile->readU8();
    _14 = pFile->readU8();
    _15 = pFile->readU8();
    mMusicID = pFile->readU8();
    _17 = pFile->readU8();
    _18 = pFile->readU8();
    _19 = pFile->readU8();
    _1A = pFile->readU16();
}
