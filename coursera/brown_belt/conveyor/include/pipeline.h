#pragma once
#include "worker.h"
#include "reader.h"
#include "filter.h"
#include "copier.h"
#include "sender.h"
#include <iostream>
#include <stack>
#include <memory>

// реализуйте класс
class PipelineBuilder
{
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(std::istream &in)
    {
        workersPool_.push(std::make_unique<Reader>(in));
    }

    // добавляет новый обработчик Filter
    PipelineBuilder &FilterBy(Filter::Function filter)
    {
        workersPool_.push(std::make_unique<Filter>(filter));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder &CopyTo(std::string recipient)
    {
        workersPool_.push(std::make_unique<Copier>(recipient));
        return *this;
    }
    // добавляет новый обработчик Sender
    PipelineBuilder &Send(std::ostream &out)
    {
        workersPool_.push(std::make_unique<Sender>(out));
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    std::unique_ptr<Worker> Build()
    {
        if (workersPool_.empty())
            return nullptr;
        while (workersPool_.size() != 1)
        {
            auto w = std::move(workersPool_.top());
            workersPool_.pop();
            workersPool_.top()->SetNext(std::move(w));
        }
        return std::move(workersPool_.top());
    }

private:
    std::stack<std::unique_ptr<Worker>> workersPool_;
};