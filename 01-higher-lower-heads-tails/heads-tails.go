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
		if len(input) > 0 {
			c = unicode.ToLower(rune(input[0]))
		}
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
func Boldify(formatStr string, a ...interface{}) string {
	var str = fmt.Sprintf(formatStr, a...)
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
	fmt.Println()

	// Get player's name and their high score
	var player string
	var highScore uint = 0
	for {
		fmt.Print("! Please input your name: ")
		fmt.Scanf("%s", &player)
		if len(player) > 0 {
			break
		}
	}
	fmt.Printf("> Welcome, %s!\n", Boldify(player))
	time.Sleep(time.Second)
	fmt.Printf("> Your high score is: %s\n", Boldify("%d points", 0))
	time.Sleep(time.Second)

	// Main game loop
	var score uint = 0
	for {
		fmt.Printf("\n# Current score: %s\n", Boldify("%d point(s)", score))
		var roundPoints = uint(math.Max(float64(2*score), 1))
		var ok = PlayRound(roundPoints)
		time.Sleep(time.Second)
		fmt.Println()
		if !ok {
			break
		}
		score = roundPoints
	}
	// Show final score and check for new high
	var newHigh = false
	if score > highScore {
		highScore = score
		newHigh = true
	}
	fmt.Printf("# Final score: %s\n", Boldify("%d point(s)", score))
	fmt.Printf("#  High score: %s", Boldify("%d point(s)", score))
	if newHigh {
		fmt.Print(" (NEW HIGH!)")
	}
	fmt.Print("\n\n")
}
