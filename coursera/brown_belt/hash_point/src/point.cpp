#include "point.h"

#include <tuple>

bool Point3D::operator==(const Point3D &other) const
{
    return std::tie(x, y, z) == std::tie(other.x, other.y, other.z);
}
