using static Maze.PrintableChar;

partial class Maze {
    /// <summary>Available chars to be printed on screen.</summary>
    public enum PrintableChar
    {
        Empty     = ' ',
        Wall      = '█',
        Start     = 'S',
        Exit      = 'E',
        PathUp    = '↑',
        PathDown  = '↓',
        PathLeft  = '←',
        PathRight = '→',
        NewLine   = '\n'
    }

    /// <summary>Maze cell encapsulated as a graph node.</summary>
    public class Node {
        /// <summary>Vertical cell offset.</summary>
        public int i;
        /// <summary>Horizontal cell offset.</summary>
        public int j;

        /// <summary>Cell type, represented by a printable char.</summary>
        public PrintableChar type;

        /// <summary>Node's edge list (i.e neighbor nodes).</summary>
        public List<Node> edges = new();

        /// <summary>BFS-calculated distance from starting node.</summary>
        public int dist = -1;

        /// <summary>Basic constructor.</summary>
        public Node(int _i, int _j, PrintableChar _type)
            => (i, j, type) = (_i, _j, _type);

        /// <summary>Allows direct char comparisons.</summary>
        public static implicit operator PrintableChar(Node node)
            => node.type;
    }

    /// <summary>Maze height.</summary>
    public int m;
    /// <summary>Maze width.</summary>
    public int n;

    /// <summary>Board matrix representing maze arrangement.</summary>
    public Node[,] board;

    /// <summary>Clears console and draws base maze (no empty cells).</summary>
    public void DrawBase() {
        Console.Clear();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                Console.Write((char) Wall);
            }
            Console.WriteLine();
        }
    }

    /// <summary>Draws char on screen position <c>(i, j)</c>.</summary>
    /// <param name="sleepTime">Miliseconds to wait after drawing.</param>
    /// <param name="color">ANSI color code index (0 for none).</param>
    public static void DrawOnScreen(
        int i, int j, PrintableChar c,
        int sleepTime = 0, int color = 0
    ) {
        const char EscCode = (char) 0x1B;
        string format = "{0}";
        if (color != 0) {
            format = string.Format("\x1b[33;1m\x1b[3{0}m{1}\x1b[0m",
                color, "{0}");
        }
        string s = string.Format(format, ((char) c).ToString());
        Console.Write("{0}[{1};{2}H", EscCode, i+1, j+1);
        Console.Write(s);
        Console.Write("{0}[{1};{2}H", EscCode, i+1, j+1);
        Thread.Sleep(sleepTime);
    }
}
