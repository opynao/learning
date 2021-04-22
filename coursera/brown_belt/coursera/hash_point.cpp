#include <tuple>
#include <functional>

using CoordType = int;

struct Point3D
{
    CoordType x;
    CoordType y;
    CoordType z;

    bool operator==(const Point3D &other) const;
};

bool Point3D::operator==(const Point3D &other) const
{
    return std::tie(x, y, z) == std::tie(other.x, other.y, other.z);
}

struct Hasher
{
    size_t operator()(const Point3D &point) const;
    std::hash<int> ihash;
};

size_t Hasher::operator()(const Point3D &point) const
{
    size_t x = ihash(point.x);
    size_t y = ihash(point.y);
    size_t z = ihash(point.z);
    size_t a = 2'946'901;

    return (x * x * a + y * a + z);
}

int main()
{
    return 0;
}