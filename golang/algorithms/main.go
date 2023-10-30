package main

import "fmt"

func fib(n uint, memo map[uint]uint) uint {
	if n <= 1 {
		return n
	}

	if v, ok := memo[n]; ok {
		return v
	}

	result := fib(n-1, memo) + fib(n-2, memo)
	memo[n] = result
	return result
}

func main() {
	cache := make(map[uint]uint)
	result := fib(50, cache)
	fmt.Println(result)
}
