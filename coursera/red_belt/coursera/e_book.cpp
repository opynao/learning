#include <map>
#include <set>
#include <iomanip>
#include <iostream>
#include <utility>
#include <iterator>
#include <string>
#include <unordered_map>

void init()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

class ReadingManager 
{
public:
  void Read(const int&, const int&); 
  double Cheer(const int&) const;
 
private:
  std::unordered_map< int, int > m_person_pages;
  std::multiset< int > m_pages;
};

void ReadingManager::Read(const int& user_id, const int& page_count) 
{
  if ( m_person_pages.count( user_id ) )
    m_pages.erase( m_pages.find( m_person_pages[user_id] ) );
  
  m_person_pages[user_id] = page_count;
  m_pages.insert( page_count );
}

double ReadingManager::Cheer(const int& user_id) const
{
  const auto itUserPages = m_person_pages.find(user_id);
  if( itUserPages == m_person_pages.cend() )
    return {};

  if( m_person_pages.size() == 1 )
    return 1.0;
  
  const auto itLess = m_pages.lower_bound( itUserPages->second );
  return ( 1.0*std::distance(m_pages.cbegin(), itLess)/(m_person_pages.size() - 1) );
}

enum class QueryType
{
  READ,
  CHEER
};

class Parser
{
public:
  Parser( std::istream& is, std::ostream& os, ReadingManager& rm)
    : m_is {is}
    , m_os {os}
    , m_rm {rm}
  {}
  void Parse();
  void MakeQuery();
private:
  std::istream& m_is;
  std::ostream& m_os;
  ReadingManager m_rm;
  std::map< std::string, QueryType > m
  {
    { "READ", QueryType::READ },
    { "CHEER", QueryType::CHEER }
  };
};

void Parser::Parse()
{
  init();
  size_t query_count;
  m_is >> query_count;
  while( query_count-- )
    MakeQuery();
}

void Parser::MakeQuery()
{
  init();
  std::string query_type;
  m_is >> query_type;
  int user_id;
  m_is >> user_id;
  
  auto it_query = m.find(query_type);
  
  switch( it_query->second )
  {
    case QueryType::READ:
      int page_count;
      m_is >> page_count;
      m_rm.Read(user_id, page_count);
      break;

    case QueryType::CHEER:
      m_os << std::setprecision(6) << m_rm.Cheer(user_id) << "\n";
      break;
  }
}

int main() 
{
  init(); 
  ReadingManager manager;
  
  Parser pr( std::cin, std::cout, manager );
  pr.Parse();

  return 0;
}
