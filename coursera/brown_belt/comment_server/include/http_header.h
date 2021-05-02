#pragma once
#include <string>
#include <ostream>

struct HttpHeader
{
    HttpHeader(const std::string &n, const std::string &v)
        : name{n}, value{v}
    {
    }
    std::string name;
    std::string value;
};

std::ostream &operator<<(std::ostream &output, const HttpHeader &h);

bool operator==(const HttpHeader &lhs, const HttpHeader &rhs);