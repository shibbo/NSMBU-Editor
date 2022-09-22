#ifndef FILESYSTEMBASE_H
#define FILESYSTEMBASE_H

#include <QString>
#include <QDir>

class FileBase;

class FilesystemBase {
public:
    virtual ~FilesystemBase() {

    }

    virtual bool directoryExists(QString path) = 0;
    virtual void directoryContents(QString path, QDir::Filter filter, QList<QString> &rOut) = 0;
    virtual bool fileExists(QString path) = 0;
    virtual FileBase* openFile(QString path) = 0;
    virtual bool save(FileBase *pFile) = 0;
    virtual bool deleteFile(QString path) = 0;
    virtual bool renameFile(QString path, QString newName) = 0;
    virtual bool renameDir(QString path, QString newName) = 0;
    virtual bool copyFile(QString path, QString newPath) = 0;
};

#endif // FILESYSTEMBASE_H
