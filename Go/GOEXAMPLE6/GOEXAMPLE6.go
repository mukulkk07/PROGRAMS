package main

import (
	"crypto/rand"
	"fmt"
	"math/big"
	"time"
)

// --- THE MATHEMATICS ---
// RSA relies on the relationship: (M^e)^d ≡ M (mod n)
// 1. p, q = Two large random prime numbers
// 2. n = p * q (The Modulus)
// 3. φ(n) = (p-1) * (q-1) (Euler's Totient)
// 4. e = Public Exponent (usually 65537)
// 5. d = Private Exponent (Modular Multiplicative Inverse of e mod φ(n))

func main() {
	fmt.Println("--- Starting RSA Key Generation (Math/Big) ---")
	start := time.Now()

	// 1. GENERATE PRIMES (p and q)
	// In real security, these would be 2048+ bits. We use 128 for speed here.
	bitSize := 128
	p, _ := rand.Prime(rand.Reader, bitSize)
	q, _ := rand.Prime(rand.Reader, bitSize)

	// 2. CALCULATE N (The Public Modulus)
	// N = p * q
	N := new(big.Int).Mul(p, q)

	// 3. CALCULATE EULER'S TOTIENT φ(n)
	// φ(n) = (p-1) * (q-1)
	one := big.NewInt(1)
	pMinus1 := new(big.Int).Sub(p, one)
	qMinus1 := new(big.Int).Sub(q, one)
	phi := new(big.Int).Mul(pMinus1, qMinus1)

	// 4. DEFINE PUBLIC EXPONENT (e)
	// 65537 is the industry standard (prime and efficient)
	E := big.NewInt(65537)

	// 5. CALCULATE PRIVATE KEY (d)
	// d = e^(-1) mod φ(n)
	// This uses the "Extended Euclidean Algorithm"
	D := new(big.Int).ModInverse(E, phi)

	if D == nil {
		fmt.Println("Math Error: E and Phi are not coprime. Try again.")
		return
	}

	fmt.Printf("Keys Generated in %s\n", time.Since(start))
	fmt.Printf("Public Modulus (N): %s... (truncated)\n", N.String()[:20])
	fmt.Println("------------------------------------------------")

	// --- SIMULATION ---

	// The secret message (as a number)
	messageVal := int64(123456789)
	Message := big.NewInt(messageVal)

	fmt.Printf("Original Message:  %d\n", Message)

	// ENCRYPTION: C = M^e mod N
	Ciphertext := new(big.Int).Exp(Message, E, N)
	fmt.Printf("Encrypted (C):     %s\n", Ciphertext.String())

	// DECRYPTION: M = C^d mod N
	Decrypted := new(big.Int).Exp(Ciphertext, D, N)
	fmt.Printf("Decrypted (M):     %s\n", Decrypted.String())

	// VALIDATION
	if Decrypted.Cmp(Message) == 0 {
		fmt.Println("\nSuccess! The math works.")
	} else {
		fmt.Println("\nFailure! The math is broken.")
	}
}
