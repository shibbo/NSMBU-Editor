#include "util/units.h"

namespace util {
int sign(int nbr) {
    return (nbr >= 0) ? 1 : -1;
}

int to64(int nbr) {
    return (int)((float)nbr / (float)16 * 64 + sign(nbr) * 0.5f);
}
};
