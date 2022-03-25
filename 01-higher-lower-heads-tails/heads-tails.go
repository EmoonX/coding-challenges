package main

import (
	"fmt"
	"unicode"
)

func main() {
	var option rune
	for option != 'h' && option != 't' {
		var input string
		fmt.Print("Please choose Heads (h) or Tails (t): ")
		fmt.Scanln(&input)
		option = unicode.ToLower(rune(input[0]))
	}
	var s = "HEADS"
	if option == 't' {
		s = "TAILS"
	}
	fmt.Printf("> You chose %s.\n", s)
}
