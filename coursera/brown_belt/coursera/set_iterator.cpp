#include <deque>
#include <cassert>

using namespace std;

struct Node
{
    Node(int v, Node *p)
        : value(v), parent(p)
    {
    }

    int value;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent;
};

Node *Next(Node *me);

Node *Minimum(Node *me);

Node *Next([[maybe_unused]] Node *me)
{
    if (me->right != nullptr)
        return Minimum(me->right);

    auto p = me->parent;
    while (p != nullptr && me == p->right)
    {
        me = p;
        p = p->parent;
    }
    return p;
}

Node *Minimum(Node *me)
{
    while (me->left != nullptr)
        me = me->left;
    return me;
}

class NodeBuilder
{
public:
    Node *CreateRoot(int value);

    Node *CreateLeftSon(Node *me, int value);

    Node *CreateRightSon(Node *me, int value);

private:
    std::deque<Node> nodes;
};

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

int main()
{
    return 0;
}