package JavaFun;

import java.util.Scanner;

public class MasterConditions {

    public static void main(String[] args) {
        
        // Setup Scanner for input
        Scanner scanner = new Scanner(System.in);

        System.out.println("=== JAVA CONDITIONAL STATEMENTS MASTERCLASS ===\n");

        // ---------------------------------------------------------
        // 1. SIMPLE IF STATEMENT
        // Used when you only want to do something if a condition is true.
        // ---------------------------------------------------------
        System.out.print("Enter a number to check if it's positive: ");
        int number = scanner.nextInt();

        if (number > 0) {
            System.out.println("-> Result: The number is POSITIVE.");
        }
        // If false, nothing happens here.

        System.out.println("----------------------------------------");


        // ---------------------------------------------------------
        // 2. IF - ELSE STATEMENT
        // Used when you have two paths: one for True, one for False.
        // ---------------------------------------------------------
        System.out.print("Enter your age: ");
        int age = scanner.nextInt();

        if (age >= 18) {
            System.out.println("-> Result: You are an Adult.");
        } else {
            System.out.println("-> Result: You are a Minor.");
        }

        System.out.println("----------------------------------------");


        // ---------------------------------------------------------
        // 3. IF - ELSE IF - ELSE LADDER
        // Used when you have more than two possible outcomes.
        // ---------------------------------------------------------
        System.out.print("Enter a traffic light color (1=Red, 2=Yellow, 3=Green): ");
        int light = scanner.nextInt();

        if (light == 1) {
            System.out.println("-> Action: STOP!");
        } else if (light == 2) {
            System.out.println("-> Action: SLOW DOWN!");
        } else if (light == 3) {
            System.out.println("-> Action: GO!");
        } else {
            // This runs if none of the above match
            System.out.println("-> Error: Invalid Color Code.");
        }

        System.out.println("----------------------------------------");


        // ---------------------------------------------------------
        // 4. NESTED IF STATEMENTS
        // An 'if' inside another 'if'. Used for specific sub-conditions.
        // ---------------------------------------------------------
        System.out.print("Enter a year to check for Leap Year: ");
        int year = scanner.nextInt();

        if (year % 4 == 0) {
            // It is divisible by 4, but we must check further...
            if (year % 100 == 0) {
                // Divisible by 100, must also be divisible by 400
                if (year % 400 == 0) {
                    System.out.println("-> Result: " + year + " IS a Leap Year.");
                } else {
                    System.out.println("-> Result: " + year + " is NOT a Leap Year.");
                }
            } else {
                System.out.println("-> Result: " + year + " IS a Leap Year.");
            }
        } else {
            System.out.println("-> Result: " + year + " is NOT a Leap Year.");
        }

        System.out.println("----------------------------------------");


        // ---------------------------------------------------------
        // 5. SWITCH STATEMENT
        // Used to replace long 'else-if' ladders when checking a single variable against strict values.
        // ---------------------------------------------------------
        System.out.print("Enter Day of Week (1-7): ");
        int day = scanner.nextInt();
        String dayName;

        switch (day) {
            case 1:
                dayName = "Monday";
                break; // 'break' stops the code from falling through to the next case
            case 2:
                dayName = "Tuesday";
                break;
            case 3:
                dayName = "Wednesday";
                break;
            case 4:
                dayName = "Thursday";
                break;
            case 5:
                dayName = "Friday";
                break;
            case 6:
                dayName = "Saturday";
                break;
            case 7:
                dayName = "Sunday";
                break;
            default:
                dayName = "Invalid Day";
        }
        System.out.println("-> Result: Day " + day + " is " + dayName);


        // ---------------------------------------------------------
        // 6. MODERN SWITCH EXPRESSION (Java 12+ / Enhanced Switch)
        // Cleaner syntax, no 'break' needed. Returns a value directly.
        // ---------------------------------------------------------
        System.out.println("\n(Bonus) Checking Weekend status using Enhanced Switch...");
        String type = switch (day) {
            case 1, 2, 3, 4, 5 -> "Weekday";
            case 6, 7 -> "Weekend";
            default -> "Unknown";
        };
        System.out.println("-> Result: It is a " + type);

        
        // Close scanner
        scanner.close();
    }
}