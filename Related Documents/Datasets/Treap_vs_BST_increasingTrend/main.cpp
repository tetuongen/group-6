#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
using namespace std::chrono;
using namespace std;
extern mt19937 rng;

struct Node
{
    int key, prior;
    Node* l, *r;
    Node(int k)
    {
        key = k;
        prior = rng();
        l = r = nullptr;
    }
};


struct HeapTree
{
    Node* root;
    HeapTree()
    {
        root = nullptr;
    }

    void split(Node* t, int key, Node*& l, Node*& r);
    Node* merge(Node* l, Node* r);
    bool find(Node* t, int key);
    void insert(int key);
    void erase(int key);
    void clear(Node* t);

    ~HeapTree()
    {
        clear(root);
    }
};

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

void HeapTree::insert(int key)
{
    if (find(root, key)) return;
    Node* l, *r;
    split(root, key, l, r);
    Node* node = new Node(key);
    root = merge(merge(l, node), r);
}

void HeapTree::clear(Node* t)
{
    if (!t) return;
    clear(t->l);
    clear(t->r);
    delete t;
}

void HeapTree::erase(int key)
{
    Node* l, *r, *mid;
    split(root, key, l, r);
    split(l, key-1, l, mid);
    clear(mid);
    root = merge(l, r);
}


int main()
{
    // TREAP SOLUTION
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    auto start = chrono::high_resolution_clock::now();

    HeapTree* myTree = new HeapTree;

    // Enter the number of queries
    int q;
    cin>>q;

    while(q--)
    {
        // Enter the type of operations:
        // "Find"/ "Insert"/ "Erase" + a value
        string s;
        int val;
        cin>>s>>val;

        if (s == "Find")
        {
            bool c = myTree->find(myTree->root, val);
            if (c) cout<<"Exist"; else cout<<"Non-exist";
            cout<<'\n';
        }
        else if (s == "Insert") myTree->insert(val);
        else if (s == "Erase") myTree->erase(val);

    }

    delete myTree;

    auto end = chrono::high_resolution_clock::now();

    auto duration = duration_cast<chrono::microseconds>(end-start).count();
    double ms = duration/1000.0;
    cerr<<fixed<<setprecision(5)<<ms<<" ms\n";

}
