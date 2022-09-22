#include "io/Filesystem.h"

#include <QtEndian>

MemoryFile::MemoryFile(FilesystemBase *pFilesystem, quint8 *pDataBlob, quint32 size) {
    mParent = pFilesystem;
    mData = pDataBlob;
    mSize = size;
    mOpenCount = 0;
}

MemoryFile::MemoryFile(FilesystemBase *pFilesystem, quint32 size) {
    mParent = pFilesystem;
    mData = new quint8[size];
    memset(mData, 0, size);
    mSize = size;
    mPos = 0;
    mOpenCount = 0;
}

MemoryFile::~MemoryFile() {
    delete[] mData;
}

void MemoryFile::open() {
    mOpenCount++;
}

void MemoryFile::save() {
    if (mParent != nullptr) {
        mParent->save(this);
    }
}

void MemoryFile::close() {
    mOpenCount--;
}

quint64 MemoryFile::readData(quint8 *pData, quint64 dataLen) {
    if ((mPos + dataLen) > mSize) {
        dataLen = mSize - mPos;
    }

    if (dataLen < 1 || dataLen > 0xFFFFFFFF) {
        return 0;
    }

    switch (dataLen) {
        case 1:
            // 8-bit
            *pData = mData[mPos];
            break;
        case 2:
            // 16-bit
            *(quint16*)pData = qFromLittleEndian(*(quint16*)&mData[mPos]);
            break;
        case 4:
            // 32-bit
            *(quint32*)pData = qFromLittleEndian(*(quint32*)&mData[mPos]);
            break;
        case 8:
            // 64-bit
            *(quint64*)pData = qFromLittleEndian(*(quint64*)&mData[mPos]);
            break;
    default:
            memcpy(pData, &mData[mPos], dataLen);
            break;
    }

    mPos += dataLen;
    return dataLen;
}

quint64 MemoryFile::writeData(quint8* pData, quint64 len)
{
    if ((mPos + len) > mSize) {
        resize(mPos + len);
    }

    if (len < 1 || len > 0xFFFFFFFF) {
        return 0;
    }

    /* no need to swap data here. it is already in big endian */
    switch (len)
    {
        case 1:
            // 8-bit
            mData[mPos] = *pData;
            break;
        case 2:
            // 16-bit
            *(quint16*)&mData[mPos] = *(quint16*)pData;
            break;
        case 4:
            // 32-bit
            *(quint32*)&mData[mPos] = *(quint32*)pData;
            break;
        case 8:
            // 64-bit
            *(quint64*)&mData[mPos] = *(quint64*)pData;
            break;
        default:
            memcpy(&mData[mPos], pData, len);
            break;
    }

    mPos += len;
    return len;
}

quint64 MemoryFile::pos() const {
    return mPos;
}

bool MemoryFile::seek(quint64 pos) {
    mPos = pos;
    return true;
}

quint64 MemoryFile::size() const {
    return mSize;
}

bool MemoryFile::resize(quint64 size) {
    if (size == 0) {
        delete[] mData;
        mData = nullptr;
        mSize = 0;
    }

    if (size < 1 || size > 0xFFFFFFFF)
        return false;

    quint8* newdata = new quint8[size];
    if (size >= mSize)  {
        memcpy(newdata, mData, mSize);
    }
    else {
        memcpy(newdata, mData, size);
    }

    delete[] mData;
    mData = newdata;
    mSize = size;

    return true;
}
