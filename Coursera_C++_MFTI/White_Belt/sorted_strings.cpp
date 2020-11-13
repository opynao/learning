#include <set>
#include <vector>
#include <string>

class SortedStrings {
public:
	void AddString(const std::string& s)
       	{
		m_Strings.insert(s);
	}
	std::vector<std::string> GetSortedStrings()
       	{
		return std::vector<std::string>(std::cbegin(m_Strings),std::cend(m_Strings));
	}
private:
	std::multiset<std::string> m_Strings {};
};

