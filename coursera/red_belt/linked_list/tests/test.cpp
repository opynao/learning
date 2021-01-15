#include "gtest/gtest.h"
#include "linked_list.h"
#include <string>

class LinkedListTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }
  LinkedList<int> list;
};

TEST_F( LinkedListTest, PushFront )
{
  list.PushFront(1);
  EXPECT_EQ(list.GetHead()->value, 1);
  list.PushFront(2);
  EXPECT_EQ(list.GetHead()->value, 2);
  list.PushFront(3);
  EXPECT_EQ(list.GetHead()->value, 3);

  const std::vector<int> expected = {3, 2, 1};
  EXPECT_EQ(ToVector(list), expected);
}

TEST( LinkedList, InsertAfter ) 
{
  LinkedList<std::string> list;

  list.PushFront("a");
  auto head = list.GetHead();
  EXPECT_NE( head, nullptr );
  EXPECT_EQ(head->value, "a");

  list.InsertAfter(head, "b");
  const std::vector<std::string> expected1 = {"a", "b"};
  EXPECT_EQ(ToVector(list), expected1);

  list.InsertAfter(head, "c");
  const std::vector<std::string> expected2 = {"a", "c", "b"};
  EXPECT_EQ(ToVector(list), expected2);
}

TEST_F( LinkedListTest, InsertAfterEqualToPushFront )
{
  LinkedList<int>::Node* node_insert_after = nullptr;
  list.InsertAfter( node_insert_after, 1 );
  list.InsertAfter( list.GetHead(), 2 );
  std::vector<int> expected { 1, 2 };
  EXPECT_EQ( ToVector(list), expected);
}

TEST_F( LinkedListTest, RemoveAfter ) 
{
  for (int i = 1; i <= 5; ++i)
    list.PushFront(i);

  const std::vector<int> expected = {5, 4, 3, 2, 1};
  EXPECT_EQ(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head); // удаляем 3
  list.RemoveAfter(next_to_head); // удаляем 2

  const std::vector<int> expected1 = {5, 4, 1};
  EXPECT_EQ(ToVector(list), expected1);

  while (list.GetHead()->next) 
    list.RemoveAfter(list.GetHead());
  
  EXPECT_EQ(list.GetHead()->value, 5);
}

TEST_F( LinkedListTest, PopFrontListIsEmpty )
{
  list.PopFront();
  EXPECT_EQ( list.GetHead(), nullptr );
}

TEST_F( LinkedListTest, PopFront ) 
{
  for (int i = 1; i <= 5; ++i)
    list.PushFront(i);
  
  for (int i = 1; i <= 5; ++i)
    list.PopFront();
  EXPECT_EQ(list.GetHead(), nullptr);
}

TEST_F( LinkedListTest, RemoveAfterNodeIsNullPtr )
{
  list.PushFront(1);
  LinkedList<int>::Node* node_to_remove = nullptr;
  list.RemoveAfter(node_to_remove);
  EXPECT_EQ(list.GetHead(), nullptr);
}

TEST_F( LinkedListTest, RemoveAfterNodeNextIsNullPtr )
{
  list.PushFront(1);
  list.RemoveAfter( list.GetHead() );
  std::vector<int> expected { 1 };
  EXPECT_EQ( ToVector(list), expected);
}
