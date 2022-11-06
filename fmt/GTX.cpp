#include "GTX.h"
#include "util/ImageUtil.h"

#include <QImage>

GTX::GTX(FileBase *pFile, QString name) {
    mName = name;
    mSurfaceInfo = nullptr;
    pFile->open();
    pFile->seek(0);

    QString magic;
    pFile->ReadString(magic, 4);

    if (magic != "Gfx2") {
        qDebug("invalid GTX header");
        return;
    }

    if (pFile->readU32() != 0x20) {
        qDebug("invalid header size");
        return;
    }

    // nsmbu uses version 7.x so we can just ignore the rest of the header
    pFile->skip(0x18);

    // now we loop through our data blocks
    while (true) {
        Block* blk = new Block(pFile);
        mBlocks.append(blk);

        if (blk->mBlockType == 0x1) {
            break;
        }
    }

    // post process our blocks
    for (Block* block : mBlocks) {
        // block type 0xB contains surface info for our texture
        if (block->mBlockType == 0xB) {
            MemoryFile* f = new MemoryFile(NULL, block->mRawData, 0x9C);
            f->open();
            f->seek(0);
            mSurfaceInfo = new SurfaceInfo(f);
        }

        if (block->mBlockType == 0xC) {
            if (mSurfaceInfo->mFormat == 0x1A) {
                mDecodedData = Util::deswizzleRGBA8(block->mRawData, mSurfaceInfo->mWidth, mSurfaceInfo->mHeight);
            }
            else if (mSurfaceInfo->mFormat == 0x33) {
                quint8* deswizz = Util::deswizzleBC3(block->mRawData, mSurfaceInfo->mWidth, mSurfaceInfo->mHeight);
                mDecodedData = Util::decompressBC3(mSurfaceInfo->mWidth, mSurfaceInfo->mHeight, deswizz);
            }
        }
    }
}

GTX::Block::Block(FileBase *pFile) {
    QString magic;
    pFile->ReadString(magic, 4);

    if (magic != "BLK{") {
        qDebug("oops...not a block");
        return;
    }

    pFile->skip(0xC);
    mBlockType = pFile->readU32();
    mDataSize = pFile->readU32();

    if (mBlockType == 0xB && mDataSize != 0x9C) {
        qDebug("block was 0xB but size wasn't 0x9C, panic");
        return;
    }

    mID = pFile->readU32();
    mIdx = pFile->readU32();
    mRawData = new quint8[mDataSize];
    //memset(mRawData, 0, mDataSize);
    pFile->readData(mRawData, mDataSize);
}

SurfaceInfo::SurfaceInfo(FileBase *pFile) {
    mDim = pFile->readU32();
    mWidth = pFile->readU32();
    mHeight = pFile->readU32();
    mDepth = pFile->readU32();
    mMipMapNum = pFile->readU32();
    mFormat = pFile->readU32();
    mAAMode = pFile->readU32();
    mUsage = pFile->readU32();
    mLength = pFile->readU32();
    mDataPtr = pFile->readU32();
    mMipMapDataLen = pFile->readU32();
    mMipMapPtr = pFile->readU32();
    mTileMode = pFile->readU32();
    mSwizzle = pFile->readU32();
    mAlign = pFile->readU32();
    mPitch = pFile->readU32();

    for (quint32 i = 0; i < 0xD; i++) {
        mMipMapOffs[i] = pFile->readU32();
    }

    mFirstMipID = pFile->readU32();
    mNumAvailMips = pFile->readU32();
    mFirstSliceID = pFile->readU32();
    mNumAvailSlices = pFile->readU32();

    for (quint32 i = 0; i < 5; i++) {
        mCompSel[i] = pFile->readU8();
    }

    for (quint32 i = 0; i < 6; i++) {
        mRegs[i] = pFile->readU32();
    }
}
