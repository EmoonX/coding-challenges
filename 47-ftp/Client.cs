
void ReadCommand() {
    var input = Console.ReadLine()!.ToLower();
    // var methodName = char.ToUpper(input[0]) + input[1..];
    switch (input) {
        case "bye":
        case "quit":
            Commands.Bye();
            break;
        
    };
}

while (true) {
    Console.Write("ftp> ");
    ReadCommand();
}
