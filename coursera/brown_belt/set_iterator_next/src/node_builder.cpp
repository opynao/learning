#include "node_builder.h"

#include <cassert>

Node *NodeBuilder::CreateRoot(int value)
{
    nodes.emplace_back(value, nullptr);
    return &nodes.back();
}

Node *NodeBuilder::CreateLeftSon(Node *me, int value)
{
    assert(me->left == nullptr);
    nodes.emplace_back(value, me);
    me->left = &nodes.back();
    return me->left;
}

Node *NodeBuilder::CreateRightSon(Node *me, int value)
{
    assert(me->right == nullptr);
    nodes.emplace_back(value, me);
    me->right = &nodes.back();
    return me->right;
}
