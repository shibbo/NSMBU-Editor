#ifndef EXTERNALFILESYSTEM_H
#define EXTERNALFILESYSTEM_H

#include "io/FilesystemBase.h"

class ExternalFilesystem : public FilesystemBase
{
public:
    ExternalFilesystem(QString base);
    ~ExternalFilesystem();

    bool directoryExists(QString path);
    void directoryContents(QString path, QDir::Filter filter, QList<QString>& out);

    bool fileExists(QString path);
    FileBase* openFile(QString path);
    bool save(FileBase* file);
    bool deleteFile(QString path);
    bool renameFile(QString path, QString newName);
    bool renameDir(QString path, QString newName);

    bool copyFile(QString path, QString newPath);

private:
    QString mBasePath;
};

#endif // EXTERNALFILESYSTEM_H
