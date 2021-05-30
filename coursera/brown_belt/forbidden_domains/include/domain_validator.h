#pragma once
#include <vector>
#include <string>

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