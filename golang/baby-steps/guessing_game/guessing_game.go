package guessing_game

import (
	"fmt"
	"os"
	"os/exec"
	"runtime"
	"strings"
	"time"
)

func guessingGame() {
	guess := strings.ToLower("cuervo")
	attempts := 3

	fmt.Println("Starting guessing game!")
	fmt.Printf("You have %d attempts >///<\n\n", attempts)

	for attempt := 1; attempt <= attempts; attempt++ {
		fmt.Print("Enter your guess: ")
		input := getUserInput()

		if input == guess {
			fmt.Println("\nYou win! uwu")
			return
		} else {
			fmt.Printf("Wrong! (You have %d remaining attempts)\n", attempts-attempt)
			if input == "raven" || input == "crow" {
				fmt.Println("But really close! It is on spanish >///<")
			}
		}
	}

	fmt.Println("\nYou lose unu")
}

func Run() {
	for {
		guessingGame()
		fmt.Println("\nTry again? (y for Yes, any other for No)")
		fmt.Print("> ")
		input := getUserInput()

		if input == "y" {
			clearConsole()
			fmt.Println("A little clue: It is my favorite Animal!")
			fmt.Println()
			continue
		}
		break
	}
	fmt.Println("\nThanks for playing! uwu")
	time.Sleep(time.Second * 3)
}

func getUserInput() string {
	var input string
	fmt.Scanln(&input)
	return strings.ToLower(input)
}

func clearConsole() {
	var cmd *exec.Cmd

	switch runtime.GOOS {
	case "linux", "darwin":
		cmd = exec.Command("clear")
	case "windows":
		cmd = exec.Command("cmd", "/c", "cls")
	}

	cmd.Stdout = os.Stdout
	cmd.Run()
}
