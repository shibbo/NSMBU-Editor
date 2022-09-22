#include "Yaz0File.h"

quint8* Yaz0::Decompress(quint8 *pData, quint32 compSize, quint32 *pOutSize) {
    if (pData[0] != 'Y' || pData[1] != 'a' || pData[2] != 'z' || pData[3] != '0') {
        *pOutSize = 0;
        return nullptr;
    }

    int fullsize = (pData[4] << 24) | (pData[5] << 16) | (pData[6] << 8) | pData[7];
    *pOutSize = fullsize;
    quint8* out = new quint8[fullsize];

    int inpos = 16, outpos = 0;
    while (outpos < fullsize)
    {
       quint8 block  = pData[inpos++];

       for (int i = 0; i < 8; i++)
       {
           if ((block & 0x80) != 0) {
               // copy one plain byte
               out[outpos++] = pData[inpos++];
           }
           else {
               // copy N compressed bytes
               quint8 b1 = pData[inpos++];
               quint8 b2 = pData[inpos++];

               int dist = ((b1 & 0xF) << 8) | b2;
               int copysrc = outpos - (dist + 1);

               int nbytes = b1 >> 4;
               if (nbytes == 0) nbytes = pData[inpos++] + 0x12;
               else nbytes += 2;

               for (int j = 0; j < nbytes; j++)
                   out[outpos++] = out[copysrc++];
           }

           block <<= 1;
           if (outpos >= fullsize || inpos >= compSize)
               break;
       }
    }

    return out;
}
