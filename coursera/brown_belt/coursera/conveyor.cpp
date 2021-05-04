#include <iostream>
#include <stack>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <functional>

struct Email
{
    std::string from;
    std::string to;
    std::string body;
};

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
    std::vector<std::unique_ptr<Email>> emails_;
};

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

class Sender : public Worker
{
public:
    Sender(std::ostream &os)
        : os_{os}
    {
    }
    void Process(std::unique_ptr<Email> email) override
    {
        os_ << email->from << "\n";
        os_ << email->to << "\n";
        os_ << email->body << "\n";
        PassOn(std::move(email));
    }

private:
    std::ostream &os_;
};

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

// реализуйте класс
class PipelineBuilder
{
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(std::istream &in)
    {
        auto worker_ = std::make_unique<Reader>(in);
        workersPool_.push(std::move(worker_));
    }

    // добавляет новый обработчик Filter
    PipelineBuilder &FilterBy(Filter::Function filter)
    {
        auto f = std::make_unique<Filter>(filter);
        workersPool_.push(std::move(f));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder &CopyTo(std::string recipient)
    {
        auto c = std::make_unique<Copier>(recipient);
        workersPool_.push(std::move(c));
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

int main()
{
    return 0;
}