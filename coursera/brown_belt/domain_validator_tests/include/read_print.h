#pragma once
#include "domain.h"

#include <vector>
#include <iostream>

std::vector<Domain> ReadDomains(std::istream &in_stream = std::cin);

void PrintCheckResults(const std::vector<bool> &check_results, std::ostream &out_stream = std::cout);