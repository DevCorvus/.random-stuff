package main

import (
	"fmt"
	"learning/guessing_game"
	"learning/iters"
	"learning/random"
)

func main() {
	random.Run()
	guessing_game.Run()
	iters.Run()

	var prints []func()

	for i := 0; i <= 3; i++ {
		i := i
		prints = append(prints, func() { fmt.Println(i) })
	}

	for _, print := range prints {
		print()
	}
}
