#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <set>
#include <vector>
using Cost_t = double;
using Discount_t = double;

class DiscountRule
{
public:
	DiscountRule(const Cost_t cost, const Discount_t discount);
	bool Apply(const Cost_t originalCost) const;
	Discount_t GetDiscount() const;
	bool operator < (const DiscountRule& rhs) const;
	bool operator == (const DiscountRule& rhs) const;
private:
	Cost_t m_Cost;
	Discount_t m_Discount;
};


DiscountRule::DiscountRule(const Cost_t cost, const Discount_t discount)
	: m_Cost {cost}
	, m_Discount {discount}
	 
{}

bool DiscountRule::Apply(const Cost_t originalCost) const
{
	return originalCost > m_Cost;
}

Discount_t DiscountRule::GetDiscount() const
{
	return m_Discount;
}

bool DiscountRule::operator < (const DiscountRule& rhs) const
{
	return m_Cost < rhs.m_Cost;
}

bool DiscountRule::operator == (const DiscountRule& rhs) const
{
	return m_Cost == rhs.m_Cost && m_Discount == rhs.m_Discount;
}

class DiscountCalculator
{
public: 
	explicit DiscountCalculator(const std::set<DiscountRule>& rulesList);
	Cost_t operator () (const Cost_t originalCost) const;	       	
private:
	std::set<DiscountRule> m_rules;
};

DiscountCalculator::DiscountCalculator(const std::set<DiscountRule>& rulesList)
	:m_rules {rulesList}
{}

Cost_t DiscountCalculator::operator () (const Cost_t originalCost) const
{
	auto it {m_rules.rbegin()};
	while(!it->Apply(originalCost))
	{
		if(it == m_rules.rend())
			return originalCost;
		++it;
	}
	return originalCost*(100-it->GetDiscount())/100;
}



int main()
{
	double originalCost {};
	double diapazon1 {};
	double diapazon2 {};
	double skidka1 {};
	double skidka2 {};
	std::set<DiscountRule> vRules;
	std::cin >> originalCost >> diapazon1 >> diapazon2 >> skidka1 >> skidka2;
	vRules.emplace(diapazon1,skidka1);
	vRules.emplace(diapazon2,skidka2);
	DiscountCalculator dc(vRules);
	std::cout << dc(originalCost);
	return 0;
}
