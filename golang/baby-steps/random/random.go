package random

import (
	"fmt"
)

type user struct {
	name string
	age  uint8
}

// Struct method
func (u user) greet() {
	fmt.Println("Hi, my name is", u.name)
}

func add(n1 float64, n2 float64) float64 {
	return n1 + n2
}

func fullName(firstName string, lastName string) string {
	return firstName + " " + lastName
}

func appendLastLetter(s string, times int) string {
	lastLetter := s[len(s)-1]

	for i := 0; i < times; i++ {
		s += string(lastLetter)
	}

	return s
}

// Interface
type Awesomizer interface {
	Awesomize() string
}

// types do *not* declare to implement interfaces
type Foo struct{}

// instead, types implicitly satisfy an interface if they implement all required methods
func (foo Foo) Awesomize() string {
	return "Awesome!"
}

func Run() {
	var message1 string = "Just a simple message!"
	message2 := "Just another simple message!"

	fmt.Println(message1, message2)

	// I can use the user struct with this map
	var pets = make(map[string]string)
	pets["dog"] = "No suitable for me"
	pets["cat"] = "Just perfect"
	delete(pets, "dog")

	fmt.Println(pets)

	name := "Luis Portillo"
	age := uint8(20)

	if age >= 18 {
		fmt.Println("You can pass!")
		newUser := user{
			name: name,
			age:  age,
		}

		fmt.Println(newUser.name)
		newUser.greet()
	}

	// I'm using this syntax cuz i don't want to add a condition
	for i := 0; ; i++ {
		if i == 3 {
			break
		}
		fmt.Println("GO!")
	}

	var friends [1]string
	friends[0] = "Cuervo"

	fruits := []string{"Apple", "Orange", "Pear", "Watermelon"}
	for i, fruit := range fruits {
		fmt.Printf("%v in index %v\n", fruit, i)
	}

	fmt.Println(add(2, 2))
	fmt.Println(fullName("Luis", "Portillo"))
	fmt.Println(appendLastLetter("ola", 3))
}
