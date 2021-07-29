#pragma once

#include <string>
#include <memory>
#include <map>
#include <istream>
#include <vector>

#include "i_command.h"


class Parser
{
public:
    Parser(std::istream &is)
        : m_is{is}
    {
    }
    std::vector<std::shared_ptr<ICommand>> ParseRequest(const std::string &command)
    {
        int numberRequests;
        m_is >> numberRequests;
        std::vector<std::shared_ptr<ICommand>> vCommands(numberRequests);
        for (int i = 0; i != numberRequests; ++i)
        {
            std::string command;
            m_is >> command;
            if (command = "Stop")
            {

                m_is >>
            }
            vCommands[i].push_back;
        }
    }

private:
    std::istream &m_is;
};