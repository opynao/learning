#pragma once

#include <string>

enum class Rotation
{
    Up,
    Down,
    Last
};

struct Shape
{
    std::string shapeName;
    Rotation rotation{Rotation::Down};
    void changeRotation()
    {
        if (rotation == Rotation::Up)
            rotation = Rotation::Down;
        else
            rotation = Rotation::Up;
    }
    std::string GetRotation() const
    {
        if (rotation == Rotation::Down)
            return "down";
        else
            return "up";
    }
};