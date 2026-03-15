#include "dijkstra.h"
#include <raylib.h>
#include <queue>
#include <cmath>
void Dijkstra::build_size()
{
    adj.resize(size);
}

void Dijkstra::build_edge(int u, int v, int w)
{
    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
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