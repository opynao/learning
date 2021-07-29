#include "split.h"

using namespace std;

pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter)
{
    const size_t pos = s.find(delimiter);
    if (pos == s.npos)
    {
        return {s, nullopt};
    }
    else
    {
        return {s.substr(0, pos), s.substr(pos + delimiter.length())};
    }
}

vector<string_view> Split(string_view s, string_view delimiter)
{
    vector<string_view> parts;
    if (s.empty())
    {
        return parts;
    }
    while (true)
    {
        const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
        parts.push_back(lhs);
        if (!rhs_opt)
        {
            break;
        }
        s = *rhs_opt;
    }
    return parts;
}
