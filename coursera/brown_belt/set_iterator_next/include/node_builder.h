#pragma once

#include <deque>

#include "node.h"

class NodeBuilder
{
public:
    Node *CreateRoot(int value);

    Node *CreateLeftSon(Node *me, int value);

    Node *CreateRightSon(Node *me, int value);

private:
    std::deque<Node> nodes;
};