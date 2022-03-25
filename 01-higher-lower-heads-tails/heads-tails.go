package main

import (
	"fmt"
	"math/rand"
	"time"
	"unicode"
)

// Show input dialog and scan user's input until
// either `op1`` or `op2` are entered.
//
// Return user's answer.
func GetAnswer(text string, op1 rune, op2 rune) rune {
	var c rune
	for c != op1 && c != op2 {
		var input string
		fmt.Printf("%s: ", text)
		fmt.Scanln(&input)
		c = unicode.ToLower(rune(input[0]))
	}
	return c
}

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

// Run main game loop.
func Loop(points uint) {
	// Get user's coin side choice
	var text = "! Please choose Heads (h) or Tails (t)"
	var c = GetAnswer(text, 'h', 't')
	var option = "HEADS"
	if c == 't' {
		option = "TAILS"
	}
	fmt.Printf("\n> You chose %s.\n", option)

	// Toss coin and print result
	var outcome = CoinToss()
	fmt.Print("> The coin is tossed")
	PrintDotAndSleep(3)
	fmt.Printf("%s!", outcome)
	time.Sleep(time.Second)
	fmt.Println()

	// Show result (match or not)
	if outcome == option {
		fmt.Println("\n> You win!")
		fmt.Printf("# Current score: %d\n", points)
	} else {
		fmt.Println("\n> You lose...")
	}
}

func main() {
	Loop(1)
	fmt.Println()
}
