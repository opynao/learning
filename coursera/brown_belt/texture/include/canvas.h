#include "Common.h"
#include "Textures.h"

#include <iostream>
#include <map>

class Canvas
{
public:
    using ShapeId = size_t;

    void SetSize(Size size);

    ShapeId AddShape(ShapeType shape_type, Point position, Size size,
                     std::unique_ptr<ITexture> texture);

    ShapeId DuplicateShape(ShapeId source_id, Point target_position);

    void RemoveShape(ShapeId id);

    void MoveShape(ShapeId id, Point position);

    void ResizeShape(ShapeId id, Size size);

    int GetShapesCount() const;

    void Print(std::ostream &output) const;

private:
    using Shapes = std::map<ShapeId, std::unique_ptr<IShape>>;

    Shapes::iterator GetShapeNodeById(ShapeId id);

    ShapeId InsertShape(std::unique_ptr<IShape> shape);

    Size size_ = {};
    ShapeId current_id_ = 0;
    Shapes shapes_;
};