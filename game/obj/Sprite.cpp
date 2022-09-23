#include "Sprite.h"

Sprite::Sprite(FileBase *pFile) : Object(pFile) {
    mSpriteID = pFile->readU16();
    mXPosition = pFile->readS16();
    mYPosition = pFile->readS16();
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
}
