#pragma once

#include "command.h"
#include "canvas.h"

#include <memory>

class ClearCommand : public Command
{
    std::shared_ptr<Canvas> canvas;

public:
    ClearCommand(std::shared_ptr<Canvas> canvas)
        : canvas(canvas)
    {
    }
    void execute()
    {
        canvas->clearAll();
    }
};
