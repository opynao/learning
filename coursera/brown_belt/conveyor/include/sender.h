#include "worker.h"
#include <sstream>
#include <ostream>

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
