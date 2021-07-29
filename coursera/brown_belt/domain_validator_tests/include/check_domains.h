#pragma once
#include "domain.h"
#include "domain_checker.h"

#include <vector>

std::vector<bool> CheckDomains(const std::vector<Domain> &banned_domains, const std::vector<Domain> &domains_to_check)
{
    const DomainChecker checker(std::begin(banned_domains), std::end(banned_domains));

    std::vector<bool> check_results;
    check_results.reserve(domains_to_check.size());
    for (const Domain &domain_to_check : domains_to_check)
        check_results.push_back(!checker.IsSubdomain(domain_to_check));

    return check_results;
}