#include "Game.h"

Game* Game::sGame = nullptr;

Game::Game(QString path)
{
    mPath = path;
    mFilesystem = new ExternalFilesystem(path);
}

Game::~Game() {
    delete mFilesystem;
}

SARCFilesystem* Game::getAndDecompLevelArchive(QString path) {
    ExternalFile* file = new ExternalFile(mFilesystem, mPath + path);
    file->open();
    quint8* data = new quint8[file->size()];
    file->readData(data, file->size());
    qDebug("%d %d %d %d", data[0], data[1], data[2], data[3]);
    quint32 outsize;
    quint8* decompData = Yaz0::Decompress(data, file->size(), &outsize);
    SARCFilesystem* sarc = new SARCFilesystem(new MemoryFile(mFilesystem, decompData, outsize));
    return sarc;
}
