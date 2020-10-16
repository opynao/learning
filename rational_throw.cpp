#include <iostream>
#include <exception>
#include <iostream>
#include <sstream>
#include <numeric>
#include <string>
#include <iomanip>

using namespace std;

class Rational {
public:
	Rational();
	Rational(int, int);
	int Numerator() const;
	int Denominator() const;
	void Input(istream&);
	void Dump(ostream&) const;
private:
	void Reduct();
	int m_numerator{};
	int m_denominator{};
};

Rational::Rational()
	: m_numerator{ 0 }
	, m_denominator{ 1 }
{
}

Rational::Rational(int numerator, int denominator)
	: m_numerator{ numerator }
	, m_denominator{ denominator }
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

bool operator == (const Rational& lhs, const Rational& rhs)
{
	return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

Rational operator + (const Rational& first, const Rational& second)
{
	Rational result{ (first.Numerator() * second.Denominator() + second.Numerator() * first.Denominator()),(first.Denominator() * second.Denominator()) };
	return result;
}

Rational operator - (const Rational& first, const Rational& second)
{
	Rational result{ (first.Numerator() * second.Denominator() - second.Numerator() * first.Denominator()),(first.Denominator() * second.Denominator()) };
	return result;
}

Rational operator * (const Rational& first, const Rational& second)
{
	Rational result{ (first.Numerator() * second.Numerator()),(first.Denominator() * second.Denominator()) };
	return result;
}

Rational operator / (const Rational& first, const Rational& second)
{
	Rational result{ (first.Numerator() * second.Denominator()),(first.Denominator() * second.Numerator()) };
	return result;
}

void Rational::Reduct()
{
	int nod = std::gcd(m_numerator, m_denominator);
	m_numerator = m_numerator / nod;
	m_denominator = m_denominator / nod;
	if (m_denominator < 0)
	{
		m_denominator = -m_denominator;
		m_numerator = -m_numerator;
	}
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
