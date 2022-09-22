#ifndef FILEBASE_H
#define FILEBASE_H

#include <QtEndian>
#include <QString>
#include "io/FilesystemBase.h"

class FileBase
{
public:
    virtual ~FileBase() {

    }

    virtual void open() = 0;
    virtual void save() = 0;
    virtual void close() = 0;
    virtual quint64 readData(quint8 *pData, quint64 dataLen) = 0;
    virtual quint64 writeData(quint8 *pData, quint64 dataLen) = 0;
    virtual quint64 pos() const = 0;
    virtual bool seek(quint64 pos) = 0;
    virtual quint64 size() const = 0;
    virtual bool resize(quint64 size) = 0;

    quint8 readU8() {
        quint8 ret;
        readData((quint8*)&ret, 1);
        return ret;
    }

    quint16 readU16() {
        quint16 ret;
        readData((quint8*)&ret, 2);
        return qToBigEndian(ret);
    }

    quint32 readU32() {
        quint32 ret;
        readData((quint8*)&ret, 4);
        return qToBigEndian(ret);
    }

    quint64 readU64() {
        quint64 ret;
        readData((quint8*)&ret, 8);
        return qToBigEndian(ret);
    }

    float readFloat() {
        quint32 bin = readU32();
        float ret;
        memcpy(&ret, &bin, 4);
        return ret;
    }

    quint32 ReadString(QString &out, quint32 len = 0) {
        QByteArray arr;
        if (len != 0) {
            for (int i = 0; i < len; i++) {
                arr.append(readU8());
            }

            out = QString(arr);
            return len;
        }

        // now we just need to find a null terminated string
        quint8 curChar;
        quint32 curIter = 0;
        while (1) {
            curChar = readU8();
            if (curChar != 0) {
                arr.append(curChar);
                curIter++;
            }
            else {
                out = QString(arr);
                return curIter;
            }
        }
    }

    void skip(qint64 num) {
        seek(pos() + num);
    }


     FileBase* getSubfile(FilesystemBase* container, quint64 offset, quint64 size);

     void setIdPath(QString path) {
         if (path[0] == '/')
             path.remove(0,1);

         if (mID.isEmpty())
             mID = path;
     }

     QString& getIdPath() {
         return mID;
     }

protected:
    FilesystemBase* mParent;
    QString mID;
    int mOpenCount;
};

#endif // FILEBASE_H
