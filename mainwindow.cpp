#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "io/Filesystem.h"
#include "game/Game.h"
#include "game/Level.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Game* gm = Game::createGame("D:\\Hacking\\WiiU\\NSMBU\\fs\\content\\Common");

    if (gm != nullptr) {
        SARCFilesystem* levelArch = gm->getAndDecompLevelArchive("\\course_res_pack\\1-1.szs");

        Level* lvl = new Level(new SARCFilesystem(levelArch->openFile("1-1")), "1-1", 1);
    }

    /*ExternalFilesystem* fs = new ExternalFilesystem("D:\\Hacking\\WiiU\\NSMBU\\fs\\content\\Common");

    if (fs->fileExists("/course_res_pack/1-1.szs")) {
        ExternalFile* file = new ExternalFile(nullptr, "D:\\Hacking\\WiiU\\NSMBU\\fs\\content\\Common\\course_res_pack\\1-1.szs");
        file->open();
        quint8* data = new quint8[file->size()];
        file->readData(data, file->size());

        quint32 outsize;
        quint8* decompData = Yaz0::Decompress(data, file->size(), &outsize);
        SARCFilesystem* sarc = new SARCFilesystem(new MemoryFile(fs, decompData, outsize));
        qDebug("%d", sarc->count());
        SARCFilesystem* innerSarc = new SARCFilesystem(sarc->openFile("1-1"));
    }*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

