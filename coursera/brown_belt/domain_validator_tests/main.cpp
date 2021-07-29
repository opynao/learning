#include "test_runner.h"
#include "read_print.h"
#include "domain.h"
#include "domain_checker.h"
#include "check_domains.h"

#include <vector>
#include <string>
#include <sstream>

using namespace std;

// 1
void TestSplittingString()
{
    Domain domain(std::string{"ya.ru"});
    size_t size{2};
    ASSERT_EQUAL(domain.GetPartCount(), size);
}

// 2
void TestGetReversedParts()
{
    Domain domain(std::string{"ya.ru"});
    std::vector<std::string> expected{"ru", "ya"};
    auto parts = domain.GetReversedParts();
    std::vector<std::string> result{parts.begin(), parts.end()};
    ASSERT_EQUAL(result, expected);
}

// 3
void TestDomainIsItselfSubdomain()
{
    ASSERT_EQUAL(IsSubdomain(Domain{"ya.ru"}, Domain{"ya.ru"}), true);
}

// 4
void TestCheckDomainsArgs()
{
    std::ostringstream oss;
    const std::vector<Domain> banned_domains{Domain{"ya.ru"}};
    const std::vector<Domain> domains_to_check{Domain{"m.ya.ru"}};
    std::vector<bool> r{false};
    ASSERT_EQUAL(CheckDomains(banned_domains, domains_to_check), r);
}

// 7
void TestPrintCheckResults()
{
    std::ostringstream oss;
    const std::vector<Domain> banned_domains{Domain{"ya.ru"}};
    const std::vector<Domain> domains_to_check{Domain{"m.ya.ru"}, Domain{"ya.com"}};
    PrintCheckResults(CheckDomains(banned_domains, domains_to_check), oss);
    std::string result = oss.str();
    std::string expected{"Bad\nGood\n"};
    ASSERT_EQUAL(result, expected);
}

// 8
void TestReadDomains()
{
    std::istringstream iss_banned{"1\nya.ru"};
    std::istringstream iss_domains_to_check{"2\nm.ya.ru\nll.com\n"};

    const std::vector<Domain> banned_domains = ReadDomains(iss_banned);
    const std::vector<Domain> domains_to_check = ReadDomains(iss_domains_to_check);

    const std::vector<Domain> banned_domains_result{Domain{"ya.ru"}};
    const std::vector<Domain> domains_to_check_result{Domain{"m.ya.ru"}, Domain{"ll.com"}};

    ASSERT_EQUAL(banned_domains, banned_domains_result);
    ASSERT_EQUAL(domains_to_check, domains_to_check_result);
}

int main()
{
    TestRunner tr;
    //1
    RUN_TEST(tr, TestSplittingString);
    //2
    RUN_TEST(tr, TestGetReversedParts);
    //3
    RUN_TEST(tr, TestDomainIsItselfSubdomain);
    //4
    RUN_TEST(tr, TestCheckDomainsArgs);

    //7
    RUN_TEST(tr, TestPrintCheckResults);

    //8
    RUN_TEST(tr, TestReadDomains);

    // const std::vector<Domain> banned_domains = ReadDomains();
    // const std::vector<Domain> domains_to_check = ReadDomains();
    // PrintCheckResults(CheckDomains(banned_domains, domains_to_check));
    return 0;
}
