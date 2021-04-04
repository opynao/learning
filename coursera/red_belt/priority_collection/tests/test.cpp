#include "gtest/gtest.h"
#include "priority_col.h"
#include "non_copy.h"

class PriorityCollectionTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }
  PriorityCollection<StringNonCopyable> prs;
  PriorityCollection<int> pri;
};

TEST_F( PriorityCollectionTest, BasicTest )
{
  PriorityCollection<StringNonCopyable> strings;
  strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);

  for (int i = 0; i < 2; ++i)
    strings.Promote(red_id);

  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    EXPECT_EQ(item.first, "red");
    EXPECT_EQ(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    EXPECT_EQ(item.first, "yellow");
    EXPECT_EQ(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    EXPECT_EQ(item.first, "white");
    EXPECT_EQ(item.second, 0);
  }
}

TEST_F( PriorityCollectionTest, AddNode )
{
  const auto a = pri.Add(1);
  const auto b = pri.Add(2);
  EXPECT_EQ( pri.Get( a ), 1 );
  EXPECT_EQ( pri.Get( b ), 2 );
  EXPECT_EQ( pri.IsValid( a ), true );
  EXPECT_EQ( pri.IsValid( b ), true );
  
  pri.Promote( a );
  EXPECT_EQ( pri.Get( a ), 1 );
  EXPECT_EQ( pri.IsValid( a ), true );
}

TEST_F( PriorityCollectionTest, AddRange )
{
  std::vector<StringNonCopyable> strings;
  strings.push_back("1");
  strings.push_back("2");
  strings.push_back("3");
  strings.push_back("4");
  std::vector< std::multiset<Node<StringNonCopyable>>::const_pointer > v_ids;
  v_ids.reserve(4);

  prs.Add( std::begin(strings), std::end(strings), std::back_inserter( v_ids ));
}

TEST_F( PriorityCollectionTest, AddEmptyRange )
{
  std::vector<int> v {};
  std::vector<int> v_copy {};
  std::vector< std::multiset<Node<int>>::const_pointer > v_ids;

  pri.Add( std::begin(v), std::end(v), std::back_inserter( v_ids ));
  
  std::vector<int> result;

  for( auto& id : v_ids )
  {
    EXPECT_EQ( pri.IsValid( id ), true );
    result.push_back( pri.Get( id ) );
  }
  
  EXPECT_EQ( result, v_copy );
}

TEST_F( PriorityCollectionTest, GetMax )
{
  std::vector<int> v { 1, 3, 2, 5 };
  std::vector< std::multiset<Node<int>>::const_pointer > v_ids;
  v_ids.reserve(4);

  pri.Add( std::begin(v), std::end(v), std::back_inserter( v_ids ));
 
  const auto& pr = pri.GetMax();
  EXPECT_EQ( pr.first, 5 );
  EXPECT_EQ( pr.second, 0 );

  pri.Promote( v_ids[1] );
  const auto& pr1 = pri.GetMax();
  EXPECT_EQ( pr1.first, 3 );
  EXPECT_EQ( pr1.second, 1 );

  pri.Promote( v_ids[2] );
  const auto& pr2 = pri.GetMax();
  EXPECT_EQ( pr2.first, 2 );
  EXPECT_EQ( pr2.second, 1 );
}

TEST_F( PriorityCollectionTest, PopMax )
{
  std::vector<int> v { 1, 3, 2, 5 };
  std::vector< std::multiset<Node<int>>::const_pointer > v_ids;
  v_ids.reserve(4);

  pri.Add( std::begin(v), std::end(v), std::back_inserter( v_ids ));
 
  const auto& pr = pri.PopMax();
  EXPECT_EQ( pr.first, 5 );
  EXPECT_EQ( pr.second, 0 );
  EXPECT_EQ( pri.IsValid( v_ids[3] ), false );

  pri.Promote( v_ids[1] );
  const auto& pr1 = pri.PopMax();
  EXPECT_EQ( pr1.first, 3 );
  EXPECT_EQ( pr1.second, 1 );
}

