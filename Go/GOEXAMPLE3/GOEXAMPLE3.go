package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strings"
	"time"
)

// --- 1. DATA STRUCTURE ---
// We'll store words and their counts here
type WordCount struct {
	Word  string
	Count int
}

func main() {
	// Step 1: Create a sample file to analyze (so this script works instantly)
	createSampleFile("sample_log.txt")

	fmt.Println("--- Starting File Analyzer ---")
	start := time.Now()

	// Step 2: Open the file for reading
	// We use os.Open for read-only access
	file, err := os.Open("sample_log.txt")
	if err != nil {
		log.Fatal("Could not open file:", err)
	}
	defer file.Close() // Ensure file closes even if we crash later

	// Step 3: Buffered Scanner
	// bufio.Scanner is efficient. It reads chunks instead of the whole file at once.
	// This allows you to process a 10GB file on a laptop with 4GB RAM.
	scanner := bufio.NewScanner(file)

	// Map to store counts
	frequencies := make(map[string]int)

	// Step 4: Process Line by Line
	for scanner.Scan() {
		line := scanner.Text()

		// Clean the line: Lowercase -> Remove punctuation could be added here
		words := strings.Fields(line) // Splits by whitespace (space, tab, etc)

		for _, word := range words {
			// Normalize: convert to lowercase
			cleanWord := strings.ToLower(word)
			frequencies[cleanWord]++
		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatal("Error reading file:", err)
	}

	// Step 5: Sort Results
	// Maps are random in Go, so we move data to a slice to sort it
	var sortedList []WordCount
	for k, v := range frequencies {
		sortedList = append(sortedList, WordCount{Word: k, Count: v})
	}

	// Sort by Count (Descending)
	sort.Slice(sortedList, func(i, j int) bool {
		return sortedList[i].Count > sortedList[j].Count
	})

	// Step 6: Write Report to a new file
	outputFile, err := os.Create("report.txt")
	if err != nil {
		log.Fatal("Could not create report:", err)
	}
	defer outputFile.Close()

	writer := bufio.NewWriter(outputFile)

	header := fmt.Sprintf("Analysis of 'sample_log.txt'\nProcessed in %v\n\nTOP WORDS:\n", time.Since(start))
	writer.WriteString(header)

	for i, wc := range sortedList {
		if i >= 10 {
			break
		} // Only top 10
		line := fmt.Sprintf("%-15s : %d\n", wc.Word, wc.Count)
		writer.WriteString(line)
	}

	// Flush ensures all data is actually written to the disk
	writer.Flush()

	fmt.Println("Success! Report saved to 'report.txt'")
}

// Helper function to generate a dummy file for you
func createSampleFile(filename string) {
	content := `
	Go is an open source programming language that makes it easy to build simple, reliable, and efficient software.
	Go is expressive, concise, clean, and efficient.
	Its concurrency mechanisms make it easy to write programs that get the most out of multicore and networked machines, 
	while its novel type system enables flexible and modular program construction.
	Go compiles quickly to machine code yet has the convenience of garbage collection and the power of run-time reflection.
	`
	// os.WriteFile is a quick way to dump data into a file (Go 1.16+)
	os.WriteFile(filename, []byte(content), 0644)
}
