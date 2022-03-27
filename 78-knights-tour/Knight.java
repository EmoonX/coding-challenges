import java.util.ArrayList;

class Knight {

    static class Node {
        int i, j;
        ArrayList<Edge> edges;

        public Node(int i, int j) {
            this.i = i;
            this.j = j;
            edges = new ArrayList<>();
        }
    }

    static class Edge {
        int iTo, jTo;

        public Edge(int iTo, int jTo) {
            this.iTo = iTo;
            this.jTo = jTo;
        }
    }

    static final int[] iMoves = {-2, -2, -1, -1, +1, +1, +2, +2};
    static final int[] jMoves = {-1, +1, -2, +2, -2, +2, -1, +1};

    static Node[][] graph;

    static void buildGraph(int n) {
        graph = new Node[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph[i][j] = new Node(i, j);
                Node node = graph[i][j];
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

    public static void main(String[] args) {
        System.out.println("Hello, world!");
        int n = 5;
        buildGraph(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.printf("(%d, %d) ->", i, j);
                for (Edge edge : graph[i][j].edges) {
                    System.out.printf(" (%d, %d)", edge.iTo, edge.jTo);
                }
                System.out.println();
            }
        } 
    }
}
