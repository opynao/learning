#include "Common.h"

using namespace std;

class Shape : public IShape
{
public:
    void SetPosition(Point point) final
    {
        point_ = std::move(point);
    }
    Point GetPosition() const final
    {
        return point_;
    }
    void SetSize(Size size) final
    {
        size_ = std::move(size);
    }
    Size GetSize() const final
    {
        return size_;
    }
    void SetTexture(std::shared_ptr<ITexture> texture) final
    {
        texture_ = texture;
    }
    ITexture *GetTexture() const final
    {
        return texture_.get();
    }

protected:
    Point point_;
    Size size_;
    std::shared_ptr<ITexture> texture_;
};

class Rectangle : public Shape
{
public:
    std::unique_ptr<IShape> Clone() const override
    {
        return std::make_unique<Rectangle>(*this);
    }
    // Рисует фигуру на указанном изображении

    void Draw(Image &image) const final
    {
        int figureBeginLine = point_.y;
        int figureBeginColumn = point_.x;

        int figureEndLine = size_.height + point_.y;
        int figureEndColumn = size_.width + point_.x;

        for (int line = figureBeginLine; line != figureEndLine; ++line)
        {
            for (int column = figureBeginColumn; column != figureEndColumn; ++column)
            {
                if (IsPointInEllipseAndTexture(line, column))
                    image[line][column] = GetCharAtPoint(line, column);
                else
                    image[line][column] = '.';
            }
        }
    }

private:
    char GetCharAtPoint(const int line, const int column) const
    {
        return texture_->GetImage().at(line - point_.y).at(column - point_.x);
    }
    bool IsPointInEllipseAndTexture(const int line, const int column) const
    {
        return texture_ && IsLineInTexture(line) && IsColumnInTexture(column);
    }
    bool IsLineInTexture(const int line) const
    {
        return line <= texture_->GetSize().height;
    }
    bool IsColumnInTexture(const int column) const
    {
        return column <= texture_->GetSize().width;
    }
};

class Ellipse : public Shape
{
public:
    std::unique_ptr<IShape> Clone() const override
    {
        return std::make_unique<Ellipse>(*this);
    }
    void Draw(Image &image) const final
    {
        for (int y = 0; y < size_.height; ++y)
        {
            for (int x = 0; x < size_.width; ++x)
            {
                if (IsPointInEllipse({x, y}, size_))
                {
                    if (IsPointInEllipseAndTexture(x, y))
                        image[point_.y + y][point_.x + x] = GetCharAtPoint(x, y);
                    else
                        image[point_.y + y][point_.x + x] = '.';
                }
            }
        }
    }

private:
    char GetCharAtPoint(const int line, const int column) const
    {
        return texture_->GetImage().at(line).at(column);
    }
    bool IsPointInEllipseAndTexture(const int line, const int column) const
    {
        return texture_ && IsLineInTexture(line) && IsColumnInTexture(column);
    }
    bool IsLineInTexture(int line) const
    {
        return line <= texture_->GetSize().height;
    }
    bool IsColumnInTexture(int column) const
    {
        return column <= texture_->GetSize().width;
    }
};

unique_ptr<IShape> MakeShape(ShapeType shape_type)
{
    if (shape_type == ShapeType::Ellipse)
        return std::make_unique<Ellipse>();
    return std::make_unique<Rectangle>();
}