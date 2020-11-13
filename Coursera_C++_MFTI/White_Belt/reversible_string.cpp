#include <memory>
#include <cassert>
#include <string>
#include <algorithm>

class ReversibleString
{
public:
	ReversibleString();
	explicit ReversibleString(const std::string&);
	void Reverse();
	std::string ToString() const;
private:
	std::string m_str {};
};

ReversibleString::ReversibleString()
{}

ReversibleString::ReversibleString(const std::string& str)
	: m_str {str}
{
}

void ReversibleString::Reverse()
{
	std::reverse(std::begin(m_str),std::end(m_str));
}

std::string ReversibleString::ToString() const
{
	return m_str;
}

void testReversibleString_ConstructWithString()
{
	const auto upReversibleString = std::make_unique<ReversibleString>("live");
	assert(nullptr != upReversibleString);
}

void testReversibleString_Reverse_ToStringReturnReverseString()
{
	const auto upReversibleString = std::make_unique<ReversibleString>("live");
       	upReversibleString->Reverse();
	assert("evil" == upReversibleString->ToString());
}

void testReversibleString_ReverseEmptyString_ToStringReturnEmptyString()
{
	const auto upReversibleString = std::make_unique<ReversibleString>("");
       	upReversibleString->Reverse();
	assert("" == upReversibleString->ToString());
}
/*
int main()
{
  ReversibleString s("live");
  s.Reverse();
  std::cout << s.ToString() << std::endl;
  
  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  std::cout << tmp << std::endl;
  
  ReversibleString empty;
  std:: cout << '"' << empty.ToString() << '"' << std::endl;
  
  return 0;
}


int main()
{
	testReversibleString_ReverseEmptyString_ToStringReturnEmptyString();
	testReversibleString_Reverse_ToStringReturnReverseString();
	testReversibleString_ConstructWithString();
	return 0;
}
*/
