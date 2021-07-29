#pragma once

#include "i_event.h"
#include "parser.h"

#include <vector>
#include <memory>
#include <istream>

class InputController
{
public:
    InputController(std::istream &is)
        : m_parser{is}
    {
    }
    void Attach(std::shared_ptr<IInputControllerEvents> eventObserver)
    {
        m_spEventsObservers.push_back(eventObserver);
    }

private:
    void Notify(std::shared_ptr<ICommand> spCommand) const
    {
        for (const auto &eventObserver : m_spEventsObservers)
            eventObserver->OnCommand(spCommand);
    }

private:
    std::vector<std::shared_ptr<IInputControllerEvents>> m_spEventsObservers;
    Parser m_parser;
};