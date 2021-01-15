#include "object_pool.h"
#include "gtest/gtest.h"

class ObjectPoolTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }
 ObjectPool<std::string> pool;
};

TEST_F( ObjectPoolTest, Test1 )
{
  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  EXPECT_EQ(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  EXPECT_EQ(*pool.Allocate(), "third");
  EXPECT_EQ(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

TEST_F( ObjectPoolTest, DeallocateThrowsException )
{
  bool IsException {false};
  try
  {
    std::string* p1 = new std::string;
    pool.Deallocate(p1);
  }
  catch(...)
  {
    IsException = true;
  }
  EXPECT_EQ( IsException, true );
}


