#include "dijkstra.h"
#include <raylib.h>
#include <queue>
#include <cmath>
#include <random>
#include <algorithm>

void Dijkstra::build_size()
{
    adj.resize(size);
}

void Dijkstra::build_edge(int u, int v, int w)
{
    adj[u].push_back({v,w});
}

void Dijkstra::implement(int sNode)
{
    vector<int> d;
    d.resize(size);
    for (int i=0;i<size;i++) d[i] = INT_MAX;

    priority_queue<edge,vector<edge>,cmp> q;

    d[sNode] = 0;
    q.push({sNode,0});

    while(q.size())
    {
        edge u = q.top();
        q.pop();
        if (u.weight > d[u.node]) continue;

        for (edge v: adj[u.node])
        {
            if (d[v.node] > d[u.node] + v.weight)
            {
                d[v.node] = d[u.node] + v.weight;
                q.push({v.node, d[v.node]});
            }
        }
    }

}

int random(int l, int r)
{
    static mt19937 gen(random_device{}());
    return uniform_int_distribution<>(l,r)(gen);
}

void shufflePosition(vector<Vector2> &contain)
{
    random_device rd;
    mt19937 gen(rd());
    shuffle(contain.begin(),contain.end(),gen);
}

string convert(int w)
{
    if (w<1e9)
    {
        if (!w) return "0";

        string s = "";
        while(w>0) s = char('0' + w%10) + s, w/=10;
        return s;
    }

    return "INF";
}

void Dijkstra::randomGraph(int n)
{
    size = n;
    build_size();
    int edge = random(n,n*2);
    for (int i=0;i<edge;i++)
    {
        int u = random(0,n-1);
        int v = random(0,n-1);
        while(u==v)
        {
            v = random(0,n-1);
        }
        int w = random(1,50);
        build_edge(u,v,w);
    }
}

void UI::placeNode(Dijkstra* &logic)
{
    node.resize(logic->size);
    vector<Vector2> pos;

    for (int i=1;i<=lim;i++) for (int j=1;j<=lim;j++) pos.push_back({i*cellW,j*cellH});

    shufflePosition(pos);

    for (int i=0;i<logic->size;i++)
    {
        node[i] = {pos[i],1000000000,0};
    }

}

void UI::drawNode(Dijkstra* &logic)
{

    for (int u=0;u<logic->size;u++)
    {
        for (edge v: logic->adj[u])
        {
            Vector2 posU = node[u].pos;
            Vector2 posV = node[v.node].pos;

            DrawLine(posU.x, posU.y, posV.x, posV.y, BLACK);

            Vector2 midpoint = {(posU.x+posV.x)/2, (posU.y+posV.y)/2};
            string s = convert(v.weight);
            const char* d = s.c_str();
            DrawText(d, midpoint.x, midpoint.y, 20, BLACK);
        }
    }

    for (int i=0;i<logic->size;i++)
    {
        Vector2 pos = node[i].pos;
        DrawCircle(pos.x, pos.y, radius, WHITE);
        DrawCircle(pos.x, pos.y, radius, {120,120,120,225});
        //DrawCircleLines(pos.x, pos.y, radius, BLACK);

        string s = convert(i);
        const char* c1 = s.c_str();
        DrawText(c1, pos.x-7, pos.y-14, 30, BLACK);

        s = convert(node[i].d);
        const char* c2 = s.c_str();
        DrawText(c2, pos.x-radius-3, pos.y-radius-3, 20, BLACK);

    }

}