package main

import (
	"fmt"
	"math/rand"
	"time"
	"unicode"
)

// Randomly return either `"HEADS"` or `"TAILS"`, with equal probability.
func CoinToss() string {
	var n = rand.Int() % 2
	if n == 0 {
		return "HEADS"
	}
	return "TAILS"
}

// Print given number of `.`s, waiting 1 second after each.
func PrintDotAndSleep(n uint) {
	for i := uint(0); i < n; i++ {
		fmt.Print(".")
		time.Sleep(time.Second)
	}
}

func main() {
	// Read user input
	var c rune
	for c != 'h' && c != 't' {
		var input string
		fmt.Print("Please choose Heads (h) or Tails (t): ")
		fmt.Scanln(&input)
		c = unicode.ToLower(rune(input[0]))
	}
	var option = "HEADS"
	if c == 't' {
		option = "TAILS"
	}
	fmt.Printf("> You chose %s.\n", option)

	// Toss coin and print result
	var result = CoinToss()
	fmt.Print("> The coin is tossed")
	PrintDotAndSleep(3)
	fmt.Printf("%s!", result)
	time.Sleep(time.Second)
	fmt.Println()
}
