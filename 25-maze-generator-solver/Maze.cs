partial class Maze {

    public class Node { }

    /// <summary>Empty cell char.</summary>
    const char EMPTY = ' ';
    /// <summary>Wall char.</summary>
    const char WALL = '█';

    /// <summary>Maze height.</summary>
    public int m;
    /// <summary>Maze width.</summary>
    public int n;

    /// <summary>Board matrix representing maze arrangement.</summary>
    public char[,] board;

    /// <summary>
    /// Clears console and draws base maze (no empty cells).
    /// </summary>
    public void DrawBase() {
        Console.Clear();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                Console.Write(WALL);
            }
            Console.WriteLine();
        }
    }

    /// <summary>
    /// Draws char <c>c</c> on the screen position of cell <c>(i, j)</c>.
    /// </summary>
    public static void DrawOnCell(char c, int i, int j) {
        const char ESC_CODE = (char) 0x1B;
        Console.Write("{0}[{1};{2}H", ESC_CODE, i+1, j+1);
        Console.Write(c);
        Console.Write("{0}[{1};{2}H", ESC_CODE, i+1, j+1);
    }
}
