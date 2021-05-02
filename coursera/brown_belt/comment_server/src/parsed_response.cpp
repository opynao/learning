#include "parsed_response.h"
#include "http_request.h"
#include <sstream>

using namespace std;

istream &operator>>(istream &input, ParsedResponse &r)
{
    string line;
    getline(input, line);
    {
        istringstream code_input(line);
        string dummy;
        code_input >> dummy >> r.code;
    }

    size_t content_length = 0;

    r.headers.clear();
    while (getline(input, line) && !line.empty())
    {
        if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length")
        {
            istringstream length_input(value);
            length_input >> content_length;
        }
        else
            r.headers.push_back({std::move(name), std::move(value)});
    }

    r.content.resize(content_length);
    input.read(r.content.data(), r.content.size());
    return input;
}