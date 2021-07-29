#include "read_print.h"
#include "domain_checker.h"

using namespace std;

vector<Domain> ReadDomains(istream &in_stream)
{
    vector<Domain> domains;

    size_t count;
    in_stream >> count;
    domains.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        string domain_text;
        in_stream >> domain_text;
        domains.emplace_back(domain_text);
    }
    return domains;
}

void PrintCheckResults(const vector<bool> &check_results, ostream &out_stream)
{
    for (const bool check_result : check_results)
        out_stream << (check_result ? "Good" : "Bad") << "\n";
}
