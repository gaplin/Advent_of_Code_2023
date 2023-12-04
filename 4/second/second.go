package main

import (
	"bufio"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

type card struct {
	winning_numbers []string
	numbers         []string
}

func delete_empty(s []string) []string {
	var r []string
	for _, str := range s {
		if str != "" {
			r = append(r, str)
		}
	}
	return r
}

func get_number_of_matches(winning_numbers []string, numbers []string) int64 {
	var matches int64
	for _, v := range winning_numbers {
		if slices.Contains(numbers, v) {
			matches++
		}
	}
	return matches
}

func get_result(cards []card) int64 {
	corrections := make([]int64, len(cards)+1)
	var result int64
	var accumulator int64
	accumulator = 1
	for idx, element := range cards {
		accumulator += corrections[idx]
		result += accumulator
		number_of_matches := get_number_of_matches(element.winning_numbers, element.numbers)
		if number_of_matches > 0 {
			corrections[idx+int(number_of_matches)+1] -= accumulator
			corrections[idx+1] += accumulator
		}
	}
	return result
}

func main() {
	file, err := os.Open("../input/input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	var cards []card
	for scanner.Scan() {
		line := scanner.Text()
		nums := strings.Split(strings.Split(line, ":")[1], "|")
		winning_numbers := delete_empty(strings.Split(nums[0], " "))
		numbers := delete_empty(strings.Split(nums[1], " "))
		cards = append(cards, card{winning_numbers: winning_numbers, numbers: numbers})
	}

	result := get_result(cards)
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	f, err := os.Create("../output/out_second.txt")

	if err != nil {
		log.Fatal(err)
	}

	defer f.Close()

	_, err2 := f.WriteString(strconv.FormatInt(result, 10))

	if err2 != nil {
		log.Fatal(err2)
	}
}
