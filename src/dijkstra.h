#pragma once
#include <vector>
using namespace std;

struct edge
{
    int node, weight;
};

struct cmp
{
    bool operator()(edge u, edge v)
    {
        return u.weight > v.weight;
    }
};

class Dijkstra
{
    public:
    int size;
    vector<vector<edge>> adj;

    void build_size();
    void build_edge(int u, int v, int w);
    void implement(int sNode);
};
