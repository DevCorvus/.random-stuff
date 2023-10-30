package iters

import "fmt"

var people = []string{"Luis", "Luisa"}

func Run() {
	for i := 0; i < len(people); i++ {
		if people[i] == "Luis" {
			fmt.Println("uwu")
		} else {
			fmt.Println("awa")
		}
	}
}
