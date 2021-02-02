#include "stack_vector.h"
#include "gtest/gtest.h"
#include "profile.h"


LOG_DURATION("total test");

TEST( TestConstruction, Test1 )
{
  StackVector<int, 10> v;
  EXPECT_EQ(v.Size(), 0u);
  EXPECT_EQ(v.Capacity(), 10u);

  StackVector<int, 8> u(5);
  EXPECT_EQ(u.Size(), 5u);
  EXPECT_EQ(u.Capacity(), 8u);

  bool IsException {false};
  try 
  {
    StackVector<int, 10> u(50);
  } 
  catch (std::invalid_argument&) 
  {
    IsException = true;
  } 
  catch (...) 
  {
  }
  EXPECT_EQ( IsException, true );
}

TEST( TestPushBack, Test2 )
{
  StackVector<int, 5> v;
  for (size_t i = 0; i < v.Capacity(); ++i)
    v.PushBack(i);
  
  bool IsException {false};
  try 
  {
    v.PushBack(0);
  } 
  catch (std::overflow_error&) 
  {
    IsException = true;
  } 
  catch (...) 
  {
  }
  EXPECT_EQ( IsException, true );
}

TEST( TestPopBack, Test3 ) 
{
  StackVector<int, 5> v;
  for (size_t i = 1; i <= v.Capacity(); ++i)
    v.PushBack(i);
  
  for (int i = v.Size(); i > 0; --i)
    EXPECT_EQ(v.PopBack(), i);

  bool IsException {false};
  try 
  {
    v.PopBack();
  } 
  catch (std::underflow_error&) 
  {
    IsException = true;
  } 
  catch (...) 
  {
  }
  EXPECT_EQ( IsException, true );
}


