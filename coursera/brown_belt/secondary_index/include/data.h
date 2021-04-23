#pragma once

#include "record.h"
#include <map>

struct Data
{
    using IteratorInt_t = std::multimap<int, Record *>::iterator;
    using IteratorString_t = std::multimap<std::string, Record *>::iterator;

    Data(const IteratorInt_t itTempStamp,
         const IteratorInt_t itKarma,
         const IteratorString_t itUser,
         const Record record)
        : itTimeStamp_{itTempStamp}, itKarma_{itKarma}, itUser_{itUser}, record_{record}
    {
    }
    IteratorInt_t itTimeStamp_{};
    IteratorInt_t itKarma_{};
    IteratorString_t itUser_{};
    Record record_{};
};
