#include "canvas.h"
#include "button.h"
#include "add_shape_command.h"
#include "clear_command.h"
#include "rotate_command.h"

#include <iostream>
#include <memory>

std::string vectorToString(const std::vector<Shape> &v)
{
    std::string result = "";
    for (size_t i = 0; i < v.size(); i++)
    {
        auto &shape = v.at(i);
        result.append(shape.shapeName + " " + shape.GetRotation() + ", ");
    }
    return result;
}

int main()
{
    auto canvas = std::make_shared<Canvas>();

    auto addTriangleButton = std::make_unique<Button>(std::make_unique<AddShapeCommand>("triangle", canvas));
    auto addSquareButton = std::make_unique<Button>(std::make_unique<AddShapeCommand>("square", canvas));
    auto clearButton = std::make_shared<Button>(std::make_unique<ClearCommand>(canvas));
    auto rotateSquareButton = std::make_unique<Button>(std::make_unique<RotateCommand>("square", canvas));

    addTriangleButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";

    addSquareButton->click();
    addSquareButton->click();
    addTriangleButton->click();
    rotateSquareButton->click();

    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";

    clearButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";

    return 0;
}