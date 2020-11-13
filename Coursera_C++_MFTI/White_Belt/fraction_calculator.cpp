#include <iostream>
#include <sstream>
#include <numeric>
#include <string>
#include <exception>

using namespace std;

//------------------CLASS-INTERFACE-----------------

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
	int m_numerator {};
	int m_denominator {};
};

//--------------CLASS-CONSTRUCTS--------------------

Rational::Rational()
	: m_numerator {0}
	, m_denominator {1}
{
}

Rational::Rational(int numerator, int denominator)
	: m_numerator {numerator}
	, m_denominator {denominator}
{
	if(m_denominator == 0)
	{
		throw std::invalid_argument("Invalid argument");
	}
	Reduct();
}

//--------------MEMBER-FUNCTIONS-----------------

int Rational::Numerator() const
{
	return m_numerator;
}

int Rational::Denominator() const
{
	return m_denominator;
}

//---------------OVERLOADED-OPERATORS---------------


Rational operator / (const Rational& first, const Rational& second)
{
	if(second.Numerator() == 0)
		throw std::domain_error("Division by zero");
	Rational result {(first.Numerator()*second.Denominator()),(first.Denominator() * second.Numerator())};
        return result;	
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
bool operator == (const Rational& lhs,const Rational& rhs)
{
	return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

Rational operator + (const Rational& first, const Rational& second)
{
	Rational result {(first.Numerator()*second.Denominator() + second.Numerator()*first.Denominator()),(first.Denominator()*second.Denominator())};
        return result;	
}

Rational operator - (const Rational& first, const Rational& second)
{
	Rational result {(first.Numerator()*second.Denominator() - second.Numerator()*first.Denominator()),(first.Denominator() * second.Denominator())};
        return result;	
}

Rational operator * (const Rational& first, const Rational& second)
{
	Rational result {(first.Numerator()*second.Numerator()),(first.Denominator() * second.Denominator())};
        return result;	
}


//------------------IO-CLASS-OBJECTS----------------------------------
void Rational::Dump(ostream& os) const
{
	os << m_numerator << "/" << m_denominator;
}


bool InputProcessing(istream& is,int& number)
{
	int m = 1;
	char ch {};
	is.get(ch);
	while(std::isblank(ch))
	{
		is.get(ch);
	}
	if( std::isdigit(ch) )
		m = 1;
	else if( ch == '-' && std::isdigit( is.get() ) )
		m = -1;
	else 
		return false;
	is.unget();
	is >> number;
	number *= m;
	return true;
}

void Rational::Input(istream& is)
{
	int numerator {};
	int denominator {};
	if(!InputProcessing(is,numerator))
		return;

	char ch {};
	is.get(ch);
	if (ch != '/')
		return;

	if(!InputProcessing(is,denominator))
		return;
	
	m_numerator = numerator;
	m_denominator = denominator;
	Reduct();
}

istream& operator >> (istream& is, Rational& rational)
{
	rational.Input(is);
	return is;
}


ostream& operator << (ostream& os, const Rational& rational)
{
		
	rational.Dump(os);
	return os;
}


//-----------------------MAIN-----------------------------

int main() {
/*
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
*/
	Rational r1;
	Rational r2;
	char operation {};
	try
	{
		std::cin >> r1 >> operation >> r2;
		Rational result;		
		switch(operation)
		{
			case '+':
				result = r1 + r2;
				break;
			case '-':
				result = r1 - r2;
				break;
			case '*':
				result = r1 * r2;
				break;
			case '/':
				result = r1 / r2;
				break;
		}
		std::cout << result;
	}
	catch(std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
