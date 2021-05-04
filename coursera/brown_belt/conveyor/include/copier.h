#pragma once
#include "worker.h"

class Copier : public Worker
{
public:
    Copier(const std::string &copyTo)
        : copyTo_{copyTo}
    {
    }
    void Process(std::unique_ptr<Email> email) override
    {
        if (email->to == copyTo_)
            PassOn(std::move(email));
        else
        {
            auto emailCopy = std::make_unique<Email>(*email.get());
            emailCopy->to = copyTo_;
            PassOn(std::move(email));
            PassOn(std::move(emailCopy));
        }
    }

private:
    std::string copyTo_;
};