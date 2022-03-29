using static Maze.PrintableChar;

partial class Maze {

    /// <summary>Builds graph connecting neighbor empty cells.</summary>
    public void BuildGraph() {
        var directions = new [] {(0, +1), (+1, 0)};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                Node u = board[i, j];
                if (u == Wall) {
                    continue;
                }
                foreach (var dir in directions) {
                    var (iTo, jTo) = (i + dir.Item1, j + dir.Item2);
                    Node v = board[iTo, jTo];
                    if (v != Wall) {
                        u.edges.Add(v);
                        v.edges.Add(u);
                    }
                }
            }
        }
    }

    /// <summary>
    /// Solves maze, calculating shortest path from start to exit.
    /// </summary>
    /// <returns>Array containing ordered nodes for shortest path.</returns>
    public Node[] Solve() {
        Node r = board[1, 0];
        r.dist = 0;
        PriorityQueue<Node, int> pq = new(new [] {(r, 0)});
        Node last = r;
        while (pq.Count > 0) {
            Node u = pq.Dequeue();
            foreach (Node v in u.edges) {
                if (v.dist == -1) {
                    v.dist = u.dist + 1;
                    pq.Enqueue(v, v.dist);
                }
            }
            if (u == Exit) {
                last = u;
                break;
            }
        }
        var path = new Node[last.dist + 1];
        path[last.dist] = last;
        for (int k = last.dist - 1; k >= 0; k--) {
            foreach (Node u in last.edges) {
                if (u.dist == last.dist - 1) {
                    last = u;
                    break;
                }
            }
            path[k] = last;
        }
        return path;
    }

    /// <summary>Draws path (from node positions) on screen.</summary>
    public void DrawPath(Node[] path) {
        foreach (Node v in path) {
            if (v == Empty) {
                DrawOnScreen(v.i, v.j, PrintableChar.Path);
            }
        }
        DrawOnScreen(m+1, 0, NewLine);
    }
}
