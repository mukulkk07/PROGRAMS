package main

import (
	"fmt"
	"image"
	"image/color"
	"image/png"
	"math/cmplx"
	"os"
	"time"
)

func main() {
	fmt.Println("--- Starting Fractal Generator ---")
	start := time.Now()

	// 1. CONFIGURATION
	const (
		width  = 1024
		height = 1024
		file   = "mandelbrot.png"
	)

	// 2. CREATE IMAGE CANVAS
	// Rect is a rectangle (x0, y0, x1, y1)
	img := image.NewRGBA(image.Rect(0, 0, width, height))

	// 3. PIXEL CALCULATION LOOP
	// We iterate over every single pixel (1024 * 1024 = 1 million pixels)
	fmt.Println("Calculating pixels... (This utilizes your CPU)")

	for py := 0; py < height; py++ {
		for px := 0; px < width; px++ {

			// Convert pixel coordinate to complex number coordinate
			// We map the image to the mathematical range -2 to +2
			x := float64(px)/width*(3.5) - 2.5
			y := float64(py)/height*(2) - 1.0
			z := complex(x, y)

			// Calculate the color for this spot
			// Image Point sets the color at (x, y)
			img.Set(px, py, mandelbrot(z))
		}
	}

	// 4. SAVE TO FILE
	outputFile, err := os.Create(file)
	if err != nil {
		panic(err)
	}
	defer outputFile.Close()

	// Encode the image object into actual PNG bytes
	err = png.Encode(outputFile, img)
	if err != nil {
		panic(err)
	}

	elapsed := time.Since(start)
	fmt.Printf("Success! Generated '%s' in %s\n", file, elapsed)
}

// --- MATH LOGIC ---
// This function determines the color based on how "stable" the point is mathematically
func mandelbrot(z complex128) color.Color {
	const iterations = 200
	const contrast = 15

	var v complex128
	for n := uint8(0); n < iterations; n++ {
		v = v*v + z

		// If it escapes the radius (diverges), it's part of the chaos
		if cmplx.Abs(v) > 2 {
			// Create a nice blue gradient based on how fast it escaped
			// R, G, B, Alpha
			return color.RGBA{0, n * contrast, 255 - (n * contrast), 255}
		}
	}
	// If it never escapes, it is black (inside the set)
	return color.Black
}
