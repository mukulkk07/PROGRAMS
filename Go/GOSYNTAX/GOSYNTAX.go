package main

import (
	"context"
	"encoding/json"
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// --- TYPE DEFINITIONS ---

// 1. GENERICS: A constraint that allows String or Int
type TaskID interface {
	~string | ~int
}

// 2. STRUCT: The blueprint for a unit of work
type Task[ID TaskID] struct {
	ID       ID     `json:"id"`
	Category string `json:"category"`
	Priority int    `json:"priority"`
}

// --- MAIN EXECUTION ---

func main() {
	// 3. SEED RANDOM: To simulate variable work times
	// Note: In Go 1.20+, global seed is deprecated, but good for specific randomness
	rng := rand.New(rand.NewSource(time.Now().UnixNano()))

	fmt.Println("--- Starting Job Processor (Go 1.25.6) ---")

	// 4. DATA SETUP (Slices)
	jobs := []Task[int]{
		{ID: 101, Category: "Image Processing", Priority: 1},
		{ID: 102, Category: "Data Mining", Priority: 2},
		{ID: 103, Category: "Report Gen", Priority: 1},
	}

	// 5. CHANNELS: The pipeline for data
	// Buffered channel avoids blocking the sender immediately
	processedStream := make(chan string, len(jobs))

	// 6. CONCURRENCY CONTROL
	var wg sync.WaitGroup
	ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
	defer cancel() // Cleanup timeout resources when main exits

	// --- FAN-OUT: Start a worker for every job ---
	for _, job := range jobs {
		wg.Add(1)

		// Launch a Goroutine (Background Thread)
		go func(j Task[int]) {
			defer wg.Done() // Decrease counter when function finishes

			// Simulate work time (between 0-500ms)
			workTime := time.Duration(rng.Intn(500)) * time.Millisecond

			select {
			case <-time.After(workTime):
				// Success case
				res := fmt.Sprintf("✓ Finished Job %d (%s) in %v", j.ID, j.Category, workTime)
				processedStream <- res
			case <-ctx.Done():
				// Timeout case
				processedStream <- fmt.Sprintf("✗ Timeout on Job %d", j.ID)
			}
		}(job)
	}

	// --- MONITOR: Close channel when all workers finish ---
	go func() {
		wg.Wait()              // Block here until all workers say .Done()
		close(processedStream) // Close the pipe so the loop below knows to stop
	}()

	// --- FAN-IN: Read results as they arrive ---
	// This loop runs until the channel is closed
	for result := range processedStream {
		fmt.Println(result)
	}

	// 7. JSON OUTPUT
	// Show how the raw data looks in JSON format
	bytes, _ := json.MarshalIndent(jobs, "", "  ")
	fmt.Printf("\nRaw Data Dump:\n%s\n", string(bytes))
}
