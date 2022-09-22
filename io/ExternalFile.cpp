#include "io/Filesystem.h"

ExternalFile::ExternalFile(FilesystemBase* pFilesystem, QString path) {
    mParent = pFilesystem;
    mFile = new QFile(path);
    mOpenCount = 0;
}


ExternalFile::ExternalFile(FilesystemBase* pFilesystem) {
    mParent = pFilesystem;
    mFile = new QTemporaryFile();
}


ExternalFile::~ExternalFile() {
    delete mFile;
}

void ExternalFile::open() {
    if (mOpenCount == 0) {
        mFile->open(QIODevice::ReadWrite);
    }

    mOpenCount++;
}

void ExternalFile::save() {
    mFile->flush();

    if (mParent != nullptr) {
        mParent->save(this);
    }
}

void ExternalFile::close() {
    mOpenCount--;

    if (mOpenCount == 0) {
        mFile->close();
    }
}

quint64 ExternalFile::readData(quint8* pData, quint64 len) {
    return mFile->read((char*)pData, len);
}

quint64 ExternalFile::writeData(quint8* pData, quint64 len) {
    return mFile->write((const char*)pData, len);
}

quint64 ExternalFile::pos() const {
    return mFile->pos();
}

bool ExternalFile::seek(quint64 pos) {
    return mFile->seek(pos);
}

quint64 ExternalFile::size() const {
    return mFile->size();
}

bool ExternalFile::resize(quint64 size) {
    return mFile->resize(size);
}
