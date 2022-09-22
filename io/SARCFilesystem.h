#ifndef SARCFILESYSTEM_H
#define SARCFILESYSTEM_H

#include "io/FileBase.h"
#include "io/FilesystemBase.h"

class SARCFilesystem : public FilesystemBase
{
public:
    SARCFilesystem(FileBase *pFile);
    virtual ~SARCFilesystem();

    bool directoryExists(QString path);
    void directoryContents(QString path, QDir::Filter filter, QList<QString>& out);
    bool fileExists(QString path);
    FileBase* openFile(QString path);
    bool save(FileBase* pFile);
    bool deleteFile(QString path);
    bool renameFile(QString path, QString newName);
    bool renameDir(QString path, QString newName);
    bool changeFileDir(QString path, QString newName);

    bool copyFile(QString path, QString newPath) {
        return false;
    }

    quint32 count() const {
        return mFileCount;
    }

    void repack();
    quint32 hash(QString &rName);

private:
    struct InternalSARCFile {
        QString name;
        quint32 offset;
        quint32 size;
        quint32 name_offset;
        quint32 name_hash;
        quint32 entry_offset;
    };

    static quint32 align(quint32 v, quint32 a) {
        return (v + a - 1) / a * a;
    }

    static bool hashSort(InternalSARCFile *pFile1, InternalSARCFile *pFile2) {
        return pFile1->name_hash < pFile2->name_hash;
    }

    FileBase* mSARC;
    quint32 mFileCount;
    quint32 mHashMult;
    quint32 mSFATOffs;
    quint32 mSFNTOffs;
    quint32 mDataOffs;
    QHash<QString, InternalSARCFile *> mFiles;
};

#endif // SARCFILESYSTEM_H
