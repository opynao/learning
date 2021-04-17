#include "entry.h"

bool operator<(const Entry &lhs, const Entry &rhs)
{
    if (lhs.wordOccurence == rhs.wordOccurence)
        return lhs.docid < rhs.docid;
    return lhs.wordOccurence > rhs.wordOccurence;
}
