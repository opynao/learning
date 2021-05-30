#include <algorithm>

#include "domain_validator.h"

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