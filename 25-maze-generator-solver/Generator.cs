using static Maze.PrintableChar;

partial class Maze {
    public Maze(int m, int n) {
        this.m = m;
        this.n = n;
        board = new Node[m, n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i, j] = new(i, j, Wall);
            }
        }
        DrawBase();

        board[1, 0].type = Start;
        DrawOnScreen(1, 0, Start, color: 3);
        var (i0, j0) = (1, 1);
        Generate(i0, j0);

        for (int i = m-2; i > 0; i--) {
            if (board[i, n-2] == Empty) {
                board[i, n-2].type = Exit;
                DrawOnScreen(i, n-2, Exit, color: 3);
                break;
            }
        }
    }

    void Generate(int i, int j) {
        if (i == 0 || i == m-1 || j == 0 || j == n-1) {
            return;
        }
        var countEmpty = (int i, int j) => (board[i, j] != Wall) ? 1 : 0;
        int count = 0;
        count += countEmpty(i  , j-1) + countEmpty(i,   j+1);
        count += countEmpty(i-1, j  ) + countEmpty(i+1, j  );
        if (count >= 2) {
            return;
        }
        var diagonals = new [] {(-1, -1), (-1, +1), (+1, -1), (+1, +1)};
        foreach (var diag in diagonals) {
            var (iTo, jTo) = (i + diag.Item1, j + diag.Item2);
            if (board[iTo, jTo] == Wall) {
                continue;
            }
            count = 0;
            count += countEmpty(i  , j  ) + countEmpty(iTo, jTo);
            count += countEmpty(i  , jTo) + countEmpty(iTo, j  );
            if (count == 1) {
                return;
            }
        }
        board[i, j].type = Empty;
        DrawOnScreen(i, j, Empty, sleepTime: 20);

        Random rand = new();
        var directions = new [] {(0, -1), (0, +1), (-1, 0), (+1, 0)};
        directions = directions.OrderBy(x => rand.Next()).ToArray();
        foreach (var dir in directions) {
            var (iTo, jTo) = (i + dir.Item1, j + dir.Item2);
            if (board[iTo, jTo] == Wall) {
                Generate(iTo, jTo);
            }
        }
    }
}

class Generator {
    static void Main() {

        int m = 30;
        int n = 90;
        Maze maze = new(m, n);
        
        maze.BuildGraph();
        var path = maze.Solve();
        maze.DrawPath(path);
    }
}
