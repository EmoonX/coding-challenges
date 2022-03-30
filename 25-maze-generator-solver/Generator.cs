using static Maze.PrintableChar;

partial class Maze {

    /// <summary>Randomly generates a new maze.</summary>
    public void Generate() {
        DrawStart();
        Build(1, 1);
        DrawExit();
    }

    /// <summary>Draws starting position.</summary>
    void DrawStart() {
        board[1, 0].type = Start;
        DrawOnScreen(1, 0, Start, color: 3);
    }

    /// <summary>Recursively builds maze from position (i, j).</summary>
    void Build(int i, int j) {
        if (i == 0 || i == m-1 || j == 0 || j == n-1) {
            // Ignore borders
            return;
        }
        // Avoid open spaces and (possibly) cycles/circuits
        Random rand = new();
        var countEmpty = (int i, int j)
                => (board[i, j] != Wall) ? 1 : 0;
        int countX = countEmpty(i  , j-1) + countEmpty(i,   j+1);
        int countY = countEmpty(i-1, j  ) + countEmpty(i+1, j  );
        if (countX + countY >= 2) {
            if (!allowCycles) {
                return;
            }
            if (countX * countY != 0 || rand.Next(32) > 0) {
                // Only allow (a handful of) same-direction connections
                return;
            }
        }
        // Avoid empty cells touching each other solely through diagonals
        var diagonals = new [] {(-1, -1), (-1, +1), (+1, -1), (+1, +1)};
        foreach (var diag in diagonals) {
            var (iTo, jTo) = (i + diag.Item1, j + diag.Item2);
            if (board[iTo, jTo] == Wall) {
                continue;
            }
            int count = 0;
            count += countEmpty(i  , j  ) + countEmpty(iTo, jTo);
            count += countEmpty(i  , jTo) + countEmpty(iTo, j  );
            if (count == 1) {
                return;
            }
        }
        // Draw empty space over solid cell
        board[i, j].type = Empty;
        DrawOnScreen(i, j, Empty, sleepTime: 1);

        // Randomly choose a direction and continue recursively towards it
        var directions = new [] {(0, -1), (0, +1), (-1, 0), (+1, 0)};
        directions = directions.OrderBy(x => rand.Next()).ToArray();
        foreach (var dir in directions) {
            var (iTo, jTo) = (i + dir.Item1, j + dir.Item2);
            if (board[iTo, jTo] == Wall) {
                Build(iTo, jTo);
            }
        }
    }

    /// <summary>Draws exit on an available spot.</summary>
    void DrawExit() {
        for (int i = m-2; i > 0; i--) {
            if (board[i, n-2] == Empty) {
                board[i, n-2].type = Exit;
                DrawOnScreen(i, n-2, Exit, color: 3);
                break;
            }
        }
    }
}

class Generator {
    static void Main() {

        int m = 30;
        int n = 90;
        bool allowCycles = true;
        Maze maze = new(m, n, allowCycles);
        maze.Generate();
        
        maze.BuildGraph();
        var path = maze.Solve();
        maze.DrawPath(path);
    }
}
