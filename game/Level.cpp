#include "Level.h"

Level::Level(SARCFilesystem *pLevelFile, QString levelName, int levelArea)
{
    mLevelArchive = pLevelFile;
    mLevelName = levelName;
    mArea = levelArea;

    QString level_file = QString("course/course%1.bin").arg(mArea);
    FileBase* course = pLevelFile->openFile(level_file);
    course->open();
    course->seek(0);

    quint32 blockOffs[15];
    quint32 blockSizes[15];

    for (quint32 i = 0; i < 15; i++) {
        blockOffs[i] = course->readU32();
        blockSizes[i] = course->readU32();
    }
}
