#pragma once

using CoordType = int;

struct Point3D
{
    CoordType x;
    CoordType y;
    CoordType z;

    bool operator==(const Point3D &other) const;
};
