#pragma once
#include "point.h"
#include <functional>

struct Hasher
{
    size_t operator()(const Point3D &point) const;
    std::hash<int> ihash;
};
