#include "MathUtil.h"

namespace Util {
    quint32 min(quint32 lhs, quint32 rhs) {
        if (lhs > rhs) {
            return rhs;
        }
        else {
            return lhs;
        }
    }

    quint32 max(quint32 lhs, quint32 rhs) {
        if (lhs > rhs) {
            return lhs;
        }
        else {
            return rhs;
        }
    }

    quint32 powTwoAlign(quint32 x, quint32 align) {
        return ~(align - 1) & (x + align - 1);
    }

    quint32 nextPow2(quint32 dim) {
        quint32 newDim = 1;
        if (dim < 0x7FFFFFFF) {
            while (newDim < dim) {
                newDim *= 2;
            }
        }
        else {
            newDim = 0x80000000;
        }

        return newDim;
    }

    qint32 RoundUp(qint32 X, qint32 Y) {
        return ((X - 1) | (Y - 1)) + 1;
    }

    quint32 RoundUp(quint32 X, quint32 Y) {
        return ((X - 1) | (Y - 1)) + 1;
    }
};
