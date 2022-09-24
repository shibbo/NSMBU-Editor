#include "Entrance.h"

Entrance::Entrance(FileBase *pFile) : Object(pFile) {
    mXPosition = util::to64(pFile->readS16());
    mYPosition = util::to64(pFile->readS16());
    mCameraOffsetX = pFile->readS16();
    mCameraOffsetY = pFile->readS16();
    mID = pFile->readU8();
    mDestArea = pFile->readU8();
    mDestEntrance = pFile->readU8();
    mType = pFile->readU8();
    mPlayerEntrance = pFile->readU8();
    mZone = pFile->readU8();
    _E = pFile->readU8();
    mPlayerDistance = pFile->readU8();
    mFlags = pFile->readS16();
    mBabyYoshiEntrance = pFile->readU8();
    mCoinEntrance = pFile->readU8();
    mPathID = pFile->readU8();
    mPathNode = pFile->readU8();
    mTransitionType = pFile->readU8();
    _17 = pFile->readU8();

    mWidth = 64;
    mHeight = 64;
    mOffsetX = 0;
    mOffsetY = 0;
}
