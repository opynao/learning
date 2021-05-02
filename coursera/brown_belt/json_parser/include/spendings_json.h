#include "json.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

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
    {
        result += s.amount;
    }
    return result;
}

string MostExpensiveCategory(
    const vector<Spending> &spendings)
{
    auto compare_by_amount =
        [](const Spending &lhs, const Spending &rhs) {
            return lhs.amount < rhs.amount;
        };
    return max_element(begin(spendings), end(spendings),
                       compare_by_amount)
        ->category;
}

vector<Spending> LoadFromJson(istream &input)
{
    std::vector<Spending> result;
    Document doc = Load(input);
    const vector<Node> &root = doc.GetRoot().AsArray();
    for (const auto &r : root)
    {
        const map<string, Node> &node = r.AsMap();
        Spending spending(node.at("category").AsString(), node.at("amount").AsInt());
        result.push_back(spending);
    }
    return result;
}