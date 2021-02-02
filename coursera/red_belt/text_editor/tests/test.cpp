#include "gtest/gtest.h"
#include "text_editor.h"
#include "profile.h"

#include <random>

TEST( TestEditing, Test1 )
{
  {
    Editor editor;
    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i)
      editor.Left();
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i)
      editor.Right();
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    EXPECT_EQ(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    EXPECT_EQ(editor.GetText(), "misprint");
  }
}


TEST( TestReverse, Test2 )
{
  Editor editor;

  const std::string text = "esreveR";
  for(char c : text) 
  {
    editor.Insert(c);
    editor.Left();
  }
  
  EXPECT_EQ(editor.GetText(), "Reverse");
}


TEST( TestNoText, Test3 )
{
  Editor editor;
  EXPECT_EQ(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  EXPECT_EQ(editor.GetText(), "");
}

TEST( TestEmptyBuffer, Test4 )
{
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  EXPECT_EQ(editor.GetText(), "example");
}

TEST( TestCut, Test5 )
{
	Editor editor;
	//1
	editor.Cut(10);
	editor.Insert('a');
	editor.Left();
	//2
	editor.Cut(1);
	EXPECT_EQ(editor.GetText(), "");
	editor.Paste();
	EXPECT_EQ(editor.GetText(), "a");
	//3
	editor.Cut(0);
	editor.Paste();
	EXPECT_EQ(editor.GetText(), "a");
	TypeText(editor, "bcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//4
	editor.Cut(10);
	EXPECT_EQ(editor.GetText(), "");
	editor.Paste();
	EXPECT_EQ(editor.GetText(), "abcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//5
	editor.Cut(5);
	EXPECT_EQ(editor.GetText(), "");
	editor.Paste();
	//6
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	editor.Cut(1);
	EXPECT_EQ(editor.GetText(), "bcde");
	editor.Right();
	editor.Cut(1);
	EXPECT_EQ(editor.GetText(), "bde");
	editor.Cut(1);
	editor.Cut(1);
	EXPECT_EQ(editor.GetText(), "b");
}

TEST( TestCopy, Test6 )
{
	Editor editor;
	//1
	editor.Copy(10);
	editor.Insert('a');
	editor.Paste();
	editor.Left();
	EXPECT_EQ(editor.GetText(), "a");
	//2
	editor.Copy(1);
	editor.Paste();
	EXPECT_EQ(editor.GetText(), "aa");//between a
    //3
	editor.Copy(0);
	editor.Paste();
	EXPECT_EQ(editor.GetText(), "aa");
	TypeText(editor, "bcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//4
	editor.Cut(10);
	EXPECT_EQ(editor.GetText(), "");
	editor.Paste();
	EXPECT_EQ(editor.GetText(), "abcdea");
}

TEST( TestCopyPasteLastChars, Test7 )
{
    Editor editor;
    TypeText(editor, "happy birthday");
    editor.Left();
    editor.Left();
    editor.Copy(5);
    editor.Paste();
    EXPECT_EQ(editor.GetText(), "happy birthdayay");
}

std::string random_string()
{
  mt19937 generator{random_device{}()};
  std::uniform_int_distribution<int> distribution{'a', 'z'};
  auto generate_len = 1'000'001;  
  std::string rand_str(generate_len, '\0');
  for(auto& dis: rand_str)
      dis = distribution(generator);
  return rand_str;
}

TEST( Insertion, Duration )
{
  Editor editor;
  std::string some_string = random_string();
  LOG_DURATION("Insertion operation");
  TypeText( editor, some_string );
}

TEST( Cut, Duration )
{
  Editor editor;
  std::string some_string = random_string();
  TypeText( editor, some_string );
  size_t numberOfQueries = 1'000'000;
  for(size_t i = 0; i < some_string.size(); ++i)
    editor.Left();
  LOG_DURATION("Cut operation");
  for( size_t i = 0; i != numberOfQueries; ++i )
    editor.Cut(1);
}

TEST( Copy, Duration )
{
  Editor editor;
  std::string some_string = random_string();
  TypeText( editor, some_string );
  size_t numberOfQueries = 1'000'000;
  for(size_t i = 0; i < some_string.size(); ++i)
    editor.Left();
  LOG_DURATION("Copy operation");
  for( size_t i = 0; i != numberOfQueries; ++i )
    editor.Copy(1);
}

TEST( CopyPaste, Duration )
{
  Editor editor;
  std::string some_string = random_string();
  TypeText( editor, some_string );
  size_t numberOfQueries = 1'000'000;
  for(size_t i = 0; i < some_string.size(); ++i)
    editor.Left();
  LOG_DURATION("CopyPaste operation");
  for( size_t i = 0; i != numberOfQueries; ++i )
  {
    editor.Copy(1);
    editor.Paste();
  }
}
