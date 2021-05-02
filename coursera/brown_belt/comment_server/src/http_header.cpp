#include "http_header.h"

std::ostream &operator<<(std::ostream &output, const HttpHeader &h)
{
    return output << h.name << ": " << h.value;
}

bool operator==(const HttpHeader &lhs, const HttpHeader &rhs)
{
    return lhs.name == rhs.name && lhs.value == rhs.value;
}