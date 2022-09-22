#ifndef MEMORYFILE_H
#define MEMORYFILE_H

#include "io/FileBase.h"

class MemoryFile : public FileBase
{
public:
    MemoryFile(FilesystemBase *pFilesystem, quint8* blob, quint32 size);
    MemoryFile(FilesystemBase *pFilesystem, quint32 size=0);
    ~MemoryFile();

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
    quint8* mData;
    quint32 mSize;
    quint32 mPos;
};

#endif // MEMORYFILE_H
