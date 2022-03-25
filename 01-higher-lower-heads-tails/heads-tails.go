package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
	"unicode"
)

// Show input dialog and scan user's input until
// any of the options are entered.
//
// Return user's answer.
func GetAnswer(text string, options map[rune]bool) rune {
	var c rune
	for !options[c] {
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

// Apply ANSI bold style to string, formatting it first.
func Boldify(format_str string, a ...interface{}) string {
	var str = fmt.Sprintf(format_str, a...)
	return fmt.Sprintf("\u001b[37;1m%s\u001b[0m", str)
}

// Play a round worth given points.
//
// Return boolean representing whether guess was right or not.
func PlayRound(points uint) bool {
	// Get user's coin side choice
	var text = "! Please choose Heads (h), Tails (t) or exit (e)"
	var options = map[rune]bool{'h': true, 't': true, 'e': true}
	var c = GetAnswer(text, options)
	if c == 'e' {
		// Exit (e) was chosen
		return false
	}
	var option = "HEADS"
	if c == 't' {
		option = "TAILS"
	}
	fmt.Printf("\n> You chose %s.\n", Boldify(option))

	// Toss coin and print result
	var outcome = CoinToss()
	fmt.Print("> The coin is tossed")
	PrintDotAndSleep(3)
	fmt.Printf("%s!", Boldify(outcome))
	time.Sleep(time.Second)
	fmt.Println()

	// Show result (match or not)
	if outcome == option {
		fmt.Print("> You win!")
		return true
	} else {
		fmt.Print("> You lose...\n")
		return false
	}
}

func main() {
	fmt.Println("**********************")
	fmt.Println("*** HEADS or TAILS ***")
	fmt.Println("**********************")

	// Main game loop
	var score uint = 0
	for {
		fmt.Printf("\n# Current score: %s\n", Boldify("%d point(s)", score))
		var round_points = uint(math.Max(float64(2*score), 1))
		var ok = PlayRound(round_points)
		time.Sleep(time.Second)
		fmt.Println()
		if !ok {
			break
		}
		score = round_points
	}
	fmt.Printf("# Final score: %s\n\n", Boldify("%d point(s)", score))
}
