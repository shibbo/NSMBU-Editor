#ifndef GTX_H
#define GTX_H

#include "io/Filesystem.h"

class SurfaceInfo {
public:
    SurfaceInfo(FileBase *pFile);

    quint32 mDim;
    quint32 mWidth;
    quint32 mHeight;
    quint32 mDepth;
    quint32 mMipMapNum;
    quint32 mFormat;
    quint32 mAAMode;
    quint32 mUsage;
    quint32 mLength;
    quint32 mDataPtr;
    quint32 mMipMapDataLen;
    quint32 mMipMapPtr;
    quint32 mTileMode;
    quint32 mSwizzle;
    quint32 mAlign;
    quint32 mPitch;
    quint32 mMipMapOffs[0xD];
    quint32 mFirstMipID;
    quint32 mNumAvailMips;
    quint32 mFirstSliceID;
    quint32 mNumAvailSlices;
    quint8 mCompSel[4];
    quint32 mRegs[5];
};


class GTX
{
public:
    GTX(FileBase *pFile, QString name);

    class Block {
    public:
        Block(FileBase *pFile);

        quint32 mBlockType;
        quint32 mDataSize;
        quint32 mID;
        quint32 mIdx;
        quint8* mRawData;
    };

    QList<Block *> mBlocks;
    SurfaceInfo* mSurfaceInfo;
    quint8* mDecodedData;
    QString mName;

    quint32 getWidth() const {
        return mSurfaceInfo->mWidth;
    }

    quint32 getHeight() const {
        return mSurfaceInfo->mHeight;
    }
};

#endif // GTX_H
