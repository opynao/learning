#include "text_editor.h"

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
  return { str_.begin(), str_.end() };  
}

size_t Editor::GetRealTokenSize(size_t tokens) 
{
  LOGF;
  if(  str_.size() < current_position_ + tokens )
    tokens = str_.size() - current_position_;
  return tokens;
}

void Editor::Copy(size_t tokens)
{
  LOGF;
  clipboard_.clear();
  std::copy_n( current_it_, GetRealTokenSize( tokens ), std::back_inserter( clipboard_ ) );
}

void Editor::Paste()
{
  LOGF;
  str_.insert( current_it_, clipboard_.begin(), clipboard_.end() );
  current_position_ += clipboard_.size();
}

void TypeText(Editor& editor, const std::string& text) 
{
  for(char c : text) 
    editor.Insert(c);
}
