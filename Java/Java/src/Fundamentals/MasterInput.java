package JavaFun;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class MasterInput {

    // "throws IOException" is required here to use BufferedReader without try-catch blocks
    public static void main(String[] args) throws IOException {
        
        System.out.println("=== JAVA INPUT MASTERCLASS ===\n");

        // ---------------------------------------------------------
        // 1. UNFORMATTED INPUT (System.in.read)
        // The most basic way. Reads a single BYTE (character code) at a time.
        // ---------------------------------------------------------
        System.out.println("--- 1. Raw Byte Input (System.in) ---");
        System.out.print("Type a single character and press Enter: ");
        
        int charCode = System.in.read(); // Reads the ASCII code (e.g., 'A' is 65)
        System.out.println("Byte value: " + charCode);
        System.out.println("Character:  " + (char)charCode);
        
        // CLEANUP: System.in.read() leaves the "Enter" key (\n) in the buffer.
        // We must skip it, otherwise the next input method will read it and skip your turn.
        System.in.skip(System.in.available()); 
        System.out.println();


        // ---------------------------------------------------------
        // 2. BUFFERED STRING INPUT (BufferedReader)
        // This is "Raw Text" input. It reads whole lines as Strings.
        // It is FASTER than Scanner but "dumb" (it doesn't know what an int is).
        // ---------------------------------------------------------
        System.out.println("--- 2. Buffered Input (Strings) ---");
        // We wrap System.in (bytes) -> InputStreamReader (chars) -> BufferedReader (lines)
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.print("Enter your full name: ");
        String fullName = reader.readLine(); // Reads until you hit Enter
        System.out.println("received: " + fullName);
        
        // MANUAL PARSING: Converting raw string input into numbers
        System.out.print("Enter your birth year (read as String, parsed to Int): ");
        String yearString = reader.readLine();
        int year = Integer.parseInt(yearString); // This converts "2000" to 2000
        System.out.println("Calculated Age: " + (2026 - year));
        System.out.println();


        // ---------------------------------------------------------
        // 3. FORMATTED INPUT (Scanner)
        // The "Smart" way. Breaks input into "tokens" and parses them automatically.
        // Note: We use the same System.in, so we don't create a new stream, just a new wrapper.
        // ---------------------------------------------------------
        System.out.println("--- 3. Formatted Input (Scanner) ---");
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your generic age (int): ");
        int age = scanner.nextInt(); // Automatically parses "25" to int 25
        
        System.out.print("Enter your GPA (double): ");
        double gpa = scanner.nextDouble(); // Automatically parses "3.5" to double 3.5

        System.out.printf("Student is %d years old with a GPA of %.2f %n", age, gpa);


        // ---------------------------------------------------------
        // 4. THE SCANNER "NEWLINE TRAP" (Very Common Bug!)
        // ---------------------------------------------------------
        System.out.println("\n--- 4. The Scanner 'Next Line' Trap ---");
        System.out.println("Enter a favorite quote: ");
        
        // PROBLEM: nextInt() and nextDouble() read the number but leave the "Enter" key (\n)
        // sitting in the input stream.
        // The next command, scanner.nextLine(), sees that \n and thinks the user hit enter immediately.
        
        // FIX: We fire one empty nextLine() to consume that leftover \n
        scanner.nextLine(); 
        
        String quote = scanner.nextLine(); // Now this will wait for actual input
        System.out.println("Quote recorded: " + quote);

        
        // Close the scanner (This also closes System.in, so do this last!)
        scanner.close();
    }
}