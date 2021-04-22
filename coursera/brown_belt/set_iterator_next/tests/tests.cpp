#include "gtest/gtest.h"
#include "node_builder.h"

#include <iostream>

TEST(Basic, Test1)
{
    NodeBuilder nb;

    Node *root = nb.CreateRoot(50);
    EXPECT_EQ(root->value, 50);

    Node *l = nb.CreateLeftSon(root, 2);
    Node *min = nb.CreateLeftSon(l, 1);
    Node *r = nb.CreateRightSon(l, 4);
    EXPECT_EQ(min->value, 1);
    EXPECT_EQ(r->parent->value, 2);

    nb.CreateLeftSon(r, 3);
    nb.CreateRightSon(r, 5);

    r = nb.CreateRightSon(root, 100);
    l = nb.CreateLeftSon(r, 90);
    nb.CreateRightSon(r, 101);

    nb.CreateLeftSon(l, 89);
    r = nb.CreateRightSon(l, 91);

    EXPECT_EQ(Next(l)->value, 91);
    EXPECT_EQ(Next(root)->value, 89);
    EXPECT_EQ(Next(min)->value, 2);
    EXPECT_EQ(Next(r)->value, 100);

    while (min)
    {
        std::cout << min->value << '\n';
        min = Next(min);
    }
}

TEST(Basic, RootOnly)
{
    NodeBuilder nb;
    Node *root = nb.CreateRoot(42);
    EXPECT_EQ(Next(root), nullptr);
};