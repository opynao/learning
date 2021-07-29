#include "domain.h"

using namespace std;

ostream &operator<<(ostream &stream, const Domain &domain)
{
    bool first = true;
    for (const string_view part : domain.GetParts())
    {
        if (!first)
        {
            stream << '.';
        }
        else
        {
            first = false;
        }
        stream << part;
    }
    return stream;
}
