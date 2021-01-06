#pragma once

class Rectangle
{
public:
    virtual void display() const;
private:
    int height;
    int width;
};

class RectangleArea : public Rectangle
{
public:
    void read_input();
    void display() const override;
};


