#include "canvas.h"
#include "utils.h"
using namespace std;

void Canvas::SetSize(Size size)
{
    m_ImageSize = size;
}

Canvas::ShapeId Canvas::AddShape(ShapeType shape_type, Point position, Size size,
                                 std::unique_ptr<ITexture> texture)
{
    LOGF;
    auto shape = MakeShape(shape_type);
    shape->SetPosition(position);
    shape->SetSize(size);
    shape->SetTexture(move(texture));
    LOGF;
    return InsertShape(move(shape));
}

Canvas::ShapeId Canvas::DuplicateShape(ShapeId source_id, Point target_position)
{
    auto shape = GetShapeNodeById(source_id)->second->Clone();
    shape->SetPosition(target_position);
    return InsertShape(move(shape));
}

void Canvas::RemoveShape(ShapeId id)
{
    shapes_.erase(GetShapeNodeById(id));
}

void Canvas::MoveShape(ShapeId id, Point position)
{
    GetShapeNodeById(id)->second->SetPosition(position);
}

void Canvas::ResizeShape(ShapeId id, Size size)
{
    GetShapeNodeById(id)->second->SetSize(size);
}

int Canvas::GetShapesCount() const
{
    return static_cast<int>(shapes_.size());
}

void Canvas::Print(ostream &output) const
{
    Image image(m_ImageSize.height, string(m_ImageSize.width, ' '));
    
    for (const auto &[id, shape] : shapes_)
        shape->Draw(image);
    
    output << '#' << string(m_ImageSize.width, '#') << "#\n";
    
    for (const auto &line : image)
        output << '#' << line << "#\n";
    
    output << '#' << string(m_ImageSize.width, '#') << "#\n";
}

Canvas::Shapes::iterator Canvas::GetShapeNodeById(ShapeId id)
{
    auto it = shapes_.find(id);
    if (it == shapes_.end())
        throw out_of_range("No shape with given ID");

    return it;
}

Canvas::ShapeId Canvas::InsertShape(unique_ptr<IShape> shape)
{
    shapes_[current_id_] = move(shape);
    return current_id_++;
}