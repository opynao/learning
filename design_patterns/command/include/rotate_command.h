#pragma once

#include "command.h"
#include "canvas.h"

#include <string>
#include <memory>

class RotateCommand : public Command
{
    std::string m_shapeName;
    std::shared_ptr<Canvas> m_canvas;

public:
    RotateCommand(const std::string &shapeName, const std::shared_ptr<Canvas> &canvas)
        : m_shapeName(shapeName), m_canvas(canvas)
    {
    }
    void execute()
    {
        m_canvas->rotateShape(m_shapeName);
    }
};
