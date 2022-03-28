import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;

class Knight {

    /** Graph node representing board square. */
    static class Node {
        int i, j;
        ArrayList<Edge> edges;
        boolean visited = false;
        Integer numMoves;

        /** Builds a node with given position and empty edge list. */
        Node(int i, int j) {
            this.i = i;
            this.j = j;
            edges = new ArrayList<>();
        }

        /** Either increments or decrements valid move
            counter on reachable nodes. */
        void updateNeighborNumMoves(int delta) {
            for (Edge edge : edges) {
                Node v = board[edge.iTo][edge.jTo];
                v.numMoves += delta;
            }
        }

        /** Sorts edges on increasing order of
            {@code numMoves} of node they point to. */
        void sortEdges() {
            Collections.sort(edges, new Comparator<Edge>() {
                public int compare(Edge e1, Edge e2) {
                    Node u = board[e1.iTo][e1.jTo];
                    Node v = board[e2.iTo][e2.jTo];
                    return u.numMoves.compareTo(v.numMoves);
                }
            });
        }
    }

    /** Graph edge representing valid knight move. */
    static class Edge {
        int iTo, jTo;

        /** Builds edge pointing to position {@code (iTo, jTo)} */
        Edge(int iTo, int jTo) {
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

    /** Whether the tour to search should be closed or not. */
    static boolean closed;

    /** Whether Warnsdorff's heuristic should be used or not. */
    static boolean useWarnsdorff;

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
                // Shuffle edge list for randomness :)
                Collections.shuffle(node.edges);
            }
        }
    }

    /** Resets graph nodes: unvisited and all moves available. */
    static void resetGraph() {
        for (Node[] row: board) {
            for (Node node: row) {
                node.visited = false;
                node.numMoves = node.edges.size();
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
     */
    static boolean findTour(Node r, ArrayList<Node> tour) {
        r.visited = true;
        tour.add(r);
        if (tour.size() == n*n) {
            return true;
        }
        r.updateNeighborNumMoves(-1);
        if (closed) {
            Node first = tour.get(0);
            if (first.numMoves == 0) {
                cleanUpSearch(r, tour);
                return false;
            }
        }
        if (useWarnsdorff) {
            r.sortEdges();
        }
        for (Edge edge : r.edges) {
            Node v = board[edge.iTo][edge.jTo];
            if (v.visited) {
                continue;
            }
            boolean found = findTour(v, tour);
            if (found) { 
                return true;
            }
        }
        cleanUpSearch(r, tour);
        return false;
    }

    /** Cleanup procedures to be done before
        {@code return false} in {@code findTour()} */
    static void cleanUpSearch(Node r, ArrayList<Node> tour) {
        r.visited = false;
        tour.remove(tour.size() - 1);
        r.updateNeighborNumMoves(+1);
    }

    /**
     * Visually and progressively draws tour on screen.
     * <p>
     * {@code "S"} indicates starting position, {@code "."}
     * unvisited squares, {@code "#"} already visited squares,
     * and {@code "E"} where the knight is currently on.
     */
    static void drawTour(ArrayList<Node> tour)
            throws InterruptedException {

        System.out.print("\033\143");
        System.out.printf("[Knight's tour] (%s)\n\n",
            closed ? "closed" : "open");

        // Draw empty board and borders
        for (int i = -1; i <= n; i++) {
            System.out.print("   ");
            for (int j = -1; j <= n; j++) {
                char c = '.';
                if (i == -1 || i == n || j == -1 || j == n) {
                    if (i == j || i*j == -n) {
                        c = '+';
                    } else if (i == -1 || i == n) {
                        c = '-';
                    } else {
                        c = '|';
                    }
                }
                System.out.print(c);
            }
            System.out.println();
        }
        // Print knight positions as it moves across the board,
        // waiting a little bit (with `sleep()`) between each move
        // (extra iteration at the end if closed, to insert '!')
        Node last = null;
        for (int k = 0; k <= n*n; k++) {
            if (k == n*n && !closed) {
                break;
            }
            if (k > 1) {
                int xLast = last.i + 4;
                int yLast = last.j + 5;
                moveCursorAndPrint(xLast, yLast, '#', false);
            }
            Node node = tour.get(k % (n*n));
            int x = node.i + 4;
            int y = node.j + 5;
            char c = (k == 0) ? 'S' : ((k == n*n) ? '!' : 'E');
            moveCursorAndPrint(x, y, c, true);
            Thread.sleep(20);
            last = node;
        }
        moveCursorAndPrint(n + 6, 0, '\n', true);
    }

    /** Move cursor to position ({@code x}, {@code y}) on screen
        and print char {@code c} on it (w/ optional highlight). */
    static void moveCursorAndPrint(
            int x, int y, char c, boolean highlight) {
        final char ESC_CODE = 0x1B;
        String format = highlight ?
            "\033[33;1m\033[41m%c\033[0m" : "\033[;1m%c\033[0m";
        System.out.printf("%c[%d;%df", ESC_CODE, x, y);
        System.out.printf(format, c);
        System.out.printf("%c[%d;%df", ESC_CODE, x, y);
    }

    public static void main(String[] args)
            throws InterruptedException {
        int n = 16;
        closed = true;
        useWarnsdorff = true;
        buildGraph(n);

        boolean found = false;
        Random rand = new Random();
        for (int count = 0; count < 100; count++) {
            int i = rand.nextInt(n);
            int j = rand.nextInt(n);
            Node r = board[i][j];
            ArrayList<Node> tour = new ArrayList<>();
            System.out.printf("(%d, %d) -> ", i, j);
            resetGraph();
            found = findTour(r, tour);
            if (found) {
                System.out.println("Found!");
                Thread.sleep(1200);
                drawTour(tour);
                return;
            } else {
                System.out.println("Not found...");
            }
        }
        System.out.printf("No available tours for %dx%d... :(\n", n, n);
    }
}
