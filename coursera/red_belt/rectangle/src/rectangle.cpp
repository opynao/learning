#include "rectangle.h"

void Rectangle::display() const
{
    std::cout << height << " " << widthi << std::endl;
}

void RectangleArea::read_input()
{
    std::cin >> width >> height;
}

void RectangleArea::display() const
{
    std::cout << (width * height) << std::endl;
}


