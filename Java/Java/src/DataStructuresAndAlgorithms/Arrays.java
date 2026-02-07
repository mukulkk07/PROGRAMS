package JavaDSA;

// We import the standard utility class.
// Note: Since our class is also named 'Arrays', we must refer to the standard
// library version as 'java.util.Arrays' to avoid conflicts (Shadowing).

/**
 * A Master Class demonstrating all fundamental concepts of Arrays in Java.
 * Topics covered:
 * 1. Declaration, Instantiation, Initialization
 * 2. Memory concepts (References)
 * 3. Iteration (Loops)
 * 4. Multidimensional Arrays (2D & Jagged)
 * 5. Common Operations (Sorting, Searching, Copying) via java.util.Arrays
 * 6. Passing and Returning Arrays
 */
public class Arrays {

    public static void main(String[] args) {
        System.out.println("=== 1. BASICS OF ARRAYS ===");
        basics();
        
        System.out.println("\n=== 2. ITERATION TECHNIQUES ===");
        iteration();

        System.out.println("\n=== 3. MULTIDIMENSIONAL ARRAYS ===");
        multiDimensional();

        System.out.println("\n=== 4. THE java.util.Arrays UTILITY CLASS ===");
        utilities();

        System.out.println("\n=== 5. REFERENCE & MEMORY BEHAVIOR ===");
        memoryConcepts();
        
        System.out.println("\n=== 6. PASSING & RETURNING ARRAYS ===");
        int[] result = generateArray(5);
        printArray(result);
    }

    // --- SECTION 1: BASICS ---
    public static void basics() {
        // A. Declaration: Telling the compiler "numbers" will hold an array of integers
        int[] numbers; 

        // B. Instantiation: Allocating memory for 5 integers.
        // Default values are 0 for int, false for boolean, null for objects.
        numbers = new int[5];

        // C. Initialization: Assigning values to specific indices
        numbers[0] = 10;
        numbers[1] = 20;
        numbers[2] = 30; // Indices 3 and 4 remain 0

        System.out.println("Element at index 0: " + numbers[0]);
        System.out.println("Element at index 4 (default): " + numbers[4]);

        // D. Array Literal: Declare, Instantiate, and Initialize in one line
        String[] fruits = {"Apple", "Banana", "Cherry"};
        System.out.println("First fruit: " + fruits[0]);
        
        // E. Size of Array
        // .length is a property, not a method()
        System.out.println("Length of numbers array: " + numbers.length);
        
        // F. Common Pitfall: ArrayIndexOutOfBoundsException
        try {
            numbers[100] = 0; // This index does not exist
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error caught: You tried to access an index that doesn't exist!");
        }
    }

    // --- SECTION 2: ITERATION ---
    public static void iteration() {
        int[] data = {10, 20, 30, 40, 50};

        // A. Standard For-Loop (Good if you need the index)
        System.out.print("Standard Loop: ");
        for (int i = 0; i < data.length; i++) {
            System.out.print(data[i] + " ");
        }
        System.out.println();

        // B. Enhanced For-Loop (For-Each) (Cleaner, use if index isn't needed)
        System.out.print("Enhanced Loop: ");
        for (int num : data) {
            System.out.print(num + " ");
        }
        System.out.println();
    }

    // --- SECTION 3: MULTIDIMENSIONAL ARRAYS ---
    public static void multiDimensional() {
        // A. 2D Array (Matrix) - [Rows][Columns]
        int[][] matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        System.out.println("Center element (1,1): " + matrix[1][1]); // Output: 5

        // Iterating a 2D Array
        System.out.println("Printing Matrix:");
        for (int i = 0; i < matrix.length; i++) { // Loop through rows
            for (int j = 0; j < matrix[i].length; j++) { // Loop through cols
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }

        // B. Jagged Arrays (Rows with different lengths)
        System.out.println("Jagged Array:");
        int[][] jagged = new int[3][]; // Define rows, but not columns yet
        jagged[0] = new int[] {1, 2};
        jagged[1] = new int[] {3, 4, 5, 6};
        jagged[2] = new int[] {7};

        for (int[] row : jagged) {
            System.out.println(java.util.Arrays.toString(row));
        }
    }

    // --- SECTION 4: UTILITIES (java.util.Arrays) ---
    public static void utilities() {
        int[] arr = {5, 1, 9, 3, 7};

        // A. Printing (Instead of writing a loop)
        System.out.println("Original: " + java.util.Arrays.toString(arr));

        // B. Sorting
        java.util.Arrays.sort(arr); // Uses Dual-Pivot Quicksort
        System.out.println("Sorted:   " + java.util.Arrays.toString(arr));

        // C. Binary Search (Array MUST be sorted first)
        // Returns index of element, or negative number if not found
        int index = java.util.Arrays.binarySearch(arr, 9);
        System.out.println("Found 9 at index: " + index);

        // D. Filling (Populating array with specific value)
        int[] empty = new int[5];
        java.util.Arrays.fill(empty, 99);
        System.out.println("Filled:   " + java.util.Arrays.toString(empty));
        
        // E. Comparison
        int[] arr1 = {1, 2, 3};
        int[] arr2 = {1, 2, 3};
        // Do NOT use arr1 == arr2 (compares memory address)
        boolean isEqual = java.util.Arrays.equals(arr1, arr2); 
        System.out.println("Arrays are equal by value: " + isEqual);
    }

    // --- SECTION 5: MEMORY CONCEPTS ---
    public static void memoryConcepts() {
        // Arrays are Objects. Variables store REFERENCES (Address), not the actual data.
        int[] original = {10, 20, 30};
        int[] referenceCopy = original; // Both point to the SAME memory address

        referenceCopy[0] = 999; // Modifying the copy...

        System.out.println("Original[0] after modifying copy: " + original[0]); 
        // Output is 999! Because they look at the same object.

        // To make a distinct copy:
        int[] distinctCopy = java.util.Arrays.copyOf(original, original.length);
        distinctCopy[0] = 10; // Does not affect original
        System.out.println("Distinct copy modified. Original[0] is still: " + original[0]);
    }
    
    // --- SECTION 6: METHODS ---
    
    // Returning an array from a method
    public static int[] generateArray(int size) {
        int[] newArr = new int[size];
        for(int i = 0; i < size; i++) {
            newArr[i] = i * i;
        }
        return newArr;
    }
    
    // Passing an array as a parameter
    public static void printArray(int[] arr) {
        System.out.print("Generated Array passed to method: ");
        System.out.println(java.util.Arrays.toString(arr));
    }
}