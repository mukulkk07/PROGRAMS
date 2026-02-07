package JavaFun;

import java.util.Date;

public class MasterOutput {

    public static void main(String[] args) {
        
        System.out.println("=== JAVA OUTPUT MASTERCLASS ===\n");

        // ---------------------------------------------------------
        // 1. UNFORMATTED OUTPUT (print & println)
        // This is quick and dirty. You just dump data to the console.
        // ---------------------------------------------------------
        System.out.println("--- 1. Unformatted Output ---");
        
        System.out.print("System.out.print: "); 
        System.out.print("This stays on the same line... ");
        System.out.print("Still on the same line.");
        
        System.out.println(); // Manually print a new line to fix the formatting
        
        System.out.println("System.out.println: This moves to the next line automatically.");
        
        double pi = 3.14159265359;
        System.out.println("Raw Value of PI: " + pi); // You cannot easily cut off decimals here
        System.out.println();


        // ---------------------------------------------------------
        // 2. FORMATTED OUTPUT (printf)
        // Syntax: System.out.printf( "Format String", arguments... );
        // Use this when you need specific decimal places, alignment, or padding.
        // NOTE: printf does NOT add a new line automatically! You must use %n or \n.
        // ---------------------------------------------------------
        System.out.println("--- 2. Formatted Output (printf) ---");
        
        String name = "Alice";
        int age = 25;
        double grade = 95.5;

        // %s = String, %d = Integer, %f = Float/Double, %n = New Line
        System.out.printf("Student: %s, Age: %d, Grade: %f %n", name, age, grade);
        
        
        // ---------------------------------------------------------
        // 3. CONTROLLING PRECISION (Decimal Places)
        // %.2f means "floating point number with exactly 2 decimal places"
        // ---------------------------------------------------------
        System.out.println("\n--- 3. Decimal Precision ---");
        
        double price = 12.5; // Stored as 12.5
        System.out.printf("Raw price: %f %n", price); // Prints 12.500000 (ugly)
        System.out.printf("Currency style: $%.2f %n", price); // Prints $12.50 (clean)
        System.out.printf("Scientific notation: %.4f %n", Math.PI); 


        // ---------------------------------------------------------
        // 4. WIDTH AND ALIGNMENT (Making Tables)
        // %10s  -> Right align (pad with spaces on left to make width 10)
        // %-10s -> Left align (pad with spaces on right)
        // ---------------------------------------------------------
        System.out.println("\n--- 4. Alignment & Tables ---");
        
        System.out.println("-----------------------------");
        System.out.printf("| %-10s | %-5s | %8s |%n", "ITEM", "QTY", "PRICE");
        System.out.println("-----------------------------");
        
        System.out.printf("| %-10s | %-5d | $%7.2f |%n", "Apples", 5, 2.50);
        System.out.printf("| %-10s | %-5d | $%7.2f |%n", "Milk", 1, 10.99);
        System.out.printf("| %-10s | %-5d | $%7.2f |%n", "Bread", 2, 4.25);
        System.out.println("-----------------------------");


        // ---------------------------------------------------------
        // 5. ESCAPE SEQUENCES
        // Special characters that start with a backslash (\)
        // ---------------------------------------------------------
        System.out.println("\n--- 5. Escape Sequences ---");
        
        System.out.println("New Line:      Line 1\nLine 2");
        System.out.println("Tab Space:     Column1\tColumn2");
        System.out.println("Backslash:     C:\\Windows\\System32"); // You need \\ to print one \
        System.out.println("Quotes:        She said, \"Java is cool!\""); // You need \" to print "

        
        // ---------------------------------------------------------
        // 6. STRING.FORMAT (Storing format instead of printing)
        // If you want to SAVE the formatted text to a variable instead of printing it.
        // ---------------------------------------------------------
        System.out.println("\n--- 6. String.format() ---");
        
        String logMessage = String.format("User %s logged in at %tc", "Admin", new Date());
        System.out.println("Saved Log: " + logMessage);
    }
}