package main

import "fmt"

func main() {
	var input string
	fmt.Print("Please choose Heads (h) or Tails (t): ")
	fmt.Scanln(&input)
	var option byte = input[0]
	fmt.Printf("%c\n", option)
}
