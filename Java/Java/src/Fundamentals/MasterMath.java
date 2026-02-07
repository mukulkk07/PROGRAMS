package JavaFun;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.RoundingMode;
import java.util.Random;

public class MasterMath {

    public static void main(String[] args) {

        System.out.println("=== JAVA ADVANCED MATH MASTERCLASS ===\n");

        // ---------------------------------------------------------
        // 1. THE MATH CLASS (Standard Library)
        // Java's built-in utility for common mathematical operations.
        // ---------------------------------------------------------
        System.out.println("--- 1. Basic Math Class Functions ---");
        
        System.out.println("Absolute Value (-10): " + Math.abs(-10));
        System.out.println("Square Root (64):     " + Math.sqrt(64));
        System.out.println("Power (2^3):          " + Math.pow(2, 3)); // Returns a double (8.0)
        System.out.println("Max of (10, 20):      " + Math.max(10, 20));
        System.out.println("Min of (10, 20):      " + Math.min(10, 20));
        
        // Constants
        System.out.println("Value of PI:          " + Math.PI);
        System.out.println("Value of E:           " + Math.E);
        System.out.println();


        // ---------------------------------------------------------
        // 2. ROUNDING AND PRECISION
        // Java has different ways to turn decimals into integers.
        // ---------------------------------------------------------
        System.out.println("--- 2. Rounding Methods ---");
        double num = 5.7;
        
        System.out.println("Original: " + num);
        System.out.println("Math.ceil (Up):       " + Math.ceil(num));  // 6.0
        System.out.println("Math.floor (Down):    " + Math.floor(num)); // 5.0
        System.out.println("Math.round (Nearest): " + Math.round(num)); // 6 (Returns long/int)
        System.out.println();


        // ---------------------------------------------------------
        // 3. TRIGONOMETRY
        // Note: Java Math functions use RADIANS, not DEGREES.
        // ---------------------------------------------------------
        System.out.println("--- 3. Trigonometry ---");
        
        double angleDegrees = 45.0;
        double angleRadians = Math.toRadians(angleDegrees); // Convert first!
        
        System.out.println("Sin(45): " + Math.sin(angleRadians));
        System.out.println("Cos(45): " + Math.cos(angleRadians));
        System.out.println("Tan(45): " + Math.tan(angleRadians));
        System.out.println();


        // ---------------------------------------------------------
        // 4. RANDOM NUMBERS
        // Two main ways: Math.random() (simple) and Random class (advanced).
        // ---------------------------------------------------------
        System.out.println("--- 4. Random Numbers ---");
        
        // Math.random() gives a double between 0.0 and 1.0
        double randDouble = Math.random();
        System.out.println("Math.random(): " + randDouble);
        
        // Getting a random number between 1 and 100
        int min = 1, max = 100;
        int randomRange = (int) (Math.random() * (max - min + 1)) + min;
        System.out.println("Random (1-100): " + randomRange);
        
        // Using the Random Object (Better for specialized needs)
        Random rand = new Random();
        System.out.println("Random Boolean: " + rand.nextBoolean());
        System.out.println();


        // ---------------------------------------------------------
        // 5. BIG INTEGER (Massive Whole Numbers)
        // 'long' maxes out at 9 quintillion. BigInteger has NO LIMIT (except RAM).
        // You cannot use standard operators (+, -, *) with these objects.
        // ---------------------------------------------------------
        System.out.println("--- 5. BigInteger (Huge Numbers) ---");
        
        long maxLong = Long.MAX_VALUE;
        System.out.println("Max Long: " + maxLong);
        
        BigInteger bigNum1 = new BigInteger("123456789123456789123456789");
        BigInteger bigNum2 = new BigInteger("987654321987654321987654321");
        
        // Use methods like .add(), .multiply() instead of operators
        BigInteger bigSum = bigNum1.add(bigNum2);
        System.out.println("Big Sum:  " + bigSum);
        System.out.println();


        // ---------------------------------------------------------
        // 6. BIG DECIMAL (Precise Currency Math)
        // Floats/Doubles lose precision (0.1 + 0.2 != 0.3).
        // BigDecimal is essential for financial apps.
        // ---------------------------------------------------------
        System.out.println("--- 6. BigDecimal (Money Math) ---");
        
        double a = 0.1;
        double b = 0.2;
        System.out.println("Double Math (Error): " + (a + b)); // Output: 0.30000000000000004
        
        BigDecimal moneyA = new BigDecimal("0.1");
        BigDecimal moneyB = new BigDecimal("0.2");
        
        // Precise addition
        BigDecimal correctMoney = moneyA.add(moneyB);
        System.out.println("BigDecimal (Exact):  " + correctMoney);
        
        // Precise Division with Rounding (Required for non-terminating decimals like 1/3)
        BigDecimal ten = new BigDecimal("10");
        BigDecimal three = new BigDecimal("3");
        // divide(divisor, scale, roundingMode)
        System.out.println("10 / 3 (2 decimals): " + ten.divide(three, 2, RoundingMode.HALF_UP));
    }
}