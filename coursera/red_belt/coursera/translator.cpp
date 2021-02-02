#include <string_view>
#include <string>
#include <map>
#include <algorithm>
#include <set>
#include <tuple>

class Translator 
{
public:
  using Translator_t = std::map< std::string_view, std::string_view >;

public:  
  void Add(const std::string_view& source, const std::string_view& target);
  std::string_view TranslateForward(const std::string_view& source) const;
  std::string_view TranslateBackward(const std::string_view& target) const;

private:
  std::string_view GetCache( const std::string_view& str );
  std::string_view Translate( const Translator_t& m, const std::string_view& str ) const;

private:
  Translator_t forward_translation {};
  Translator_t backward_translation {};
  std::set<std::string> cache;
};

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

int main()
{
  return 0;
}
