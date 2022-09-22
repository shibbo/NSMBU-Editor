#ifndef EXTERNALFILE_H
#define EXTERNALFILE_H

#include "io/FileBase.h"
#include "io/FilesystemBase.h"
#include <QTemporaryFile>

class ExternalFile : public FileBase
{
public:
    ExternalFile(FilesystemBase* fs, QString path);
    ExternalFile(FilesystemBase* fs);
    ~ExternalFile();

    void open();
    void save();
    void close();
    quint64 readData(quint8* data, quint64 len);
    quint64 writeData(quint8* data, quint64 len);
    quint64 pos() const;
    bool seek(quint64 pos);
    quint64 size() const;
    bool resize(quint64 size);

private:
    QFile* mFile;
};

#endif // EXTERNALFILE_H
