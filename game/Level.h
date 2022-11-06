#ifndef LEVEL_H
#define LEVEL_H

#include "io/SARCFilesystem.h"
#include "obj/Objects.h"
#include "Tileset.h"
#include "fmt/GTX.h"

class Level
{
public:
    Level(SARCFilesystem *pLevelFile, QString levelName, int levelArea);
    ~Level();

    enum Blocks : quint32 {
        BLOCK_TILESET       = 0,
        BLOCK_AREA          = 1,
        BLOCK_BOUNDS        = 2,
        BLOCK_UNK_3         = 3,
        BLOCK_BG            = 4,
        BLOCK_UNK_5         = 5,
        BLOCK_ENTRANCES     = 6,
        BLOCK_SPRITES       = 7,
        BLOCK_SPRITES_USED  = 8,
        BLOCK_ZONES         = 9,
        BLOCK_LOCATIONS     = 10,
        BLOCK_UNK_11        = 11,
        BLOCK_UNK_12        = 12,
        BLOCK_PATHS         = 13,
        BLOCK_PATH_NODES    = 14
    };

    enum BlockSizes : quint32 {
        BLOCK_SIZE_AREA             = 0x18,
        BLOCK_SIZE_BOUNDS           = 0x1C,
        BLOCK_SIZE_BG               = 0x1C,
        BLOCK_SIZE_ENTRANCE         = 0x18,
        BLOCK_SIZE_SPRITE           = 0x18,
        BLOCK_SIZE_SPRITES_USED     = 0x4,
        BLOCK_SIZE_ZONE             = 0x1C,
        BLOCK_SIZE_LOCATION         = 0xC,
        BLOCK_SIZE_PATH             = 0xC,
        BLOCK_SIZE_PATH_NODE        = 0x14
    };

    struct AreaSettings {
        quint32 area_events;
        quint32 zone_events;
        quint16 flags;
        quint16 time_limit;
        quint8 _C;
        quint8 _D;
        quint8 _E;
        quint8 _F;
        quint8 start_entrance;
        quint8 _11;
        quint8 _12;
        quint8 start_for_coin_boost;
        quint16 midway_time_limit;
        quint16 midway_time_limit_2;

    };

    //QString mTilesets[4];
    //QMap<QString, GTX *> mTilesetImages;
    //QMap<quint32, Tileset *> mTiles;
    Tileset* mTilesets[4];
    AreaSettings* mSettings;
    QList<ZoneBounds *> mZoneBounds;
    QList<Background *> mBackgrounds;
    QList<Entrance *> mEntrances;
    QList<Sprite *> mSprites;
    QList<quint16> mLoadedSpritesList;
    QList<Zone *> mZones;
    QList<Location *> mLocations;
    QList<Path *> mPaths;
    QList<PathPoint *> mPathPoints;
    QMap<quint8, QList<BgDatObject *>> mObjects;

private:
    SARCFilesystem* mLevelArchive;
    QString mLevelName;
    int mArea;
};

#endif // LEVEL_H
