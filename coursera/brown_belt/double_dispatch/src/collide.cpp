#include "collide.h"

#include <vector>
#include <memory>

#define UnitOther return geo2d::Collide(position_, that.GetGeometry())
#define OtherOther return geo2d::Collide(geometry_, that.GetGeometry())
#define OtherUnit return geo2d::Collide(geometry_, that.GetPosition())
#define Geometry return geometry_

using namespace std;

bool Collide(const GameObject &first, const GameObject &second)
{
  return first.Collide(second);
}


Unit::Unit(geo2d::Point position)
    : position_{position}
{
}

bool Unit::CollideWith(const Unit &that) const
{
  return geo2d::Collide(position_, that.position_);
}
bool Unit::CollideWith(const Building &that) const { UnitOther; }
bool Unit::CollideWith(const Tower &that) const { UnitOther; }
bool Unit::CollideWith(const Fence &that) const { UnitOther; }

geo2d::Point Unit::GetPosition() const
{
  return position_;
}

Building::Building(geo2d::Rectangle geometry)
    : geometry_{geometry}
{
}
bool Building::CollideWith(const Unit &that) const { OtherUnit; }
bool Building::CollideWith(const Building &that) const { OtherOther; }
bool Building::CollideWith(const Tower &that) const { OtherOther; }
bool Building::CollideWith(const Fence &that) const { OtherOther; }

geo2d::Rectangle Building::GetGeometry() const { Geometry; }

Tower::Tower(geo2d::Circle geometry)
    : geometry_{geometry}
{
}

bool Tower::CollideWith(const Unit &that) const { OtherUnit; }
bool Tower::CollideWith(const Building &that) const { OtherOther; }
bool Tower::CollideWith(const Tower &that) const { OtherOther; }
bool Tower::CollideWith(const Fence &that) const { OtherOther; }

geo2d::Circle Tower::GetGeometry() const { Geometry; }

Fence::Fence(geo2d::Segment geometry)
    : geometry_{geometry}
{
}

bool Fence::CollideWith(const Unit &that) const { OtherUnit; }
bool Fence::CollideWith(const Building &that) const { OtherOther; }
bool Fence::CollideWith(const Tower &that) const { OtherOther; }
bool Fence::CollideWith(const Fence &that) const { OtherOther; }

geo2d::Segment Fence::GetGeometry() const { Geometry; }