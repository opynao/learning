#include "translator.h"
#include <tuple>

void Translator::Add(const std::string_view& source, const std::string_view& target)
{
  forward_translation[GetCache(source)] = target;
  backward_translation[GetCache(target)] = source;
}

std::string_view Translator::TranslateForward(const std::string_view& source) const
{
  return Translate( forward_translation, source );
}

std::string_view Translator::TranslateBackward(const std::string_view& target) const
{
  return Translate( backward_translation, target );
}

std::string_view Translator::Translate( const Translator_t& m, const std::string_view& str ) const
{
  auto it = m.find(str);
  if( it == m.cend() )
    return {""};
  return it->second;
}

std::string_view Translator::GetCache( const std::string_view& str )
{
  std::set<std::string>::iterator it;
  std::tie( it, std::ignore ) = cache.emplace(str);
  return {*it};
}

