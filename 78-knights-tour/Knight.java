import java.util.ArrayList;

class Knight {

    /** Graph node representing board square. */
    static class Node {
        int i, j;
        ArrayList<Edge> edges;
        boolean visited = false;

        public Node(int i, int j) {
            this.i = i;
            this.j = j;
            edges = new ArrayList<>();
        }
    }

    /** Graph edge representing valid knight move. */
    static class Edge {
        int iTo, jTo;

        public Edge(int iTo, int jTo) {
            this.iTo = iTo;
            this.jTo = jTo;
        }
    }

    /** Horizontal deltas for knight moves. */
    static final int[] iMoves = {-2, -2, -1, -1, +1, +1, +2, +2};

    /** Vertical deltas for knight moves. */
    static final int[] jMoves = {-1, +1, -2, +2, -2, +2, -1, +1};

    /** Board size (both width and height). */
    static int n;

    /** Node 2D matrix representing nxn chess board. */
    static Node[][] board;

    /**
     * Builds graph matrix for a <b>nxn</b> board.
     * <p>
     * Method iterates over board nodes and adds edges
     * corresponding to reachable squares when playing
     * a valid knight move from said position.
     */
    static void buildGraph(int _n) {
        n = _n;
        board = new Node[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = new Node(i, j);
                Node node = board[i][j];
                for (int k = 0; k < 8; k++) {
                    int iTo = i + iMoves[k];
                    int jTo = j + jMoves[k];
                    if (iTo < 0 || iTo >= n || jTo < 0 || jTo >= n) {
                        continue;
                    }
                    Edge edge = new Edge(iTo, jTo);
                    node.edges.add(edge);
                }
            }
        }
    }

    /**
     * Searches for a Knight's tour starting at node {@code r}.
     * <p>
     * A DFS is ran, traversing through unvisited nodes, which are
     * marked as visited and added to the list. {@code tour} contains
     * a valid path from initial call's node to the current one.
     * <p>
     * Search ends successfully if all nodes are added to the list;
     * otherwise, there are no more valid moves (i.e reachable nodes).
     * All visited nodes are unmarked as so at recursion's end (save
     * from the very first one, which must be unmarked by the caller).
     */
    static boolean findTour(Node r, ArrayList<Node> tour) {
        r.visited = true;
        tour.add(r);
        if (tour.size() == n*n) {
            return true;
        }
        for (Edge edge : r.edges) {
            Node v = board[edge.iTo][edge.jTo];
            if (!v.visited) {
                boolean found = findTour(v, tour);
                v.visited = false;
                if (found) { 
                    return true;
                }
            }
        }
        tour.remove(tour.size() - 1);
        return false;
    }

    public static void main(String[] args) {
        int n = 5;
        buildGraph(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Node r = board[i][j];
                ArrayList<Node> tour = new ArrayList<>();
                System.out.printf("(%d, %d) ->", i, j);
                boolean found = findTour(r, tour);
                r.visited = false;
                if (found) {
                    for (Node v : tour) {
                        System.out.printf(" (%d, %d)", v.i, v.j);
                    }
                    System.out.println();
                } else {
                    System.out.println(" Not found...");
                }
            }
        } 
    }
}
