#pragma once

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