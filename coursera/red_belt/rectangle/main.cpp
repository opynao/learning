#include <iostream>

class Rectangle
{
public:
    virtual void display() const;
protected:
    int height;
    int width;
};

class RectangleArea : public Rectangle
{
public:
    void read_input();
    void display() const override;
};

void Rectangle::display() const
{
    std::cout << width << " " << height << std::endl;
}

void RectangleArea::read_input()
{
    std::cin >> width >> height;
}

void RectangleArea::display() const
{
    std::cout << (width * height) << std::endl;
}


int main()
{
    RectangleArea r_area;
    r_area.read_input();
    r_area.Rectangle::display();
    r_area.display();
    return 0;
}
