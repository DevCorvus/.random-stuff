package main

import (
	"fmt"
	"sort"
)

type SuffixArray struct {
	text     string
	length   int
	suffixes []string
	lcp      []uint
}

type LongestRepeatedSubstrings struct {
	longest    uint
	substrings []string
}

func (s *SuffixArray) buildSuffixes() {
	suffixes := make([]string, s.length)

	for i := 0; i < s.length; i++ {
		suffixes[i] = s.text[i:]
	}

	sort.Strings(suffixes)

	s.suffixes = suffixes
}

// Kasai's algorithm to build "Longest Common Prefix" array
func (s *SuffixArray) buildLcp() {
	lcp := make([]uint, s.length)

	for i := 0; i < s.length; i++ {
		if i == s.length-1 {
			lcp[i] = 0
			break
		}

		curr := s.suffixes[i]
		next := s.suffixes[i+1]

		var count uint = 0

		for j := 0; j < len(curr) && j < len(next) && curr[j] == next[j]; j++ {
			count++
		}

		lcp[i] = count
	}

	s.lcp = lcp
}

func (s *SuffixArray) countUniqueSubstrings() uint {
	var lcpSum uint = 0

	for i := 0; i < s.length; i++ {
		lcpSum += s.lcp[i]
	}

	return uint(((s.length * (s.length + 1)) / 2)) - lcpSum
}

func (s *SuffixArray) findLongestRepeatedSubstrings() *LongestRepeatedSubstrings {
	var longest uint = 0
	var substrings []string

	for i, v := range s.lcp {
		if v > longest {
			longest = v
			substrings = []string{s.suffixes[i][:v]}
		} else if v == longest {
			substrings = append(substrings, s.suffixes[i][:v])
		}
	}

	return &LongestRepeatedSubstrings{
		longest:    longest,
		substrings: substrings,
	}
}

func (s *SuffixArray) findLongestCommonSubstring() {
	// TODO (Kinda tricky problem atm)
}

func NewSuffixArray(text string) *SuffixArray {
	sa := SuffixArray{text: text, length: len(text)}

	sa.buildSuffixes()
	sa.buildLcp()

	return &sa
}

func main() {
	sa := NewSuffixArray("banana")

	fmt.Printf("suffixes: %v\n", sa.suffixes)
	fmt.Printf("lcp: %v\n", sa.lcp)
	fmt.Printf("unique substrings: %d\n", sa.countUniqueSubstrings())
	fmt.Printf("longest repeated substrings: %v\n", sa.findLongestRepeatedSubstrings())
}
