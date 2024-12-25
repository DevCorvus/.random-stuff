package main

import (
	"fmt"
	"math"

	"sudoku-solver/stack"
)

// My first approach
type Sudoku [][]uint8

type Position struct {
	y, x uint8
}

type Limit struct {
	y, x [2]uint8
}

func (s Sudoku) getCell(pos *Position) uint8 {
	return s[pos.y][pos.x]
}

func (s Sudoku) setCell(pos *Position, value uint8) {
	s[pos.y][pos.x] = value
}

var subgridLimits = []Limit{
	{y: [2]uint8{0, 2}, x: [2]uint8{0, 2}},
	{y: [2]uint8{0, 2}, x: [2]uint8{3, 5}},
	{y: [2]uint8{0, 2}, x: [2]uint8{6, 8}},
	{y: [2]uint8{3, 5}, x: [2]uint8{0, 2}},
	{y: [2]uint8{3, 5}, x: [2]uint8{3, 5}},
	{y: [2]uint8{3, 5}, x: [2]uint8{6, 8}},
	{y: [2]uint8{6, 8}, x: [2]uint8{0, 2}},
	{y: [2]uint8{6, 8}, x: [2]uint8{3, 5}},
	{y: [2]uint8{6, 8}, x: [2]uint8{6, 8}},
}

func (s *Sudoku) getSubgridLimits(pos *Position) *Limit {
	for _, limit := range subgridLimits {
		minY := limit.y[0]
		maxY := limit.y[1]

		minX := limit.x[0]
		maxX := limit.x[1]

		if pos.y >= minY && pos.y <= maxY && pos.x >= minX && pos.x <= maxX {
			return &limit
		}
	}

	panic("No limits")
}

func (s *Sudoku) getFixedSubgridPositions(pos *Position) []Position {
	limit := s.getSubgridLimits(pos)

	minY := limit.y[0]
	maxY := limit.y[1]

	minX := limit.x[0]
	maxX := limit.x[1]

	out := []Position{}

	for y := minY; y < maxY+1; y++ {
		for x := minX; x < maxX+1; x++ {
			if y != pos.y || x != pos.x {
				out = append(out, Position{y, x})
			}
		}
	}

	return out

}

func (s *Sudoku) getSubgridPositions(pos *Position) []Position {
	minY := uint8(math.Floor(float64(pos.y/3)) * 3)
	maxY := uint8(math.Floor(float64(pos.y/3))*3 + 3)

	minX := uint8(math.Floor(float64(pos.x/3)) * 3)
	maxX := uint8(math.Floor(float64(pos.x/3))*3 + 3)

	out := []Position{}

	for y := minY; y < maxY; y++ {
		for x := minX; x < maxX; x++ {
			out = append(out, Position{y, x})
		}
	}

	return out
}

func (s *Sudoku) isSubgridSafe(pos *Position, value uint8) bool {
	positions := s.getSubgridPositions(pos)

	for _, pos := range positions {
		cell := s.getCell(&pos)

		if cell == value {
			return false
		}
	}

	return true
}

func (s Sudoku) isColumnSafe(pos *Position, value uint8) bool {
	var y uint8

	for y = 0; y < 9; y++ {
		if y != pos.y {
			cell := s[y][pos.x]

			if cell == value {
				return false
			}
		}
	}

	return true
}

func (s Sudoku) isRowSafe(pos *Position, value uint8) bool {
	var x uint8

	for x = 0; x < 9; x++ {
		if x != pos.x {
			cell := s[pos.y][x]

			if cell == value {
				return false
			}
		}
	}

	return true
}

func (s *Sudoku) isSafe(pos *Position, value uint8) bool {
	isSafeColumn := s.isColumnSafe(pos, value)
	isSafeRow := s.isRowSafe(pos, value)
	isSafeSubgrid := s.isSubgridSafe(pos, value)

	return isSafeColumn && isSafeRow && isSafeSubgrid
}

func (s *Sudoku) getValidNumber(pos *Position, start uint8) *uint8 {
	n := start + 1
	for n = start + 1; n <= 9; n++ {
		if s.isSafe(pos, n) {
			return &n
		}
	}

	return nil
}

func (s *Sudoku) solveWithBacktracking() {
	var stack stack.Stack[Position]
	isBacktracking := false

	var y, x uint8
	for y = 0; y < 9; y++ {
		for x = 0; x < 9; x++ {
			pos := Position{y, x}

			cell := s.getCell(&pos)

			var start uint8 = 0
			if isBacktracking {
				start = cell
			}

			if cell == 0 || isBacktracking {
				n := s.getValidNumber(&pos, start)

				if n != nil {
					s.setCell(&pos, *n)
					stack.Push(pos)
					isBacktracking = false
				} else {
					if isBacktracking {
						s.setCell(&pos, 0)
					}

					lastValidPos := stack.Pop()

					if lastValidPos == nil {
						panic("Could not solve it")
					}

					y = lastValidPos.y
					x = lastValidPos.x - 1
					isBacktracking = true
				}
			}

		}
	}
}

func (s Sudoku) print() {
	for _, row := range s {
		fmt.Println(row)
	}
	fmt.Println()
}

func (s *Sudoku) solve() {
	s.print()
	s.solveWithBacktracking()
	s.print()
}

// Recursive approach (the usual one)
func (s *Sudoku) solveWithBacktrackingRecursive(y, x uint8) bool {
	pos := &Position{y, x}

	if y == 9 {
		return true
	} else if x == 9 {
		return s.solveWithBacktrackingRecursive(y+1, 0)
	} else if s.getCell(pos) != 0 {
		return s.solveWithBacktrackingRecursive(y, x+1)
	} else {
		var n uint8
		for n = 1; n <= 9; n++ {
			if s.isSafe(pos, n) {
				s.setCell(pos, n)

				if s.solveWithBacktrackingRecursive(y, x+1) {
					return true
				}

				s.setCell(pos, 0)
			}
		}
		return false
	}
}

func (s *Sudoku) solveRecursive() {
	s.print()
	s.solveWithBacktrackingRecursive(0, 0)
	s.print()
}

func main() {
	var sudoku = Sudoku{
		{5, 3, 0, 0, 7, 0, 0, 0, 0},
		{6, 0, 0, 1, 9, 5, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 0},
		{0, 0, 0, 4, 1, 9, 0, 0, 5},
		{0, 0, 0, 0, 8, 0, 0, 7, 9},
	}

	// sudoku.solve()
	sudoku.solveRecursive()
}
