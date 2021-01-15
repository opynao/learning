#include <map>
#include <iomanip>
#include <iostream>
#include <utility>
#include <iterator>
#include <string>
#include <array>
#include <set>

void init()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

class ReadingManager 
{
public:
  using UserID = size_t;
  using PageNumber = size_t;
  using UserCount = size_t;
public:
  void Read(int user_id, int page_count); 
  double Cheer(int user_id) const;
private:
  std::array< PageNumber, 100'001 > m_UsersPages;
  std::array< UserCount, 1001 > m_PageUsers;
  std::set< UserID > m_Users;
};

void ReadingManager::Read(int user_id, int page_count) 
{
  m_Users.insert(user_id);
 
  if( !page_count )
    return;
  
  auto& userPage = m_UsersPages[ user_id ];
  
  if( userPage )
    --m_PageUsers[ userPage ];
      
  userPage = page_count;
  
  ++m_PageUsers[ userPage ];
}

double ReadingManager::Cheer(int user_id) const
{
  const auto& userPage = m_UsersPages[ user_id ];

  if( !userPage )
    return 0.0;

  if( m_Users.size() == 1 )
    return 1.0;
 
 size_t size { 0 };

 for( size_t i = 1; i != userPage; ++i )
    size += m_PageUsers[i];

  return static_cast<double>(size)/static_cast<double>( m_Users.size() - 1);
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
  ReadingManager& m_rm;
  std::map< std::string, QueryType > m
  {
    { "READ", QueryType::READ },
    { "CHEER", QueryType::CHEER }
  };
};

void Parser::Parse()
{
  size_t query_count;
  m_is >> query_count;
  while( query_count-- )
    MakeQuery();
}

void Parser::MakeQuery()
{
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
