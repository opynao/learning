#pragma once
#include "worker.h"

#include <sstream>
#include <string>
#include <vector>
#include <iterator>

class Reader : public Worker
{
public:
    Reader(std::istream &is)
        : is_{is}
    {
    }
    void Run() override
    {
        while (is_)
        {
            auto email = std::make_unique<Email>();
            std::getline(is_, email->from, '\n');
            if (is_.eof())
                return;

            std::getline(is_, email->to, '\n');
            if (is_.eof())
                return;

            std::getline(is_, email->body, '\n');

            PassOn(std::move(email));
        }
    }
    void Process([[maybe_unused]] std::unique_ptr<Email> email) override
    {
    }

private:
    std::istream &is_;
};
