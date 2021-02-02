#include "reading_manager.h"
#include <iomanip>
#include <iostream>
#include <utility>
#include <iterator>

#ifndef ETALON
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
  const auto& userPage = m_UsersPages[user_id];
  if( userPage == 0 )
    return {};
  
  if( m_Users.size() == 1 )
    return 1.0;
 
 size_t size {};
 for( size_t i = 1; i != userPage; ++i )
    size += m_PageUsers[i];

  return static_cast<double>(size)/static_cast<double>( m_Users.size() - 1 );
}
#endif
