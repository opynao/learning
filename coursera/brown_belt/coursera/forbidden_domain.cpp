#include <vector>
#include <string>
#include <algorithm>
#include <string_view>
#include <iostream>
#include <iterator>

using domain_t = std::string;
using domains_t = std::vector<domain_t>;

class DomainsForbiddenListValidator
{
public:
    DomainsForbiddenListValidator(const domains_t &);
    bool Validate(domain_t &);

private:
    bool IsSubdomain(const domain_t &, const domain_t &) const;

private:
    domains_t m_BannedDomains;
};

DomainsForbiddenListValidator::DomainsForbiddenListValidator(const domains_t &bannedDomains)
    : m_BannedDomains{std::move(bannedDomains)}
{
    for (std::string &domain : m_BannedDomains)
        std::reverse(begin(domain), end(domain));

    std::sort(std::begin(m_BannedDomains), std::end(m_BannedDomains));

    auto it = std::unique(m_BannedDomains.begin(), m_BannedDomains.end(),
                          [this](const std::string &domainLeft, const std::string &domainRight) { return IsSubdomain(domainLeft, domainRight); });
    m_BannedDomains.erase(it, m_BannedDomains.end());
}

bool DomainsForbiddenListValidator::Validate(domain_t &domain)
{
    std::reverse(begin(domain), end(domain));

    if (const auto it = std::upper_bound(std::begin(m_BannedDomains), std::end(m_BannedDomains), domain);
        it != std::cbegin(m_BannedDomains) && IsSubdomain(domain, *prev(it)))
        return false;

    return true;
}

bool DomainsForbiddenListValidator::IsSubdomain(const std::string &subdomain, const std::string &domain) const
{
    size_t i{};
    size_t j{};
    for (; i != subdomain.size() && j != domain.size(); i++, j++)
    {
        if (subdomain[i] != domain[j])
            return false;
    }
    return (i == subdomain.size() && domain[j] == '.') ||
           (j == domain.size() && subdomain[i] == '.') ||
           subdomain.size() == domain.size();
}

class Parser
{
public:
    Parser(std::istream &is, std::ostream &os);

private:
    domains_t ParseDomains();

private:
    std::istream &m_is;
    std::ostream &m_os;
};

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

int main()
{
    Parser parse(std::cin, std::cout);
    return 0;
}