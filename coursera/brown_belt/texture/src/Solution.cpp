#include "Common.h"

using namespace std;

class Shape : public IShape
{
public:
    void SetPosition(Point point) final
    {
        m_StartPoint = point;
    }
    Point GetPosition() const final
    {
        return m_StartPoint;
    }

    void SetSize(Size size) final
    {
        m_ShapeSize = size;
    }
    Size GetSize() const final
    {
        return m_ShapeSize;
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
    Point m_StartPoint;
    Size m_ShapeSize;
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
        size_t figureBeginLine = m_StartPoint.y;
        size_t figureBeginColumn = m_StartPoint.x;

        if (figureBeginColumn > image[0].size() || figureBeginLine > image.size())
            return;

        size_t figureEndLine = m_ShapeSize.height + m_StartPoint.y;
        size_t figureEndColumn = m_ShapeSize.width + m_StartPoint.x;

        if (image[0].size() < figureEndColumn)
            figureEndColumn = image[0].size();

        if (image.size() < figureEndLine)
            figureEndLine = image.size();

        for (size_t line = figureBeginLine; line != figureEndLine; ++line)
        {
            for (size_t column = figureBeginColumn; column != figureEndColumn; ++column)
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
        return texture_->GetImage().at(line - m_StartPoint.y).at(column - m_StartPoint.x);
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
        size_t figureBeginLine = m_StartPoint.y;
        size_t figureBeginColumn = m_StartPoint.x;

        if (figureBeginColumn > image[0].size() || figureBeginLine > image.size())
            return;

        size_t figureEndLine = m_ShapeSize.height + m_StartPoint.y;
        size_t figureEndColumn = m_ShapeSize.width + m_StartPoint.x;

        if (image[0].size() < figureEndColumn)
            figureEndColumn = image[0].size();

        if (image.size() < figureEndLine)
            figureEndLine = image.size();

        for (int y = 0; y != m_ShapeSize.height; ++y)
        {
            for (size_t x = 0; x != m_ShapeSize.width; ++x)
            {
                if (IsPointInEllipse({x, y}, m_ShapeSize))
                {
                    if (IsPointInEllipseAndTexture(x, y))
                        image[m_StartPoint.y + y][m_StartPoint.x + x] = GetCharAtPoint(x, y);
                    else
                        image[m_StartPoint.y + y][m_StartPoint.x + x] = '.';
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