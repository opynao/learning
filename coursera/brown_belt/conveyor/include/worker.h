#pragma once
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "email.h"
#include "utils.h"

class Worker
{
public:
    virtual ~Worker() = default;
    virtual void Process(std::unique_ptr<Email> email) = 0;
    virtual void Run()
    {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw std::logic_error("Unimplemented");
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(std::unique_ptr<Email> email) const
    {
        if (next_)
            next_->Process(std::move(email));
    }
    std::unique_ptr<Worker> next_;

public:
    void SetNext(std::unique_ptr<Worker> next)
    {
        next_ = std::move(next);
    }
};
