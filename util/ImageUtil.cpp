#include "ImageUtil.h"

namespace Util {
    quint8 EXP5TO8R(quint16 packedcol) {
        return (((packedcol) >> 8) & 0xF8) | (((packedcol) >> 13) & 0x7);
    }

    quint8 EXP6TO8G(quint16 packedcol) {
        return (((packedcol) >> 3) & 0xfc) | (((packedcol) >>  9) & 0x03);
    }

    quint8 EXP5TO8B(quint16 packedcol) {
        return (((packedcol) << 3) & 0xf8) | (((packedcol) >>  2) & 0x07);
    }

    void dxt5_decode_imageblock(quint8 *pixdata, quint32 img_block_src, quint8 i, quint8 j, quint8* acomp, quint8* rcomp, quint8* gcomp, quint8* bcomp) {
        quint16 color0 = pixdata[img_block_src] | (pixdata[img_block_src + 1] << 8);
        quint16 color1 = pixdata[img_block_src + 2] | (pixdata[img_block_src + 3] << 8);
        quint32 bits = (pixdata[img_block_src + 4] | (pixdata[img_block_src + 5] << 8) | (pixdata[img_block_src + 6] << 16) | (pixdata[img_block_src + 7] << 24));
        quint8 bit_pos = 2 * (j * 4 + i);
        quint8 code = (bits >> bit_pos) & 3;

        *acomp = 255;
        if (code == 0) {
            *rcomp = EXP5TO8R(color0);
            *gcomp = EXP6TO8G(color0);
            *bcomp = EXP5TO8B(color0);
        }
        else if (code == 1) {
            *rcomp = EXP5TO8R(color1);
            *gcomp = EXP6TO8G(color1);
            *bcomp = EXP5TO8B(color1);
        }

        else if (code == 2) {
            *rcomp = ((EXP5TO8R(color0) * 2 + EXP5TO8R(color1)) / 3);
            *gcomp = ((EXP6TO8G(color0) * 2 + EXP6TO8G(color1)) / 3);
            *bcomp = ((EXP5TO8B(color0) * 2 + EXP5TO8B(color1)) / 3);
        }
        else if (code == 3) {
            *rcomp = ((EXP5TO8R(color0) + EXP5TO8R(color1) * 2) / 3);
            *gcomp = ((EXP6TO8G(color0) + EXP6TO8G(color1) * 2) / 3);
            *bcomp = ((EXP5TO8B(color0) + EXP5TO8B(color1) * 2) / 3);
        }
    }

    void fetch_2d_texel_rgba_dxt5(quint32 srcRowStride, quint8 *pixdata, quint32 i, quint32 j, quint8* acomp, quint8* rcomp, quint8* gcomp, quint8* bcomp) {
        quint32 blksrc = ((srcRowStride + 3) / 4 * (j / 4) + (i / 4)) * 16;
        quint8 alpha0 = pixdata[blksrc];
        quint8 alpha1 = pixdata[blksrc + 1];

        quint8 bit_pos = ((j & 3) * 4 + (i & 3)) * 3;
        quint8 acodelow = pixdata[blksrc + 2 + bit_pos / 8];
        quint8 acodehigh = pixdata[blksrc + 3 + bit_pos / 8];
        quint8 code = (acodelow >> (bit_pos & 0x7) | (acodehigh << (8 - (bit_pos & 0x7)))) & 0x7;

        quint8 _acomp, _rcomp, _gcomp, _bcomp;
        dxt5_decode_imageblock(pixdata, blksrc + 8, i & 3, j & 3, acomp, rcomp, gcomp, bcomp);

        if (code == 0) {
            *acomp = alpha0;
        }
        else if (code == 1) {
            *acomp = alpha1;
        }
        else if (alpha0 > alpha1) {
            *acomp = (alpha0 * (8 - code) + (alpha1 * (code -1))) / 7;
        }
        else if (code < 6) {
            *acomp = (alpha0 * (6 - code) + (alpha1 * (code - 1))) / 5;
        }
        else if (code == 6) {
            *acomp = 0;
        }
        else {
            *acomp = 255;
        }
    }

    quint8* decompressBC3(quint32 width, quint32 height, quint8 *pData) {
        quint8 r, g, b, a;
        quint32 y, x, pos;
        quint8* output = new quint8[width * height * 4];

        for (quint32 y = 0; y < height; y++) {
            for (quint32 x = 0; x < width; x++) {
                fetch_2d_texel_rgba_dxt5(width, pData, x, y, &a, &r, &g, &b);
                pos = (y * width + x) * 4;
                output[pos] = r;
                output[pos + 1] = g;
                output[pos + 2] = b;
                output[pos + 3] = a;
            }
        }

        return output;
    }

    quint8* deswizzleRGBA8(quint8* data, quint32 width, quint32 height) {
        quint8* ret = new quint8[width * height * 4];

        for (quint32 y = 0; y < height; y++) {
            for (quint32 x = 0; x < width; x++) {
                quint32 pos = (y & ~15) * width;
                pos ^= (x & 3);
                pos ^= ((x >> 2) & 1) << 3;
                pos ^= ((x >> 3) & 1) << 6;
                pos ^= ((x >> 3) & 1) << 7;
                pos ^= (x & ~0xF) << 4;
                pos ^= (y & 1) << 2;
                pos ^= ((y >> 1) & 7) << 4;
                pos ^= (y & 0x10) << 4;
                pos ^= (y & 0x20) << 2;
                pos *= 4;

                quint32 dest = (y * width + x) * 4;
                quint8* s = data + pos;
                *(ret + dest) = *s;
                *(ret + dest + 1) = *(s + 1);
                *(ret + dest + 2) = *(s + 2);
                *(ret + dest + 3) = *(s + 3);
            }
        }

        return ret;
    }

    quint8* deswizzleBC3(quint8* data, quint32 width, quint32 height) {
        quint32 blobWidth = width / 4;
        quint32 blobHeight = height / 4;
        quint8* ret = new quint8[width * height];

        for (quint32 y = 0; y < blobHeight; y++) {
            for (quint32 x = 0; x < blobWidth; x++) {
                quint32 pos = ((y >> 4) * (blobWidth * 16)) & 0xFFFF;
                pos ^= (y & 1);
                pos ^= (x & 7) << 1;
                pos ^= (x & 8) << 1;
                pos ^= (x & 8) << 2;
                pos ^= (x & 0x10) << 2;
                pos ^= (x & ~0x1F) << 4;
                pos ^= (y & 2) << 6;
                pos ^= (y & 4) << 6;
                pos ^= (y & 8) << 1;
                pos ^= (y & 0x10) << 2;
                pos ^= (y & 0x20);

                quint32 toPos = (y * blobWidth + x) * 16;
                pos *= 16;

                memcpy(ret + toPos, data + pos, 16);
            }
        }

        return ret;
    }
}
