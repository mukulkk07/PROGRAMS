package main

import (
	"crypto/rand"
	"flag"
	"fmt"
	"math/big"
	"os"
)

// --- 1. CONFIGURATION ---
// We define the character sets we want to use
const (
	letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	digits  = "0123456789"
	special = "!@#$%^&*()-_=+,.?/:;{}[]"
)

func main() {
	// --- 2. FLAGS (Command Line Arguments) ---
	// Instead of hardcoding values, we let the user decide at runtime.
	// syntax: flag.Type("name", default_value, "help description")
	lengthPtr := flag.Int("len", 16, "Length of the password")
	useSpecialPtr := flag.Bool("special", true, "Include special characters like !@#")
	useDigitsPtr := flag.Bool("digits", true, "Include numbers")

	// Essential: This parses the arguments provided by the user
	flag.Parse()

	if *lengthPtr < 4 {
		fmt.Println("Error: Password length must be at least 4 characters.")
		os.Exit(1)
	}

	fmt.Printf("--- Generating Secure Password (Length: %d) ---\n", *lengthPtr)

	// --- 3. BUILD CHARACTER POOL ---
	charPool := letters
	if *useDigitsPtr {
		charPool += digits
	}
	if *useSpecialPtr {
		charPool += special
	}

	// --- 4. GENERATION LOOP ---
	password := ""
	for i := 0; i < *lengthPtr; i++ {
		// crypto/rand.Int returns a secure random number
		// We ask for a number between 0 and the length of our pool
		randomNum, err := rand.Int(rand.Reader, big.NewInt(int64(len(charPool))))
		if err != nil {
			fmt.Println("Critical Error generating random number:", err)
			return
		}

		// Pick the character at that random index
		index := randomNum.Int64()
		password += string(charPool[index])
	}

	fmt.Printf("Result: %s\n", password)
	fmt.Println("-------------------------------------------")
}
