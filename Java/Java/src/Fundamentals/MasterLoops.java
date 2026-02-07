package JavaFun;

public class MasterLoops {

    public static void main(String[] args) {
        
        System.out.println("=== JAVA LOOPS MASTERCLASS ===\n");

        // ---------------------------------------------------------
        // 1. THE FOR LOOP
        // Use this when you know EXACTLY how many times to loop.
        // Syntax: for (initialization; condition; update)
        // ---------------------------------------------------------
        System.out.println("1. Standard For Loop (Counting 1 to 5):");
        
        for (int i = 1; i <= 5; i++) {
            System.out.print(i + " ");
        }
        System.out.println("\n----------------------------------------");


        // ---------------------------------------------------------
        // 2. THE WHILE LOOP
        // Use this when you DON'T know how many iterations strictly.
        // It runs as long as the condition is true.
        // ---------------------------------------------------------
        System.out.println("2. While Loop (Countdown):");
        
        int countdown = 5;
        while (countdown > 0) {
            System.out.print(countdown + "...");
            countdown--; // Critical! If you forget this, you get an Infinite Loop.
        }
        System.out.println("Liftoff!");
        System.out.println("----------------------------------------");


        // ---------------------------------------------------------
        // 3. THE DO-WHILE LOOP
        // Use this when the code MUST execute at least once (e.g., Menus).
        // It checks the condition AFTER running the code.
        // ---------------------------------------------------------
        System.out.println("3. Do-While Loop (Guaranteed execution):");
        
        int number = 100;
        do {
            System.out.println("   This prints even though condition (number < 10) is false!");
            number++; 
        } while (number < 10);
        
        System.out.println("----------------------------------------");


        // ---------------------------------------------------------
        // 4. THE FOR-EACH LOOP (Enhanced For Loop)
        // best used for iterating over Arrays or Lists.
        // You cannot use this to modify the index, just to read values.
        // ---------------------------------------------------------
        System.out.println("4. For-Each Loop (Iterating an Array):");
        
        String[] languages = {"Java", "C++", "Python", "JavaScript"};
        
        for (String lang : languages) {
            System.out.println("   > " + lang);
        }
        System.out.println("----------------------------------------");


        // ---------------------------------------------------------
        // 5. LOOP CONTROL STATEMENTS (Break & Continue)
        // Break: Kills the loop immediately.
        // Continue: Skips the rest of the current iteration and jumps to the next one.
        // ---------------------------------------------------------
        System.out.println("5. Break and Continue:");
        
        for (int i = 1; i <= 10; i++) {
            if (i == 3) {
                System.out.println("   (Skipping 3 using continue)");
                continue; // Jump back to top of loop, don't print 3
            }
            if (i == 7) {
                System.out.println("   (Stopping at 7 using break)");
                break; // Exit the loop entirely
            }
            System.out.println("   Number: " + i);
        }
        System.out.println("----------------------------------------");


        // ---------------------------------------------------------
        // 6. NESTED LOOPS
        // A loop inside a loop. Common for grids or matrices.
        // ---------------------------------------------------------
        System.out.println("6. Nested Loops (Building a Grid):");
        
        // Outer loop controls Rows (i)
        for (int i = 1; i <= 3; i++) {
            // Inner loop controls Columns (j)
            for (int j = 1; j <= 3; j++) {
                System.out.print("[" + i + "," + j + "] ");
            }
            System.out.println(); // New line after every row
        }
    }
}