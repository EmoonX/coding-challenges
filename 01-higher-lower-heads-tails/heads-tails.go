package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"time"
	"unicode"
)

// Possible round outcomes
const (
	Win int = iota
	Lose
	Exit
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
func PrintDotAndSleep(n int) {
	for i := 0; i < n; i++ {
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
func PlayRound(points int) int {
	// Get user's coin side choice
	var text = "! Please choose Heads (h), Tails (t) or exit (e)"
	var options = map[rune]bool{'h': true, 't': true, 'e': true}
	var c = GetAnswer(text, options)
	if c == 'e' {
		// Exit (e) was chosen
		return Exit
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
		return Win
	} else {
		fmt.Print("> You lose...\n")
		return Lose
	}
}

func main() {
	fmt.Println("**********************")
	fmt.Println("*** HEADS or TAILS ***")
	fmt.Println("**********************")
	fmt.Println()

	// Scan player's name
	var player string
	for {
		fmt.Print("! Please input your name: ")
		fmt.Scan(&player)
		if len(player) > 0 {
			break
		}
	}
	fmt.Printf("> Welcome, %s!\n", Boldify(player))
	time.Sleep(time.Second)

	// Read player's high score from file, creating it if nonexistent
	var highScore = 0
	var filename = fmt.Sprintf("high-scores/%s-heads.sco", player)
	file, err := os.Open(filename)
	if err != nil {
		os.WriteFile(filename, []byte{'0'}, 0644)
	} else {
		fmt.Fscan(file, &highScore)
	}
	fmt.Printf("> Your high score is: %s\n",
		Boldify("%d point(s)", highScore))
	time.Sleep(time.Second)

	// Main game loop
	var score = 0
	for {
		fmt.Printf("\n# Current score: %s\n", Boldify("%d point(s)", score))
		var roundPoints = int(math.Max(float64(2*score), 1))
		var result = PlayRound(roundPoints)
		if result == Exit {
			fmt.Println()
			break
		}
		time.Sleep(time.Second)
		fmt.Println()
		if result == Lose {
			score = 0
			break
		}
		score = roundPoints
	}
	// Show final score and check for new high
	var newHigh = false
	if score > highScore {
		newHigh = true
		highScore = score
	}
	fmt.Printf("# Final score: %s\n", Boldify("%d point(s)", score))
	fmt.Printf("#  High score: %s", Boldify("%d point(s)", highScore))
	if newHigh {
		// Write new high score to file
		fmt.Println(" (NEW HIGH)")
		fmt.Print("> Congratulations! You got a new high score!")
		file, err = os.OpenFile(filename, os.O_WRONLY, 0644)
		fmt.Fprint(file, score)
	}
	fmt.Println()
	time.Sleep(2 * time.Second)
	fmt.Println()
}
