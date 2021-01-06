#include "rectangle.h"
#include "gtest/gtest.h"

TEST( Rectangle, Test1 )
{
    RectangleArea r_area;
    r_area.read_input();
    r_area.Rectangle::display();
    r_area.display();
}
  
