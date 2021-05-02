#pragma once
#include "geo2d.h"
#include "game_object.h"

template <typename T>
struct Collider : public GameObject
{
    bool Collide(const GameObject &that) const final
    {
        return that.CollideWith(static_cast<const T &>(*this));
    }
};

class Building : public Collider<Building>
{
public:
    explicit Building(geo2d::Rectangle geometry);
    bool CollideWith(const Unit &that) const override;
    bool CollideWith(const Building &that) const override;
    bool CollideWith(const Tower &that) const override;
    bool CollideWith(const Fence &that) const override;
    geo2d::Rectangle GetGeometry() const;

private:
    geo2d::Rectangle geometry_;
};

class Unit : public Collider<Unit>
{
public:
    explicit Unit(geo2d::Point position);
    bool CollideWith(const Unit &that) const override;
    bool CollideWith(const Building &that) const override;
    bool CollideWith(const Tower &that) const override;
    bool CollideWith(const Fence &that) const override;
    geo2d::Point GetPosition() const;

private:
    geo2d::Point position_;
};

class Tower : public Collider<Tower>
{
public:
    explicit Tower(geo2d::Circle geometry);
    bool CollideWith(const Unit &that) const override;
    bool CollideWith(const Building &that) const override;
    bool CollideWith(const Tower &that) const override;
    bool CollideWith(const Fence &that) const override;
    geo2d::Circle GetGeometry() const;

private:
    geo2d::Circle geometry_;
};

class Fence : public Collider<Fence>
{
public:
    explicit Fence(geo2d::Segment geometry);
    bool CollideWith(const Unit &that) const override;
    bool CollideWith(const Building &that) const override;
    bool CollideWith(const Tower &that) const override;
    bool CollideWith(const Fence &that) const override;
    geo2d::Segment GetGeometry() const;

private:
    geo2d::Segment geometry_;
};