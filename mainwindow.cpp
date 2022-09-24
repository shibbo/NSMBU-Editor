#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "io/Filesystem.h"
#include "game/Game.h"
#include "game/Level.h"

MainWindow::MainWindow(WindowBase *parent) : WindowBase(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    Game* gm = Game::createGame("D:\\Hacking\\WiiU\\NSMBU\\fs\\content\\Common");

    if (gm != nullptr) {
        SARCFilesystem* levelArch = gm->getAndDecompLevelArchive("\\course_res_pack\\1-1.szs");
        mLevel = new Level(new SARCFilesystem(levelArch->openFile("1-1")), "1-1", 1);
        mLevelView = new LevelView(this, mLevel);
        ui->levelViewArea->setWidget(mLevelView);
        mLevelView->setMinimumSize(4096 * 64, 4096 * 64);
        mLevelView->setMaximumSize(4096 * 64, 4096 * 64);

        Zone* z = mLevel->mZones.at(0);
        mLevelView->screenshot(QRect(z->getX(), z->getY(), z->getW(), z->getH()));
        qDebug("screenshot done");
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

