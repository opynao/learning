#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <numeric>

using namespace std;

class Rational {
public:
	Rational();
	Rational(int, int); 
	int Numerator() const;
	int Denominator() const;
private:
	void Reduct();
	int m_numerator {};
	int m_denominator {};
};

Rational::Rational()
	: m_numerator {0}
	, m_denominator {1}
{
}

Rational::Rational(int numerator, int denominator)
	: m_numerator {numerator}
	, m_denominator {denominator}
{
	Reduct();
}

int Rational::Numerator() const
{
	return m_numerator;
}

int Rational::Denominator() const
{
	return m_denominator;
}

bool operator == (const Rational& lhs,const Rational& rhs)
{
	return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

void Rational::Reduct()
{
	int nod = std::gcd(m_numerator,m_denominator);
	m_numerator = m_numerator/nod;
	m_denominator = m_denominator/nod;
	if(m_denominator < 0)
	{
		m_denominator = -m_denominator;
		m_numerator = -m_numerator;
	}
}

Rational operator - (const Rational& first, const Rational& second)
{
	Rational result {(first.Numerator()*second.Denominator() - second.Numerator()*first.Denominator()),(first.Denominator() * second.Denominator())};
        return result;	
}


bool operator < (const Rational& rhs, const Rational& lhs)
{
	return ((rhs - lhs).Numerator() < 0);		
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
