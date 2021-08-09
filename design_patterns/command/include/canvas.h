#pragma once

#include "shape.h"

#include <vector>
#include <string>
#include <algorithm>

class Canvas
{
public:
    void addShape(const std::string &newShape)
    {
        shapes.push_back({newShape});
    }
    void clearAll()
    {
        shapes.clear();
    }
    void rotateShape(const std::string &newShape)
    {
        std::for_each(shapes.begin(), shapes.end(),
                      [&newShape](Shape &shape)
                      {
                          if (shape.shapeName == newShape)
                              shape.changeRotation();
                      });
    }

    std::vector<Shape> getShapes() { return shapes; };

private:
    std::vector<Shape> shapes;
};
