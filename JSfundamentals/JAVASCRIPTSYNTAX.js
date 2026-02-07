/* * PROJECT: Node.js CLI Task Manager
 * CONCEPTS: File I/O, Async/Await, Classes, User Input Streams, JSON Serialization
 */

const fs = require('fs').promises; // File System module (Promise version)
const path = require('path');      // Path module for handling file paths
const readline = require('readline'); // Module to read input from terminal

// Configuration
const DB_FILE = path.join(__dirname, 'tasks.json');

// --- 1. The Data Model (Class) ---
class Task {
    constructor(id, title) {
        this.id = id;
        this.title = title;
        this.completed = false;
        this.createdAt = new Date().toISOString();
    }
}

// --- 2. The Logic Controller (Class) ---
class TaskManager {
    constructor() {
        this.tasks = [];
    }

    // Load data from the hard drive
    async load() {
        try {
            const data = await fs.readFile(DB_FILE, 'utf-8');
            this.tasks = JSON.parse(data);
        } catch (error) {
            // If file doesn't exist, we start with an empty array
            if (error.code === 'ENOENT') {
                this.tasks = [];
            } else {
                throw error;
            }
        }
    }

    // Save data to the hard drive
    async save() {
        const data = JSON.stringify(this.tasks, null, 2); // Pretty print JSON
        await fs.writeFile(DB_FILE, data);
    }

    add(title) {
        const id = this.tasks.length + 1;
        const newTask = new Task(id, title);
        this.tasks.push(newTask);
        console.log(`\n[SUCCESS] Added task: "${title}"`);
    }

    list() {
        console.log('\n--- YOUR TASKS ---');
        if (this.tasks.length === 0) console.log("No tasks found.");
        
        // console.table is a built-in feature to print pretty tables
        const displayData = this.tasks.map(t => ({
            ID: t.id,
            Title: t.title,
            Status: t.completed ? "✅ DONE" : "❌ PENDING"
        }));
        console.table(displayData);
    }

    complete(id) {
        const task = this.tasks.find(t => t.id === parseInt(id));
        if (task) {
            task.completed = true;
            console.log(`\n[SUCCESS] Task ${id} marked as complete.`);
        } else {
            console.log(`\n[ERROR] Task with ID ${id} not found.`);
        }
    }
}

// --- 3. The User Interface (Input Handling) ---
// wrapping readline in a promise to make it work with async/await
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const askQuestion = (query) => {
    return new Promise(resolve => rl.question(query, resolve));
};

// --- 4. Main Execution Loop ---
async function main() {
    const manager = new TaskManager();
    console.log("Loading System...");
    await manager.load();

    let running = true;
    
    console.log("\nWelcome to JS Task Manager v1.0");

    while (running) {
        console.log("\nOptions: [1] Add Task  [2] List Tasks  [3] Complete Task  [4] Exit");
        const answer = await askQuestion("Choose an option: ");

        switch (answer.trim()) {
            case '1':
                const title = await askQuestion("Enter task title: ");
                manager.add(title);
                await manager.save(); // Save immediately
                break;
            case '2':
                manager.list();
                break;
            case '3':
                const id = await askQuestion("Enter ID to complete: ");
                manager.complete(id);
                await manager.save(); // Save immediately
                break;
            case '4':
                running = false;
                console.log("Goodbye!");
                break;
            default:
                console.log("Invalid option, try again.");
        }
    }

    rl.close();
}

// Run the application
main();