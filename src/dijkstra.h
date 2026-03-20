#pragma once
#include <vector>
#include <raylib.h>
using namespace std;

struct edge
{
    int node,weight;
};

struct cmp
{
    bool operator()(edge u, edge v)
    {
        return u.weight > v.weight;
    }
};

struct Dijkstra
{
    int size;
    vector<vector<edge>> adj;

    void build_size();
    void build_edge(int u, int v, int w);
    void implement(int sNode);
    void randomGraph(int n);
};

struct Node
{
    Vector2 pos;
    int d;
    int state;
};

struct UI
{
    vector<Node> node;
    float w,h,cellW,cellH,lim,radius;
    UI()
    {
        w = 800;
        h = 600;
        cellW = 40;
        cellH = 30;
        lim = 20;
        radius = 30;
    }
    void placeNode(Dijkstra* &logic);
    void drawNode(Dijkstra* &logic);
};