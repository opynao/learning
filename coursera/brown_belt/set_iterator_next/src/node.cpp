#include "node.h"

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