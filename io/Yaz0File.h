#ifndef YAZ0FILE_H
#define YAZ0FILE_H

#include "io/FileBase.h"

class Yaz0 {
public:
    static quint8* Decompress(quint8 *pData, quint32 compSize, quint32 *pOutSize);
};

class Yaz0File : public FileBase {
public:
    Yaz0File(FilesystemBase* pFilesystem, QString file);

    quint8* mDecompressedData;
};

#endif // YAZ0FILE_H
