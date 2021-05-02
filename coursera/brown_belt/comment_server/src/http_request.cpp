#include "http_request.h"

#include <sstream>

using namespace std;

pair<string, string> SplitBy(const string &what, const string &by)
{
    size_t pos = what.find(by);
    if (by.size() < what.size() && pos < what.size() - by.size())
        return {what.substr(0, pos), what.substr(pos + by.size())};
    
    else
        return {what, {}};
}

template <typename T>
T FromString(const string &s)
{
    T x;
    istringstream is(s);
    is >> x;
    return x;
}

pair<size_t, string> ParseIdAndContent(const string &body)
{
    auto [id_string, content] = SplitBy(body, " ");
    return {FromString<size_t>(id_string), content};
}