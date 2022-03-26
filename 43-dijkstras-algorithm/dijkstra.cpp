#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

#define INF 2e9

using namespace std;

struct Edge {
    int from, to;
    int cost;
};

struct Node {
    int v;
    vector<Edge> edges;
    int dist = INF;
};

void dijkstra(auto &nodes, int start) {
    auto cmp = [nodes](int u, int v) {
        return nodes[u].dist < nodes[v].dist;
    };
    nodes[start].dist = 0;
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    pq.push(start);
    while (not pq.empty()) {
        int u = pq.top();
        pq.pop();
        for (auto& edge : nodes[u].edges) {
            int dist = nodes[u].dist + edge.cost;
            int v = edge.to;
            if (dist < nodes[v].dist) {
                nodes[v].dist = dist;
                pq.push(v);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Node> nodes(n+1);
    while (m--) {
        int u, v, p;
        cin >> u >> v >> p;

        Edge edge = {u, v, p};
        nodes[u].edges.push_back(edge);
    }
    int start;
    cin >> start;
    dijkstra(nodes, start);

    puts("Distance from starting node:");
    for (int v = 1; v <= n; v++) {
        printf("#%d to #%d: %2d\n", start, v, nodes[v].dist);
    }
}
