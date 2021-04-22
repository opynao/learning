#include "hasher.h"

size_t Hasher::operator()(const Point3D &point) const
{
    size_t x = ihash(point.x);
    size_t y = ihash(point.y);
    size_t z = ihash(point.z);
    size_t a = 2'946'901;
    return (x * x * x * a + y * a * y + z * a + a);
}
