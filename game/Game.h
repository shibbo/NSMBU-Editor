#ifndef GAME_H
#define GAME_H

#include "io/Filesystem.h"

class Game
{
public:
    static Game* createGame(QString path) {
        if (sGame == nullptr) {
            sGame = new Game(path);
        }

        return sGame;
    }

    static Game* getGame() {
        return sGame;
    }

    Game(QString path);
    ~Game();
    SARCFilesystem* getAndDecompLevelArchive(QString path);

    ExternalFilesystem* mFilesystem;
    QString mPath;

    static Game* sGame;
};

#endif // GAME_H
