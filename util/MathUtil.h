#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <QString>

namespace Util {
    quint32 min(quint32 lhs, quint32 rhs);
    quint32 max(quint32 lhs, quint32 rhs);

    quint32 powTwoAlign(quint32 x, quint32 align);
    quint32 nextPow2(quint32 dim);

    qint32 RoundUp(qint32 X, quint32 Y);
    quint32 RoundUp(quint32 X, quint32 Y);
};

#endif // MATHUTIL_H
