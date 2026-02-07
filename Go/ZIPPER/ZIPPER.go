package main

import (
	"archive/zip"
	"fmt"
	"io"
	"log"
	"os"
)

func main() {
	// 1. SETUP: Create some dummy files to test with
	filesToZip := []string{"note1.txt", "note2.txt", "secret.log"}
	createDummyFiles(filesToZip)

	outputName := "my_archive.zip"
	fmt.Println("--- Starting Compression Tool ---")

	// 2. CREATE THE ZIP FILE
	// We create the empty file on disk
	outFile, err := os.Create(outputName)
	if err != nil {
		log.Fatal(err)
	}
	defer outFile.Close()

	// 3. CREATE THE ZIP WRITER
	// This wrapper handles the compression logic
	zipWriter := zip.NewWriter(outFile)

	// CRITICAL: You must close the zipWriter to write the final footer data
	// If you forget this, the zip file will be corrupt!
	defer zipWriter.Close()

	// 4. ADD FILES TO ARCHIVE
	for _, filename := range filesToZip {
		fmt.Printf("Zipping: %s...\n", filename)

		err := addFileToZip(zipWriter, filename)
		if err != nil {
			log.Printf("Failed to zip %s: %v", filename, err)
		}
	}

	fmt.Println("--------------------------------")
	fmt.Println("Success! Created", outputName)
}

// Helper function to handle the logic for a single file
func addFileToZip(zipWriter *zip.Writer, filename string) error {
	// A. Open the original file for reading
	fileToRead, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer fileToRead.Close()

	// B. Create a new entry inside the zip archive
	// This returns a "Writer" that points inside the zip
	writerInsideZip, err := zipWriter.Create(filename)
	if err != nil {
		return err
	}

	// C. STREAM THE DATA
	// io.Copy connects the reader (disk file) to the writer (zip entry)
	// It moves the bytes directly without loading the whole file into RAM
	_, err = io.Copy(writerInsideZip, fileToRead)
	return err
}

// --- UTILITY TO MAKE TEST FILES ---
func createDummyFiles(filenames []string) {
	for _, name := range filenames {
		content := fmt.Sprintf("This is some content for file: %s\nCreated by Go.", name)
		os.WriteFile(name, []byte(content), 0644)
	}
}
