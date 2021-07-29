#include "domain_checker.h"
#include <algorithm>
using namespace std;

// domain is subdomain of itself
bool IsSubdomain(const Domain &subdomain, const Domain &domain)
{
    const auto subdomain_reversed_parts = subdomain.GetReversedParts();
    const auto domain_reversed_parts = domain.GetReversedParts();
    return subdomain.GetPartCount() >= domain.GetPartCount() && equal(begin(domain_reversed_parts), end(domain_reversed_parts),
                                                                      begin(subdomain_reversed_parts));
}

bool IsSubOrSuperDomain(const Domain &lhs, const Domain &rhs)
{
    return lhs.GetPartCount() >= rhs.GetPartCount()
               ? IsSubdomain(lhs, rhs)
               : IsSubdomain(rhs, lhs);
}

// Check if candidate is subdomain of some domain
bool DomainChecker::IsSubdomain(const Domain &candidate) const
{
    const auto it = upper_bound(
        begin(sorted_domains_), end(sorted_domains_),
        &candidate, IsDomainLess);

    if (it == begin(sorted_domains_))
        return false;

    return ::IsSubdomain(candidate, **prev(it));
}

bool DomainChecker::IsDomainLess(const Domain *lhs, const Domain *rhs)
{
    const auto lhs_reversed_parts = lhs->GetReversedParts();
    const auto rhs_reversed_parts = rhs->GetReversedParts();
    return lexicographical_compare(
        begin(lhs_reversed_parts), end(lhs_reversed_parts),
        begin(rhs_reversed_parts), end(rhs_reversed_parts));
}

vector<const Domain *> DomainChecker::AbsorbSubdomains(vector<const Domain *> domains)
{
    domains.erase(
        unique(begin(domains), end(domains),
               [](const Domain *lhs, const Domain *rhs)
               {
                   return IsSubOrSuperDomain(*lhs, *rhs);
               }),
        end(domains));
    return domains;
}
