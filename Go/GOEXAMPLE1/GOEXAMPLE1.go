package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"
)

// --- 1. DATA MODEL ---
type Book struct {
	ID     string `json:"id"`
	Title  string `json:"title"`
	Author string `json:"author"`
}

// We simulate a database using a simple global slice
var library = []Book{
	{ID: "1", Title: "The Go Programming Language", Author: "Alan Donovan"},
	{ID: "2", Title: "Clean Code", Author: "Robert Martin"},
}

// --- 2. HANDLERS (The functions that run when you visit a URL) ---

// GetBooks sends the list of books as JSON
func GetBooks(w http.ResponseWriter, r *http.Request) {
	// Set the header so the browser knows it's receiving JSON
	w.Header().Set("Content-Type", "application/json")

	// Encode our list into JSON and send it to the user
	json.NewEncoder(w).Encode(library)
}

// AddBook allows adding a new book via a POST request
func AddBook(w http.ResponseWriter, r *http.Request) {
	if r.Method != "POST" {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}

	var newBook Book
	// Decode the data the user sent us
	err := json.NewDecoder(r.Body).Decode(&newBook)
	if err != nil {
		http.Error(w, "Invalid data", http.StatusBadRequest)
		return
	}

	library = append(library, newBook)

	w.WriteHeader(http.StatusCreated) // Send 201 Created
	fmt.Fprintf(w, "Success! Added '%s' to the library.", newBook.Title)
}

// --- 3. MIDDLEWARE (Interceptors) ---
// This function wraps our handlers to log every request
func Logger(next http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		start := time.Now()

		// Run the actual handler
		next(w, r)

		// Log how long it took
		fmt.Printf("[%s] %s %s took %v\n",
			r.Method, r.URL.Path, r.RemoteAddr, time.Since(start))
	}
}

// --- MAIN SERVER ---

func main() {
	// 4. ROUTING
	// We map URLs (like "/books") to functions
	http.HandleFunc("/books", Logger(GetBooks))
	http.HandleFunc("/add", Logger(AddBook))

	// 5. START LISTENING
	port := ":8080"
	fmt.Printf("--- Server starting on http://localhost%s ---\n", port)
	fmt.Println("Press Ctrl+C to stop")

	// This starts the infinite loop that listens for connections
	err := http.ListenAndServe(port, nil)
	if err != nil {
		log.Fatal(err)
	}
}
