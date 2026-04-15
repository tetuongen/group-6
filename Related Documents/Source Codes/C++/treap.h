#include<chrono>
#include<random>
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
    void clear(Node* t);
    void insert(int key);
    void erase(int key);

    ~HeapTree()
    {
        clear(root);
    }
};

