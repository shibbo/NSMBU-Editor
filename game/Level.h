#ifndef LEVEL_H
#define LEVEL_H

#include "io/SARCFilesystem.h"

class Level
{
public:
    Level(SARCFilesystem *pLevelFile, QString levelName, int levelArea);

private:
    SARCFilesystem* mLevelArchive;
    QString mLevelName;
    int mArea;
};

#endif // LEVEL_H
