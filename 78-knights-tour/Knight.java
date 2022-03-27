import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

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
                // Shuffle edge list for randomness :)
                Collections.shuffle(node.edges);
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
            if (v.visited) {
                continue;
            }
            boolean found = findTour(v, tour);
            v.visited = false;
            if (found) { 
                return true;
            }
        }
        tour.remove(tour.size() - 1);
        return false;
    }

    /** Move cursor to position ({@code x}, {@code y})
        on screen and print char {@code c} on it. */
    static void moveCursorAndPrint(int x, int y, char c) {
        final char ESC_CODE = 0x1B;
        System.out.printf("%c[%d;%df", ESC_CODE, x, y);
        System.out.print(c);
        System.out.printf("%c[%d;%df", ESC_CODE, x, y);
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
        System.out.println("[Knight's tour]\n");

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
        Node last = null;
        for (int k = 0; k < n*n; k++) {
            if (k > 1) {
                int xLast = last.i + 4;
                int yLast = last.j + 5;
                moveCursorAndPrint(xLast, yLast, '#');
            }
            Node node = tour.get(k);
            int x = node.i + 4;
            int y = node.j + 5;
            char c = (k == 0) ? 'S' : 'E';
            moveCursorAndPrint(x, y, c);
            Thread.sleep(400);
            last = node;
        }
        moveCursorAndPrint(n + 6, 0, '\n');
    }

    public static void main(String[] args)
            throws InterruptedException {
        int n = 5;
        buildGraph(n);

        boolean found = false;
        Random rand = new Random();
        for (int count = 0; count < 100; count++) {
            int i = rand.nextInt(n);
            int j = rand.nextInt(n);
            Node r = board[i][j];
            ArrayList<Node> tour = new ArrayList<>();
            System.out.printf("(%d, %d) -> ", i, j);
            found = findTour(r, tour);
            r.visited = false;
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
