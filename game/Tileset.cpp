#include "Tileset.h"

Tileset::Tileset(FileBase *pFile)
{
    while (true) {
        quint16 type = pFile->readU16();

        if (type == 0xFFFF) {
            return;
        }

        Tileset::Object* obj = new Tileset::Object();
        obj->mType = type;  // _0
        obj->mXPosition = pFile->readU16();
        obj->mYPosition = pFile->readU16();
        obj->mWidth = pFile->readU16();
        obj->mHeight = pFile->readU16();
        obj->mTypeOverride = pFile->readU8();
        pFile->skip(5);
        mObjects.append(obj);
    }
}
