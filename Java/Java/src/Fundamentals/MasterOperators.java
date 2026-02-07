package JavaFun;

public class MasterOperators {

    public static void main(String[] args) {
        
        System.out.println("=== 1. CONCEPTS: OPERANDS VS OPERATORS ===");
        int a = 10;
        int b = 5;
        // In the expression "a + b":
        // "a" and "b" are OPERANDS (the data being worked on).
        // "+" is the OPERATOR (the action being performed).
        System.out.println("Operands: " + a + ", " + b);
        System.out.println("Operator: + ");
        System.out.println("Result: " + (a + b));
        System.out.println("------------------------------------------------\n");


        System.out.println("=== 2. ARITHMETIC OPERATORS (Math) ===");
        // +, -, *, /, %
        System.out.println("Addition (a + b):       " + (a + b));
        System.out.println("Subtraction (a - b):    " + (a - b));
        System.out.println("Multiplication (a * b): " + (a * b));
        
        // Division Note: Integer division chops off decimals!
        System.out.println("Int Division (10 / 4):  " + (10 / 4)); // Output is 2
        System.out.println("Real Division (10.0/4): " + (10.0 / 4)); // Output is 2.5
        
        // Modulo (%): Returns the REMAINDER
        System.out.println("Modulo (10 % 3):        " + (10 % 3)); // 10 divided by 3 is 3 remainder 1
        System.out.println("------------------------------------------------\n");


        System.out.println("=== 3. UNARY OPERATORS (One Operand) ===");
        // ++, --, !, -
        int count = 10;
        
        System.out.println("Original count: " + count);
        System.out.println("Post-Increment (count++): " + (count++)); // Prints 10, THEN becomes 11
        System.out.println("Value is now: " + count);
        
        System.out.println("Pre-Increment (++count):  " + (++count)); // Becomes 12, THEN prints 12
        
        boolean isJavaFun = true;
        System.out.println("Logical NOT (!isJavaFun): " + (!isJavaFun)); // Inverts boolean
        System.out.println("------------------------------------------------\n");


        System.out.println("=== 4. RELATIONAL OPERATORS (Comparison) ===");
        // ==, !=, >, <, >=, <= (Always returns true or false)
        int x = 10;
        int y = 20;

        System.out.println("Is x equal to y? (x == y):     " + (x == y));
        System.out.println("Is x NOT equal to y? (x != y): " + (x != y));
        System.out.println("Is x greater than y? (x > y):  " + (x > y));
        System.out.println("------------------------------------------------\n");


        System.out.println("=== 5. LOGICAL OPERATORS (Logic Gates) ===");
        // && (AND), || (OR)
        boolean hasLicense = true;
        boolean hasCar = false;

        // AND (&&): Both must be true
        System.out.println("Can drive? (License && Car): " + (hasLicense && hasCar));

        // OR (||): At least one must be true
        System.out.println("Can commute? (License || Car): " + (hasLicense || hasCar));
        System.out.println("------------------------------------------------\n");


        System.out.println("=== 6. TERNARY OPERATOR (Short IF-ELSE) ===");
        // variable = (condition) ? valueIfTrue : valueIfFalse;
        int age = 18;
        String status = (age >= 18) ? "Adult" : "Minor";
        
        System.out.println("Age is " + age + ", so status is: " + status);
        System.out.println("------------------------------------------------\n");


        System.out.println("=== 7. ASSIGNMENT OPERATORS (Shortcuts) ===");
        // =, +=, -=, *=
        int num = 10;
        num += 5; // Same as: num = num + 5;
        System.out.println("num += 5 results in: " + num);
        
        num *= 2; // Same as: num = num * 2;
        System.out.println("num *= 2 results in: " + num);
        System.out.println("------------------------------------------------\n");
    }
}