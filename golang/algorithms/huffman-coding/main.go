package main

import (
	"errors"
	"fmt"
	"math"
	"os"
	"strings"
)

type Node struct {
	leftNode  *Node
	rightNode *Node
	value     string
	weight    int
}

type Tree struct {
	text string
	root *Node
}

func (t *Tree) encodeCharacter(c string, current *Node, out *string) {
	if current.leftNode == nil && current.rightNode == nil {
		if current.value == c {
			return
		}

		panic("Dead end")
	}

	if current.leftNode != nil && strings.Contains(current.leftNode.value, c) {
		*out += "0"
		t.encodeCharacter(c, current.leftNode, out)
	} else {
		*out += "1"
		t.encodeCharacter(c, current.rightNode, out)
	}
}

// No priority queue or stack?
func (t *Tree) encode() (string, error) {
	if t.root == nil {
		return "", errors.New("Empty tree")
	}

	cache := map[byte]string{}

	out := ""
	for _, c := range t.text {
		cByte := byte(c)

		if cache[cByte] != "" {
			out += cache[cByte]
		} else {
			encodedChar := ""
			t.encodeCharacter(string(c), t.root, &encodedChar)

			out += encodedChar
			cache[cByte] = encodedChar
		}

	}

	return out, nil
}

func (t *Tree) decode(encoded string) (string, error) {
	if t.root == nil {
		return "", errors.New("Empty tree")
	}

	out := ""
	current := t.root

	for _, b := range encoded {
		if string(b) == "0" {
			current = current.leftNode
		} else {
			current = current.rightNode
		}

		if current.leftNode == nil && current.rightNode == nil {
			out += current.value
			current = t.root
		}

	}

	return out, nil
}

func newHuffmanTree(text string) Tree {
	table := newHuffmanTable(text)
	var root *Node

	for len(table) > 1 {
		firstSmallestNode := table.getSmallestNode()
		delete(table, firstSmallestNode.value)

		secondSmallestNode := table.getSmallestNode()
		delete(table, secondSmallestNode.value)

		root = joinNodes(firstSmallestNode, secondSmallestNode)
		table[root.value] = root
	}

	return Tree{root: root, text: text}
}

type FrequencyTable map[string]*Node

func (table *FrequencyTable) getSmallestNode() *Node {
	smallest := &Node{weight: math.MaxInt}

	for _, node := range *table {
		if node.weight < smallest.weight {
			smallest = node
		}
	}

	return smallest
}

func newHuffmanTable(text string) FrequencyTable {
	table := FrequencyTable{}

	for _, c := range text {
		cString := string(c)

		if table[cString] == nil {
			table[cString] = &Node{value: cString, weight: 1}
		} else {
			table[cString].weight++
		}
	}

	return table
}

func joinNodes(firstNode, secondNode *Node) *Node {
	return &Node{
		leftNode:  firstNode,
		rightNode: secondNode,
		weight:    firstNode.weight + secondNode.weight,
		value:     firstNode.value + secondNode.value,
	}
}

func main() {
	args := os.Args[1:]

	if len(args) == 0 {
		panic("Missing input argument")
	}

	text := args[0]

	tree := newHuffmanTree(text)

	encoded, _ := tree.encode()
	decoded, _ := tree.decode(encoded)

	fmt.Println("Text:", text)
	fmt.Println("Encoded:", encoded)
	fmt.Println("Decoded:", decoded)
}
