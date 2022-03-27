#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

#define pair pair<int, int>
#define INF 2e9

using namespace std;

// Weighted directed graph edge.
struct Edge {
    int from, to;
    int cost;
};

// Graph node.
// 
// Holds list of edges and min distance throughout algorithm.
struct Node {
    int v;
    vector<Edge> edges;
    int dist = INF;
};

// Run Dijkstra's algorithm starting from given node.
//
// Resulting graph nodes will contain respective
// minimum calculated distance (from starting node).
void dijkstra(auto &nodes, int start)
{
    // Create (min) priority queue with (distance, node) pairs
    priority_queue<pair, vector<pair>, greater<pair>> pq;
    pq.push({0, start});
    nodes[start].dist = 0;

    // Run algorithm until queue is empty
    while (not pq.empty()) {
        // Get min item from queue
        int u = pq.top().second;
        pq.pop();
        printf("! Picked up node #%d (%d)\n", u, nodes[u].dist);

        // Iterate over node edges
        for (auto& edge : nodes[u].edges) {
            int dist = nodes[u].dist + edge.cost;
            int v = edge.to;
            if (dist < nodes[v].dist) {
                // New dist is smaller, so update it and add node to queue
                nodes[v].dist = dist;
                pq.push({dist, v});
                printf("> Node #%d has now dist %d\n", v, dist);
            }
        }
    }
}

int main()
{
    // Read number of nodes and edges
    int n, m;
    cin >> n >> m;

    // Build node vector from weighted edges (both directions)
    vector<Node> nodes(n+1);
    while (m--) {
        int u, v, p;
        cin >> u >> v >> p;
        Edge edge = {u, v, p};
        Edge rev = {v, u, p};
        nodes[u].edges.push_back(edge);
        nodes[v].edges.push_back(rev);
    }
    // Read start node and run Dijkstra's algo on it
    int start;
    cin >> start;
    dijkstra(nodes, start);

    // Print final distances
    puts("\nDistances from starting node:");
    for (int v = 1; v <= n; v++) {
        printf("#%d to #%d: %2d\n", start, v, nodes[v].dist);
    }
}
