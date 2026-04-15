#include "treap.h"
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void HeapTree::split(Node* t, int key, Node*& l, Node*& r)
{
    if (!t)
    {
        l = r = nullptr;
        return;
    } else
    if (t->key <= key)
    {
        split(t->r, key, t->r, r);
        l = t;
    } else
    {
        split(t->l, key, l, t->l);
        r = t;
    }
}

Node* HeapTree::merge(Node* l, Node* r)
{
    if (!l || !r)
    {
        return l?l:r;
    }
    if (l->prior > r->prior)
    {
        l->r = merge(l->r, r);
        return l;
    } else
    {
        r->l = merge(l, r->l);
        return r;
    }
}

bool HeapTree::find(Node* t, int key)
{
    if (!t) return 0;
    if (t->key == key) return 1;
    if (key < t->key) return find(t->l, key);
    return find(t->r, key);
}

void HeapTree::clear(Node* t)
{
    if (!t) return;
    clear(t->l);
    clear(t->r);
    delete t;
}

void HeapTree::insert(int key)
{
    if (find(root, key)) return;
    Node* l, *r;
    split(root, key, l, r);
    Node* node = new Node(key);
    root = merge(merge(l, node), r);
}



void HeapTree::erase(int key)
{
    Node* l, *r, *mid;
    split(root, key, l, r);
    split(l, key-1, l, mid);
    clear(mid);
    root = merge(l, r);
}

