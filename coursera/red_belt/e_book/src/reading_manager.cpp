#include "reading_manager.h"
#include <iomanip>
#include <iostream>
#include <utility>
#include <iterator>

void ReadingManager::Read(int user_id, int page_count) 
{
  if ( m_UsersPages.count( user_id ) )
    m_Pages.erase( m_Pages.find( m_UsersPages[user_id] ) );
  
  m_UsersPages[user_id] = page_count;
  m_Pages.insert( page_count );
}

double ReadingManager::Cheer(int user_id) const
{
  const auto itUserPages = m_UsersPages.find(user_id);
  if( itUserPages == m_UsersPages.cend() )
    return {};

  if( m_UsersPages.size() == 1 )
    return 1.0;
  
  const auto itLess = m_Pages.lower_bound( itUserPages->second );
  return ( std::distance(m_Pages.cbegin(), itLess)/static_cast<double>(m_UsersPages.size() - 1) );
}
