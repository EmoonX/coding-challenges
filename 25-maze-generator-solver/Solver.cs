using static Maze.PrintableChar;

partial class Maze {

    /// <summary>Builds graph connecting neighbor empty cells.</summary>
    public void BuildGraph() {
        var directions = new [] {(0, +1), (+1, 0)};
        foreach (Node u in board) {
            if (u == Wall) {
                continue;
            }
            foreach (var dir in directions) {
                var (iTo, jTo) = (u.i + dir.Item1, u.j + dir.Item2);
                Node v = board[iTo, jTo];
                if (v != Wall) {
                    u.edges.Add(v);
                    v.edges.Add(u);
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

    /// <summary>Draws path arrows (from node sequence) on screen.</summary>
    public void DrawPath(Node[] path) {
        for (int k = 0; k < path.Length; k++) {
            Node u = path[k];
            if (u == Empty) {
                PrintableChar c;
                Node v = path[k+1];                
                var (di, dj) = (v.i - u.i, v.j - u.j);
                if (di == 0) {
                    c = (dj == -1) ? PathLeft : PathRight;
                } else {
                    c = (di == -1) ? PathUp : PathDown;
                }
                DrawOnScreen(u.i, u.j, c, sleepTime: 5, color: 1);
            }
        }
        DrawOnScreen(m+1, 0, NewLine);
    }
}
