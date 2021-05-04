#pragma once
#include "worker.h"
#include <functional>

class Filter : public Worker
{
public:
    using Function = std::function<bool(const Email &)>;

public:
    Filter(Function function)
        : function_{function}
    {
    }
    void Process(std::unique_ptr<Email> email) override
    {
        if (function_(*email.get()))
            PassOn(std::move(email));
    }

private:
    Function function_;
};
