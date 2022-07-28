var s = Console.ReadLine();
var rev = (s != null) ? s.Reverse() : "";
foreach (var c in rev) {
    Console.Write(c);
}
Console.WriteLine();
