package main

import (
	"fmt"
	"math"
	"math/cmplx"
)

func main() {
	fmt.Println("--- Starting Signal Analysis (DFT) ---")

	// 1. CONFIGURATION
	// SampleRate: How many times per second we measure the signal
	const sampleRate = 8.0
	// Duration: How long the signal lasts (seconds)
	const seconds = 1.0

	N := int(sampleRate * seconds) // Total number of samples

	// 2. GENERATE A COMPLEX SIGNAL
	// We mix two different frequencies together:
	// - A strong low wave (1 Hz)
	// - A weaker high wave (3 Hz)
	inputSignal := make([]float64, N)

	fmt.Println("\nInput Signal (Time Domain):")
	for i := 0; i < N; i++ {
		t := float64(i) / sampleRate

		// Math: f(t) = Amplitude * sin(2 * pi * Frequency * t)
		wave1 := 1.0 * math.Sin(2*math.Pi*1.0*t) // 1 Hz
		wave2 := 0.5 * math.Sin(2*math.Pi*3.0*t) // 3 Hz

		inputSignal[i] = wave1 + wave2
		fmt.Printf("t=%.2f: %.4f\n", t, inputSignal[i])
	}

	// 3. APPLY DISCRETE FOURIER TRANSFORM
	// This math converts Time Domain -> Frequency Domain
	spectrum := DFT(inputSignal)

	// 4. ANALYZE RESULTS
	fmt.Println("\nOutput Spectrum (Frequency Domain):")
	fmt.Println("Freq (Hz) | Magnitude (Strength)")
	fmt.Println("--------------------------------")

	for k, val := range spectrum {
		// We only look at the first half (Nyquist limit)
		if k > N/2 {
			break
		}

		// Magnitude = Absolute value of the complex number
		// We divide by N/2 to normalize the amplitude
		magnitude := cmplx.Abs(val) / (float64(N) / 2.0)

		// Filter out noise (floating point errors)
		if magnitude < 0.0001 {
			magnitude = 0
		}

		// If the magnitude is high, we found a wave!
		bar := ""
		if magnitude > 0.1 {
			bar = " <--- FOUND SIGNAL!"
		}

		// The index 'k' corresponds directly to Frequency in Hz here
		// because our duration is exactly 1.0 second.
		fmt.Printf("   %d Hz   |   %.4f  %s\n", k, magnitude, bar)
	}
}

// --- THE IMPORTANT MATH ---
// Formula: X_k = Σ (x_n * e^(-i * 2π * k * n / N))
func DFT(input []float64) []complex128 {
	N := len(input)
	output := make([]complex128, N)

	for k := 0; k < N; k++ {
		var sum complex128
		for n := 0; n < N; n++ {
			// 1. Euler's Formula part
			// theta represents the angle on the complex plane
			theta := -2.0 * math.Pi * float64(k) * float64(n) / float64(N)

			// 2. Convert angle to Complex Number (cos θ + i sin θ)
			// Go allows creating complex numbers natively
			complexFactor := cmplx.Rect(1, theta)

			// 3. Summation
			sum += complex(input[n], 0) * complexFactor
		}
		output[k] = sum
	}
	return output
}
