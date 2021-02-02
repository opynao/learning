#include <string>
#include <string_view>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#define LOGF //std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl
#include <list>

class Editor
{
 public:
  Editor();

  void Left();
  
  void Right();
  
  void Insert(char token);
 
  void Cut(size_t tokens = 1);
  
  void Copy(size_t tokens = 1);
  
  void Paste();
  
  std::string GetText() const; 

private:
  size_t GetRealTokenSize(size_t tokens);

private:
  std::list< char > str_ {};
  std::list< char >::iterator current_it_;
  std::list< char > clipboard_ {};
  size_t current_position_ {};
};

void TypeText(Editor& editor, const std::string& text);


Editor::Editor()
  : current_it_ { str_.begin() }
{}

void Editor::Left()
{
  LOGF;
  if( current_it_ == str_.cbegin() )
    return;
  --current_it_;
  --current_position_;
}

void Editor::Right()
{
  LOGF;
  if( current_it_ == str_.cend() )
    return;
  ++current_it_;
  ++current_position_;
}

void Editor::Insert(char token)
{
  LOGF;
  current_it_ = str_.insert( current_it_, token );
  ++current_it_;
  ++current_position_;
}

void Editor::Cut(size_t tokens)
{
  LOGF;
  if( str_.empty() )
    return;
  
  tokens = GetRealTokenSize(tokens);
  
  clipboard_.clear();
  
  auto other = current_it_;
  std::advance(current_it_,tokens);
  clipboard_.splice( clipboard_.begin(), str_, other, std::next( other, tokens ) );
}


std::string Editor::GetText() const 
{ 
  LOGF;
  std::string s = "";
  s.reserve( str_.size() );
  std::copy( str_.begin(), str_.end(), std::back_inserter(s) );
  return s;  
}

size_t Editor::GetRealTokenSize(size_t tokens) 
{
/*  size_t distance {};
  for( auto it = current_it_; it != str_.end(); ++it )
    ++distance;
  if( distance < tokens )
    tokens = distance;
*/  LOGF;
  if(  str_.size() < current_position_ + tokens )
    tokens = str_.size() - current_position_;
  return tokens;
}

void Editor::Copy(size_t tokens)
{
  LOGF;
  if( str_.empty() )
    return;
  
  clipboard_.clear();
  std::copy_n( current_it_, GetRealTokenSize( tokens ), std::back_inserter( clipboard_ ) );
}

void Editor::Paste()
{
  LOGF;
  if( clipboard_.empty() )
    return;
  
  current_it_ = str_.insert( current_it_, clipboard_.begin(), clipboard_.end() );
  std::advance( current_it_, clipboard_.size() );
  current_position_ += clipboard_.size();
}

void TypeText(Editor& editor, const std::string& text) 
{
  for(char c : text) 
    editor.Insert(c);
}

int main() {
  Editor editor;
  const string text = "hello, world";
  for (char c : text) {
    editor.Insert(c);
  }
  // Текущее состояние редактора: `hello, world|`
  for (size_t i = 0; i < text.size(); ++i) {
    editor.Left();
  }
  // Текущее состояние редактора: `|hello, world`
  editor.Cut(7);
  // Текущее состояние редактора: `|world`
  // в буфере обмена находится текст `hello, `
  for (size_t i = 0; i < 5; ++i) {
    editor.Right();
  }
  // Текущее состояние редактора: `world|`
  editor.Insert(',');
  editor.Insert(' ');
  // Текущее состояние редактора: `world, |`
  editor.Paste();
  // Текущее состояние редактора: `world, hello, |`
  editor.Left();
  editor.Left();
  //Текущее состояние редактора: `world, hello|, `
  editor.Cut(3); // Будут вырезаны 2 символа
  // Текущее состояние редактора: `world, hello|`
  cout << editor.GetText();
}
