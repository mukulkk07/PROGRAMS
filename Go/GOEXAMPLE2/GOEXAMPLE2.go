package main

import (
	"fmt"
	"net/http"
	"time"
)

// --- 1. RESULT STRUCT ---
// We will send this data back through a channel
type SiteStatus struct {
	Url     string
	Latency time.Duration
	IsUp    bool
}

// --- 2. THE WORKER FUNCTION ---
// This function visits a single URL and reports back
func checkWebsite(url string, results chan<- SiteStatus) {
	start := time.Now()

	// Try to get the website with a strict 2-second timeout
	client := http.Client{
		Timeout: 2 * time.Second,
	}

	resp, err := client.Get(url)

	// Prepare the result
	status := SiteStatus{
		Url:     url,
		Latency: time.Since(start),
		IsUp:    true,
	}

	// If there was an error (e.g., site down) or status isn't 200 OK
	if err != nil || resp.StatusCode != 200 {
		status.IsUp = false
	} else {
		// Always close the body to prevent memory leaks!
		resp.Body.Close()
	}

	// Send the report card into the channel
	results <- status
}

// --- MAIN EXECUTION ---

func main() {
	// List of websites to monitor
	websites := []string{
		"https://www.google.com",
		"https://www.github.com",
		"https://golang.org",
		"https://www.stackoverflow.com",
		"https://this-site-does-not-exist.xyz", // Intentionally broken
	}

	// Create a channel to collect results
	results := make(chan SiteStatus)

	fmt.Println("--- Starting Network Health Check ---")

	// 3. LAUNCH GOROUTINES
	// We start checking ALL sites instantly without waiting for the previous one
	for _, site := range websites {
		go checkWebsite(site, results)
	}

	// 4. COLLECT RESULTS
	// We wait for exactly as many results as we have websites
	for i := 0; i < len(websites); i++ {
		status := <-results // This line blocks until a result arrives

		if status.IsUp {
			fmt.Printf("[ONLINE] %s \t(Time: %v)\n", status.Url, status.Latency)
		} else {
			fmt.Printf("[DOWN]   %s \t(Failed after %v)\n", status.Url, status.Latency)
		}
	}

	fmt.Println("\n--- All checks complete ---")
}
