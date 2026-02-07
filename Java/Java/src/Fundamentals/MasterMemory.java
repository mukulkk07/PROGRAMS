package JavaFun;

// A simple class to represent an object on the Heap
class DataObject {
    int id;
    String name;

    DataObject(int id, String name) {
        this.id = id;
        this.name = name;
    }

    // This method runs when the Garbage Collector deletes this object
    @Override
    protected void finalize() {
        System.out.println("   [GC Alert] Object ID " + id + " (" + name + ") is being collected from Heap.");
    }
}

public class MasterMemory {

    public static void main(String[] args) {
        
        System.out.println("=== JAVA MEMORY MANAGEMENT MASTERCLASS ===\n");

        // ---------------------------------------------------------
        // 1. STACK MEMORY (Primitives)
        // Primitives live directly on the Stack. They store the ACTUAL value.
        // ---------------------------------------------------------
        System.out.println("--- 1. Stack Memory (Primitives) ---");
        int x = 10;
        int y = x; // A COPY of the value 10 is made. 'y' is independent of 'x'.
        y = 20;    // Changing 'y' does NOT affect 'x'.
        
        System.out.println("x: " + x + " (Unchanged)");
        System.out.println("y: " + y + " (Changed)");
        System.out.println("Reason: Primitives store values, not references.\n");


        // ---------------------------------------------------------
        // 2. HEAP MEMORY (Objects & References)
        // Objects live on the Heap. Variables on the Stack store the ADDRESS (Reference).
        // ---------------------------------------------------------
        System.out.println("--- 2. Heap Memory (References) ---");
        DataObject obj1 = new DataObject(1, "Original");
        DataObject obj2 = obj1; // Copies the REFERENCE (Address), not the object!

        // Both obj1 and obj2 point to the SAME object in the Heap.
        obj2.name = "Modified"; 
        
        System.out.println("obj1 name: " + obj1.name); // Prints "Modified"
        System.out.println("obj2 name: " + obj2.name);
        System.out.println("Reason: Both variables point to the same Heap address.\n");


        // ---------------------------------------------------------
        // 3. PASS BY VALUE (The Golden Rule)
        // Java ALWAYS passes by value. For objects, it passes the value of the REFERENCE.
        // ---------------------------------------------------------
        System.out.println("--- 3. Function Calls & Memory ---");
        modifyPrimitive(x);
        System.out.println("x after function call: " + x + " (Unchanged)");
        
        modifyObject(obj1);
        System.out.println("obj1 after function call: " + obj1.name + " (Changed!)");
        System.out.println();


        // ---------------------------------------------------------
        // 4. GARBAGE COLLECTION (GC)
        // Java automatically deletes objects when they have no references pointing to them.
        // ---------------------------------------------------------
        System.out.println("--- 4. Garbage Collection Demo ---");
        
        // Creating an object inside a limited scope
        createTemporaryObject();
        
        // At this point, the object created inside the method is "Unreachable".
        // The variable 'temp' was popped off the Stack, so the link is broken.
        
        System.out.println("Requesting Garbage Collection...");
        System.gc(); // Suggests JVM to run the Garbage Collector (not guaranteed instantly)
        
        // Small pause to let GC run (for demo purposes only)
        try { Thread.sleep(1000); } catch (InterruptedException e) {}
        
        System.out.println("End of Program.");
    }

    // Method to demonstrate primitive passing
    static void modifyPrimitive(int num) {
        num = 999; // Changes the COPY inside this method only
    }

    // Method to demonstrate object passing
    static void modifyObject(DataObject d) {
        d.name = "ChangedInsideMethod"; // Follows the reference and changes the actual object
    }
    
    // Method to create an object that will be destroyed
    static void createTemporaryObject() {
        DataObject temp = new DataObject(2, "Temporary");
        System.out.println("   Inside method: Created " + temp.name);
    } // 'temp' variable is destroyed here. The Object remains on Heap, but lost.
}