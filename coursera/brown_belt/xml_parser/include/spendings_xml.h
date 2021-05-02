#include "xml.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#define PR(x) std::cerr << #x << " = " << x << std::endl

struct Spending
{
    string category;
    int amount;
    Spending(const std::string &c, const int a)
        : category{c}, amount{a}
    {
    }
};

bool operator==(const Spending &lhs, const Spending &rhs)
{
    return lhs.category == rhs.category && lhs.amount == rhs.amount;
}

ostream &operator<<(ostream &os, const Spending &s)
{
    return os << '(' << s.category << ": " << s.amount << ')';
}

int CalculateTotalSpendings(
    const vector<Spending> &spendings)
{
    int result = 0;
    for (const Spending &s : spendings)
        result += s.amount;

    return result;
}

string MostExpensiveCategory(
    const vector<Spending> &spendings)
{
    auto compare_by_amount =
        [](const Spending &lhs, const Spending &rhs) {
            return lhs.amount < rhs.amount;
        };
    return max_element(begin(spendings), end(spendings), compare_by_amount)->category;
}

vector<Spending> LoadFromXml(istream &input)
{
    std::vector<Spending> result;
    Document doc = Load(input);
    const Node &root = doc.GetRoot();
    for (const Node &node : root.Children())
    {
        Spending spending(node.AttributeValue<string>("category"), node.AttributeValue<int>("amount"));
        result.push_back(spending);
    }
    return result;
}