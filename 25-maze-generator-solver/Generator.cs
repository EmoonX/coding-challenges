
partial class Maze {
    public Maze(int m, int n) {
        this.m = m;
        this.n = n;

        Random rand = new();
        board = new Node[m, n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int k = rand.Next(2);
                char c = (k == 0) ? ' ' : '█';
                board[i, j] = new(c);
            }
        }
    }
}

class Generator {
    static void Main() {

        int m = 20;
        int n = 60;
        Maze maze = new(m, n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c = maze.board[i,j].c;
                Console.Write(c);
            }
            Console.WriteLine();
        }
    }
}
