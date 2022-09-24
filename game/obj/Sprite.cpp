#include "Sprite.h"

Sprite::Sprite(FileBase *pFile) : Object(pFile) {
    mSpriteID = pFile->readU16();
    mXPosition = util::to64(pFile->readS16());
    mYPosition = util::to64(pFile->readS16());
    mEventID = pFile->readU16();
    mSettings = pFile->readU64();
    mZoneID = pFile->readU8();
    mLayer = pFile->readU8();
    mLinkID = pFile->readU8();
    mMovementID = pFile->readU8();
    mInitialState = pFile->readU8();
    _15 = pFile->readU8();
    _16 = pFile->readU8();
    _17 = pFile->readU8();

    mOffsetX = 0;
    mOffsetY = 0;
    mHeight = 64;
    mWidth = 64;
}
