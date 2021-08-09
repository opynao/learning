#pragma once

#include "command.h"
#include "canvas.h"

#include <string>
#include <memory>

class AddShapeCommand : public Command
{
    std::string m_shapeName;
    std::shared_ptr<Canvas> m_canvas;

public:
    AddShapeCommand(const std::string &shapeName, const std::shared_ptr<Canvas> &canvas)
        : m_shapeName(shapeName), m_canvas(canvas)
    {
    }

    void execute()
    {
        m_canvas->addShape(m_shapeName);
    }
};
