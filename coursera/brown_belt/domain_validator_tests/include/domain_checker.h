#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>

class DomainChecker
{
public:
    template <typename InputIt>
    DomainChecker(InputIt domains_begin, InputIt domains_end)
    {
        sorted_domains_.reserve(static_cast<size_t>(std::distance(domains_begin, domains_end)));
        for (const Domain &domain : Range(domains_begin, domains_end))
        {
            sorted_domains_.push_back(&domain);
        }
        std::sort(begin(sorted_domains_), end(sorted_domains_), IsDomainLess);
        sorted_domains_ = AbsorbSubdomains(move(sorted_domains_));
    }

    // Check if candidate is subdomain of some domain
    bool IsSubdomain(const Domain &candidate) const;

private:
    std::vector<const Domain *> sorted_domains_;

    static bool IsDomainLess(const Domain *lhs, const Domain *rhs);

    static std::vector<const Domain *> AbsorbSubdomains(std::vector<const Domain *> domains);
};

// domain is subdomain of itself
bool IsSubdomain(const Domain &subdomain, const Domain &domain);

bool IsSubOrSuperDomain(const Domain &lhs, const Domain &rhs);