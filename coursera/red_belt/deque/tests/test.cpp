#include "deque.h"
#include "gtest/gtest.h"


class DequeTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    dq.PushBack(1);
    dq.PushBack(2);
    dq.PushFront(3);
    dq.PushFront(4);
    dq.PushBack(5);
    dq.PushFront(6);
    dq_PushBackEmpty.PushFront(1);
    dq_PushBackEmpty.PushFront(2);
    dq_PushBackEmpty.PushFront(3);
    dq_PushFrontEmpty.PushBack(1);
    dq_PushFrontEmpty.PushBack(2);
    dq_PushFrontEmpty.PushBack(3);
  }
    Deque<int> dq;
    Deque<int> dq_PushBackEmpty;
    Deque<int> dq_PushFrontEmpty;
};


TEST_F( DequeTest, Size )
{
    EXPECT_EQ( dq.Size(), 6u);
    EXPECT_EQ( dq.Empty(), false );
}

TEST( Deque, Empty )
{
  Deque<int> dq;
  EXPECT_EQ( dq.Empty(), true );
}

TEST_F( DequeTest, Operators )
{
  EXPECT_EQ( dq[0], 6 );
  EXPECT_EQ( dq[1], 4 );
  EXPECT_EQ( dq[2], 3 );
  EXPECT_EQ( dq[3], 1 );
  EXPECT_EQ( dq[4], 2 );
  EXPECT_EQ( dq[5], 5 );
  EXPECT_EQ( dq.At(0), 6 );
  EXPECT_EQ( dq.At(1), 4 );
  EXPECT_EQ( dq.At(2), 3 );
  EXPECT_EQ( dq.At(3), 1 );
  EXPECT_EQ( dq.At(4), 2 );
  EXPECT_EQ( dq.At(5), 5 );
}

TEST_F ( DequeTest, At_Throws_Exception )
{
  bool IsException {false};
  try
  {
    dq.At(6);
  }
  catch(...)
  {
    IsException = true;
  }
  EXPECT_EQ( IsException, true );
}

TEST_F( DequeTest, Back_IfPushBackVectorIsEmpty )
{
  EXPECT_EQ( dq_PushBackEmpty.Back(), 1);
}

TEST_F( DequeTest, Front_IfPushFrontVectorIsEmpty )
{
  EXPECT_EQ( dq_PushFrontEmpty.Front(), 1);
  dq_PushFrontEmpty.PushFront(2);
  EXPECT_EQ( dq_PushFrontEmpty.Front(), 2 );
}
