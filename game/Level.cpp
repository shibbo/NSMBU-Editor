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

    /* Tileset Block */
    for (quint32 i = 0; i < 4; i++) {
        course->seek(blockOffs[Level::BLOCK_TILESET] + (i * 32));
        QString name;
        course->ReadString(name, 32);

        if (name.isEmpty()) {
            mTilesets[i] = "";
            continue;
        }
        else {
            mTilesets[i] = name;
        }
    }

    /* Area Block */
    course->seek(blockOffs[Level::BLOCK_AREA]);
    mSettings = new AreaSettings();
    mSettings->area_events = course->readU32();
    mSettings->zone_events = course->readU32();
    mSettings->flags = course->readU16();
    mSettings->time_limit = course->readU16();
    mSettings->_C = course->readU8();
    mSettings->_D = course->readU8();
    mSettings->_E = course->readU8();
    mSettings->_F = course->readU8();
    mSettings->start_entrance = course->readU8();
    mSettings->_11 = course->readU8();
    mSettings->_12 = course->readU8();
    mSettings->start_for_coin_boost = course->readU8();
    mSettings->midway_time_limit = course->readU16();
    mSettings->midway_time_limit_2 = course->readU16();

    /* Zone Bound Block */
    course->seek(blockOffs[Level::BLOCK_BOUNDS]);
    for (quint32 i = 0; i < blockSizes[Level::BLOCK_BOUNDS] / Level::BLOCK_SIZE_BOUNDS; i++) {
        mZoneBounds.append(new ZoneBounds(course));
    }

    /* Zone Background Block */
    course->seek(blockOffs[Level::BLOCK_BG]);
    for (quint32 i = 0; i < blockSizes[Level::BLOCK_BG] / Level::BLOCK_SIZE_BG; i++) {
        mBackgrounds.append(new Background(course));
    }

    /* Entrances Block */
    course->seek(blockOffs[Level::BLOCK_ENTRANCES]);
    for (quint32 i = 0; i < blockSizes[Level::BLOCK_ENTRANCES] / Level::BLOCK_SIZE_ENTRANCE; i++) {
        mEntrances.append(new Entrance(course));
    }

    /* Sprites Block */
    course->seek(blockOffs[Level::BLOCK_SPRITES]);
    for (quint32 i = 0; i < blockSizes[Level::BLOCK_SPRITES] / Level::BLOCK_SIZE_SPRITE; i++) {
        mSprites.append(new Sprite(course));
    }

    /* Sprites Used Block */
    course->seek(blockOffs[Level::BLOCK_SPRITES_USED]);
    for (quint32 i = 0; i < blockSizes[Level::BLOCK_SPRITES_USED] / Level::BLOCK_SIZE_SPRITES_USED; i++) {
        mLoadedSpritesList.append(course->readU16());
        course->skip(2);
    }

    /* Zones Block */
    course->seek(blockOffs[Level::BLOCK_ZONES]);
    for (quint32 i = 0; i < blockSizes[Level::BLOCK_ZONES] / Level::BLOCK_SIZE_ZONE; i++) {
        mZones.append(new Zone(course));
    }

    /* Locations Block */
    course->seek(blockOffs[Level::BLOCK_LOCATIONS]);
    for (quint32 i = 0; i < blockSizes[Level::BLOCK_LOCATIONS] / Level::BLOCK_SIZE_LOCATION; i++) {
        mLocations.append(new Location(course));
    }

    course->seek(blockOffs[Level::BLOCK_PATHS]);
    for (quint32 i = 0; i < blockSizes[Level::BLOCK_PATHS] / Level::BLOCK_SIZE_PATH; i++) {
        mPaths.append(new Path(course));
    }

    course->seek(blockOffs[Level::BLOCK_PATH_NODES]);
    for (quint32 i = 0; i < blockSizes[Level::BLOCK_PATH_NODES] / Level::BLOCK_SIZE_PATH_NODE; i++) {
        mPathPoints.append(new PathPoint(course));
    }

    for (quint32 i = 0; i < 3; i++) {
        QString layer_file = QString("course/course%1_bgdatL%2.bin").arg(mArea).arg(i);

        if (pLevelFile->fileExists(layer_file)) {
            FileBase* layer = pLevelFile->openFile(layer_file);
            layer->open();
            layer->seek(0);
            mTiles.insert(i, new Tileset(layer));
            delete layer;
        }
    }

    course->close();
    delete course;
}

Level::~Level() {
    delete mSettings;

    for (ZoneBounds* bound : mZoneBounds) {
        delete bound;
    }

    for (Background* bg : mBackgrounds) {
        delete bg;
    }

    for (Entrance* en : mEntrances) {
        delete en;
    }

    for (Sprite* spr : mSprites) {
        delete spr;
    }

    for (Zone* z : mZones) {
        delete z;
    }

    for (Location* loc : mLocations) {
        delete loc;
    }

    for (Path* path : mPaths) {
        delete path;
    }

    for (PathPoint* pp : mPathPoints) {
        delete pp;
    }
}
