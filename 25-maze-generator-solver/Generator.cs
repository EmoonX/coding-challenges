
Random rand = new();

for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
        int k = rand.Next(2);
        char c = (k == 0) ? ' ' : '█';
        Console.Write(c);
    }
    Console.WriteLine();
}
