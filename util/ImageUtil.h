#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H

#include <QString>
#include "fmt/GTX.h"

namespace Util {
    quint8* deswizzleRGBA8(quint8* data, quint32 width, quint32 height);
    quint8* deswizzleBC3(quint8* data, quint32 width, quint32 height);

    quint8* decompressBC3(quint32 width, quint32 height, quint8 *pData);
};

#endif // IMAGEUTIL_H
