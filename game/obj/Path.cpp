#include "Path.h"

Path::Path(FileBase *pFile) {
    mID = pFile->readU8();
    _1 = pFile->readU8();
    mStartNode = pFile->readU16();
    mNodeCount = pFile->readU16();
    mLoopFlag = pFile->readU16();
    _8 = pFile->readU32();
}
