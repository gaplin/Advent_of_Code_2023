package main

import (
	"bufio"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

func delete_empty(s []string) []string {
	var r []string
	for _, str := range s {
		if str != "" {
			r = append(r, str)
		}
	}
	return r
}

func get_won_values(winning_numbers []string, numbers []string) int64 {
	matches := 0
	for _, v := range winning_numbers {
		if slices.Contains(numbers, v) {
			matches++
		}
	}
	if matches == 0 {
		return 0
	}
	return 1 << (matches - 1)
}

func main() {
	file, err := os.Open("../input/input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	sum := int64(0)
	for scanner.Scan() {
		line := scanner.Text()
		nums := strings.Split(strings.Split(line, ":")[1], "|")
		winning_numbers := delete_empty(strings.Split(nums[0], " "))
		numbers := delete_empty(strings.Split(nums[1], " "))
		sum += get_won_values(winning_numbers, numbers)
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	f, err := os.Create("../output/out_first.txt")

	if err != nil {
		log.Fatal(err)
	}

	defer f.Close()

	_, err2 := f.WriteString(strconv.FormatInt(sum, 10))

	if err2 != nil {
		log.Fatal(err2)
	}
}
