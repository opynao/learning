#include "parser.h"
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>

Parser::Parser(std::istream &is, std::ostream &os)
    : m_is{is}, m_os{os}
{
    domains_t bannedDomains = ParseDomains();

    DomainsForbiddenListValidator manager(bannedDomains);
    domains_t domainsToCheck = ParseDomains();

    for (auto &domain : domainsToCheck)
        m_os << (manager.Validate(domain) == true ? "Good\n" : "Bad\n");
}

domains_t Parser::ParseDomains()
{
    size_t count;
    m_is >> count;

    domains_t domains;
    domains.reserve(count);

    std::copy_n(std::istream_iterator<domain_t>(m_is),
                count,
                std::back_inserter(domains));

    return domains;
}