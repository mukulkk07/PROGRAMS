package JavaDSA;

import java.util.LinkedList;

/**
 * A Master Class demonstrating all fundamental concepts of Linked Lists in Java.
 * * CONTENT:
 * 1. Theory: What is a Linked List?
 * 2. Custom Implementation: Building a Singly Linked List from scratch (Nodes & Pointers).
 * 3. Java Collections Framework: Using java.util.LinkedList (Doubly Linked List).
 * 4. Performance: Arrays vs Linked Lists.
 */
public class LinkedLists {

    public static void main(String[] args) {
        System.out.println("=== 1. CUSTOM SINGLY LINKED LIST (Under the Hood) ===");
        customImplementationDemo();

        System.out.println("\n=== 2. java.util.LinkedList (Standard Library) ===");
        stdLibraryDemo();
    }

    // ==========================================================
    // SECTION 1: CUSTOM IMPLEMENTATION (SINGLY LINKED LIST)
    // ==========================================================
    
    /**
     * This method drives the custom list we built below.
     */
    public static void customImplementationDemo() {
        CustomSinglyList list = new CustomSinglyList();
        
        System.out.println("-> Inserting 10, 20, 30 at end...");
        list.addLast(10);
        list.addLast(20);
        list.addLast(30);
        list.printList(); // 10 -> 20 -> 30 -> null
        
        System.out.println("-> Inserting 5 at the beginning (Head)...");
        list.addFirst(5);
        list.printList(); // 5 -> 10 -> 20 -> 30 -> null

        System.out.println("-> Deleting the first element...");
        list.deleteFirst();
        list.printList(); // 10 -> 20 -> 30 -> null
        
        System.out.println("-> Size of list: " + list.getSize());
    }

    /**
     * The Blueprint for a Single Node.
     * Unlike Arrays, data is not stored continuously in memory.
     * A Node contains Data + A Reference (address) to the next node.
     */
    static class Node {
        int data;
        Node next; // Reference to the next node object

        public Node(int data) {
            this.data = data;
            this.next = null;
        }
    }

    /**
     * A simple implementation of a Singly Linked List.
     */
    static class CustomSinglyList {
        Node head; // The entry point to the list
        private int size;

        public CustomSinglyList() {
            this.head = null;
            this.size = 0;
        }

        // Operation: Add to End (Append) - O(n) without a tail pointer
        public void addLast(int data) {
            Node newNode = new Node(data);
            if (head == null) {
                head = newNode;
            } else {
                Node current = head;
                // Traverse to the very end
                while (current.next != null) {
                    current = current.next;
                }
                current.next = newNode; // Link the last node to the new node
            }
            size++;
        }

        // Operation: Add to Front (Prepend) - O(1)
        public void addFirst(int data) {
            Node newNode = new Node(data);
            newNode.next = head; // Point new node to current head
            head = newNode;      // Update head to be the new node
            size++;
        }

        // Operation: Delete First - O(1)
        public void deleteFirst() {
            if (head == null) {
                System.out.println("List is empty");
                return;
            }
            head = head.next; // Move head to the second node. The old head is garbage collected.
            size--;
        }

        // Operation: Traversal / Printing - O(n)
        public void printList() {
            if (head == null) {
                System.out.println("List is empty");
                return;
            }
            Node current = head;
            while (current != null) {
                System.out.print(current.data + " -> ");
                current = current.next;
            }
            System.out.println("null");
        }
        
        public int getSize() {
            return size;
        }
    }

    // ==========================================================
    // SECTION 2: STANDARD LIBRARY (java.util.LinkedList)
    // ==========================================================
    
    /**
     * Demonstration of the built-in LinkedList class.
     * Note: java.util.LinkedList is a Doubly Linked List (Nodes have prev and next pointers).
     */
    public static void stdLibraryDemo() {
        // 1. Declaration
        // We use Integer wrapper class because Collections don't support primitives (int).
        LinkedList<String> shoppingList = new LinkedList<>();

        // 2. Adding Elements
        shoppingList.add("Milk");       // Adds to end
        shoppingList.add("Bread");
        shoppingList.addFirst("Eggs");  // Adds to front
        shoppingList.addLast("Butter"); // Adds to end (same as add)
        shoppingList.add(2, "Cheese");  // Add at specific index 2

        System.out.println("Current List: " + shoppingList);

        // 3. Accessing Elements (Slower than Array!)
        // In Array: arr[2] is Instant (O(1)).
        // In Linked List: .get(2) must traverse from start (O(n)).
        String item = shoppingList.get(2); 
        System.out.println("Item at index 2: " + item);

        // 4. Removing Elements
        shoppingList.removeFirst();     // Removes "Eggs"
        shoppingList.removeLast();      // Removes "Butter"
        shoppingList.remove("Bread");   // Removes by Object
        
        System.out.println("After Removal: " + shoppingList);

        // 5. Iteration
        System.out.print("Iterating: ");
        for (String s : shoppingList) {
            System.out.print(s + " | ");
        }
        System.out.println();
        
        // 6. Linked List as a Queue (FIFO) or Stack (LIFO)
        // Because LinkedList implements Deque (Double Ended Queue)
        System.out.println("Peek (Head of list): " + shoppingList.peek());
        System.out.println("Poll (Retrieve & Remove Head): " + shoppingList.poll());
    }
}