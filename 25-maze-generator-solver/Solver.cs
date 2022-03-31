using static Maze.PrintableChar;

partial class Maze {

    /// <summary>Builds graph connecting neighbor empty cells.</summary>
    public void BuildGraph() {
        var directions = new [] {(0, +1), (+1, 0)};
        foreach (Node u in board) {
            if (u == Wall) {
                continue;
            }
            foreach (var (iDelta, jDelta) in directions) {
                var (iTo, jTo) = (u.i + iDelta, u.j + jDelta);
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
        var pQueue = new PriorityQueue<Node, int>(new [] {(r, 0)});
        Node last = r;
        while (pQueue.Count > 0) {
            Node u = pQueue.Dequeue();
            foreach (Node v in u.edges) {
                if (v.dist == -1) {
                    v.dist = u.dist + 1;
                    pQueue.Enqueue(v, v.dist);
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
                Node v = path[k+1];
                var (di, dj) = (v.i - u.i, v.j - u.j);
                PrintableChar c =
                    (di == 0) ?
                        ((dj == -1) ? PathLeft : PathRight) :
                        ((di == -1) ? PathUp   : PathDown);
                DrawOnScreen(
                    u.i, u.j, c,
                    sleepTime: 5000 / path.Length, color: 1
                );
            }
        }
        DrawOnScreen(m+1, 0, NewLine);
    }
}
