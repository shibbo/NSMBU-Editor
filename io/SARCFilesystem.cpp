#include "SARCFilesystem.h"
#include "io/MemoryFile.h"

SARCFilesystem::SARCFilesystem(FileBase *pFile) {
    mSARC = pFile;
    pFile->open();
    pFile->seek(0);

    quint32 tag = pFile->readU32();
    qDebug("SARC Tag: %08x", tag);

    pFile->skip(8);
    mDataOffs = pFile->readU32();
    pFile->skip(4);

    mSFATOffs = (quint32)pFile->pos();
    pFile->skip(6);
    mFileCount = pFile->readU16();
    mHashMult = pFile->readU32();
    mSFNTOffs = mSFATOffs + 0xC + (mFileCount * 0x10);

    for (quint32 i = 0; i < mFileCount; i++) {
        pFile->seek(mSFATOffs + 0xC + (i * 0x10));
        InternalSARCFile* internal = new InternalSARCFile();
        internal->entry_offset = (quint32)pFile->pos();
        internal->name_hash = pFile->readU32();
        internal->name_offset = (pFile->readU32() & 0x00FFFFFF) << 2;
        internal->offset = pFile->readU32();
        internal->size = pFile->readU32() - internal->offset;
        pFile->seek(mSFNTOffs + 0x8 + internal->name_offset);
        pFile->ReadString(internal->name, 0);
        mFiles.insert(internal->name, internal);
    }

    pFile->close();
}

SARCFilesystem::~SARCFilesystem() {
    delete mSARC;
}

bool SARCFilesystem::directoryExists(QString path) {
    if (path[0] == '/') {
        path.remove(0, 1);
    }

    if (!path.endsWith("/")) {
        path.append("/");
    }

    for (int i = 0; i < mFiles.size(); i++) {
        QString curPath = mFiles.keys()[i];

        if (curPath.startsWith(path)) {
            return true;
        }
    }

    return false;
}
void SARCFilesystem::directoryContents(QString path, QDir::Filter filter, QList<QString>& out) {
    if (path[0] == '/') {
        path.remove(0, 1);
    }

    if (path != "" && !path.endsWith("/")) {
        path.append("/");
    }

    out.clear();

    for (int i = 0; i < mFiles.size(); i++) {
        QString curPath = mFiles.keys()[i];

        if (curPath.startsWith(path)) {
            curPath.remove(0, path.length());
            int slashidx = curPath.indexOf('/');
            bool isDir = (slashidx != -1);

            if ((isDir && (filter & QDir::Dirs)) || ((!isDir) && (filter & QDir::Files))) {
                if (isDir) {
                    curPath = curPath.left(slashidx);
                }

                if (!out.contains(curPath)) {
                    out.append(curPath);
                }
            }
        }
    }
}

bool SARCFilesystem::fileExists(QString path) {
    if (path[0] == '/') {
        path.remove(0, 1);
    }

    return mFiles.contains(path);
}
FileBase* SARCFilesystem::openFile(QString path) {
    if (path[0] == '/') {
        path.remove(0, 1);
    }

    if (!mFiles.contains(path)) {
        MemoryFile* ret = new MemoryFile(this);
        ret->setIdPath(path);
        return ret;
    }

    InternalSARCFile* file = mFiles[path];
    FileBase* ret = mSARC->getSubfile(this, mDataOffs + file->offset, file->size);
    ret->setIdPath(path);
    return ret;
}
bool SARCFilesystem::save(FileBase* pFile) {

}
bool SARCFilesystem::deleteFile(QString path) {

}
bool SARCFilesystem::renameFile(QString path, QString newName) {

}
bool SARCFilesystem::renameDir(QString path, QString newName) {

}
bool SARCFilesystem::changeFileDir(QString path, QString newName) {

}
