using static Maze.PrintableChar;

partial class Maze {
    /// <summary>Available chars to be printed on screen.</summary>
    public enum PrintableChar
    {
        Empty   = ' ',
        Wall    = '█',
        Start   = 'S',
        Exit    = 'E',
        Path    = '@',
        NewLine = '\n'
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
    public static void DrawOnScreen(int i, int j, PrintableChar c) {
        const char EscCode = (char) 0x1B;
        Console.Write("{0}[{1};{2}H", EscCode, i+1, j+1);
        Console.Write((char) c);
        Console.Write("{0}[{1};{2}H", EscCode, i+1, j+1);
        Thread.Sleep(10);
    }
}
