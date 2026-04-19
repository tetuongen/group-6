#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Node
{
    int key;
    Node *l, *r;
    Node(int k)
    {
        key = k;
        l = r = nullptr;
    }
};

struct BST
{
    Node* root;
    BST()
    {
        root = nullptr;
    }

    void insert(Node*& t, int key);
    bool find(Node* t, int key);
    Node* getMin(Node* t);
    void erase(Node*& t, int key);
    void clear(Node* t);

    ~BST()
    {
        clear(root);
    }
};

void BST::insert(Node*& t, int key)
{
    if (!t)
    {
        t = new Node(key);
        return;
    }
    if (key == t->key) return;
    if (key<t->key) insert(t->l, key);
    else insert(t->r, key);
}

bool BST::find(Node* t, int key)
{
    if (!t) return 0;
    if (key == t->key) return 1;
    if (key<t->key) return find(t->l, key);
    else return find(t->r, key);
}

Node* BST::getMin(Node* t)
{
    while (t->l) t = t->l;
    return t;
}

void BST::erase(Node*& t, int key)
{
    if (!t) return;

    if (key < t->key) erase(t->l, key);
    else if (key > t->key) erase(t->r, key);
    else
    {
        if (!t->l)
        {
            Node* tmp = t;
            delete tmp;
            t = t->r;
        } else if (!t->r)
        {
            Node* tmp = t;
            delete tmp;
            t = t->l;
        } else
        {
            Node* succ = getMin(t->r);
            t->key = succ->key;
            erase(t->r, succ->key);
        }
    }
}

void BST::clear(Node* t)
{
    if (!t) return;
    clear(t->l);
    clear(t->r);
    delete t;
}

int main()
{
    // NAIVE SOLUTION
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    auto start = chrono::high_resolution_clock::now();
    BST* myTree = new BST;

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
        else if (s == "Insert") myTree->insert(myTree->root, val);
        else if (s == "Erase") myTree->erase(myTree->root, val);

    }

    delete myTree;

    auto end = chrono::high_resolution_clock::now();

    auto duration = duration_cast<chrono::microseconds>(end-start).count();
    double ms = duration/1000.0;
    cerr<<fixed<<setprecision(5)<<ms<<" ms\n";

}
