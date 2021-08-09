#pragma once

#include "command.h"

#include <memory>

class Button
{
    std::unique_ptr<Command> command;

public:
    Button(std::unique_ptr<Command> command)
        : command(std::move(command))
    {
    }
    void click()
    {
        command->execute();
    };
};
