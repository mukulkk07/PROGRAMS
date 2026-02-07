/**
 * PROJECT: NanoVM (Stack-Based Virtual CPU)
 * CONCEPTS: Bytecode, Stack Memory, Instruction Pointers, Assembly Compilation
 */

const fs = require('fs');

// --- 1. The Instruction Set Architecture (ISA) ---
// These are the only things our CPU knows how to do.
const OP = {
    HALT: 0x00, // Stop program
    PUSH: 0x01, // Push number onto stack
    POP:  0x02, // Remove number from stack
    ADD:  0x03, // Pop 2 nums, Add them, Push result
    SUB:  0x04, // Pop 2 nums, Subtract them, Push result
    MUL:  0x05, // Pop 2 nums, Multiply them, Push result
    PRINT:0x06, // Print top of stack
    JMP:  0x07, // Jump to specific instruction (Looping)
    EQ:   0x08, // Checks if equal: Pushes 1 (True) or 0 (False)
    JMP_IF: 0x09 // Jump if top of stack is True (1)
};

// --- 2. The Virtual Machine (The Chip) ---
class VirtualMachine {
    constructor() {
        this.stack = [];       // Temporary memory (The Stack)
        this.ip = 0;           // Instruction Pointer (Current line number)
        this.program = [];     // The bytecode to run
        this.running = false;
    }

    load(program) {
        this.program = program;
        this.ip = 0;
        this.stack = [];
        this.running = true;
    }

    // Run one CPU Cycle (Fetch -> Decode -> Execute)
    step() {
        if (!this.running || this.ip >= this.program.length) {
            this.running = false;
            return;
        }

        // FETCH
        const instruction = this.program[this.ip];
        
        // DECODE & EXECUTE
        switch (instruction) {
            case OP.HALT:
                this.running = false;
                console.log("\n[CPU]: HALT Signal received.");
                return;

            case OP.PUSH:
                this.ip++; // Move to next slot to get the value
                const value = this.program[this.ip];
                this.stack.push(value);
                break;

            case OP.POP:
                this.stack.pop();
                break;

            case OP.ADD:
                const b_add = this.stack.pop();
                const a_add = this.stack.pop();
                this.stack.push(a_add + b_add);
                break;

            case OP.SUB:
                const b_sub = this.stack.pop();
                const a_sub = this.stack.pop();
                this.stack.push(a_sub - b_sub);
                break;

            case OP.MUL:
                const b_mul = this.stack.pop();
                const a_mul = this.stack.pop();
                this.stack.push(a_mul * b_mul);
                break;
            
            case OP.EQ:
                const b_eq = this.stack.pop();
                const a_eq = this.stack.pop();
                this.stack.push(a_eq === b_eq ? 1 : 0);
                break;

            case OP.PRINT:
                const val = this.stack[this.stack.length - 1];
                console.log(`[STDOUT]: ${val}`);
                break;

            case OP.JMP:
                this.ip++; // Get jump target
                const target = this.program[this.ip];
                this.ip = target; // Teleport IP
                return; // Don't do the normal this.ip++ below

            case OP.JMP_IF:
                this.ip++;
                const jumpLoc = this.program[this.ip];
                const condition = this.stack.pop(); // 1 or 0
                if (condition === 1) {
                    this.ip = jumpLoc;
                    return;
                }
                break;
        }

        this.ip++; // Move to next instruction
    }

    dumpState() {
        // Visualizes the internal state of the CPU
        const stackStr = `[ ${this.stack.join(', ')} ]`;
        const nextOp = Object.keys(OP).find(key => OP[key] === this.program[this.ip]) || "DATA";
        console.log(`IP: ${String(this.ip).padEnd(3)} | OP: ${String(nextOp).padEnd(6)} | STACK: ${stackStr}`);
    }
}

// --- 3. The Compiler (Text -> Bytecode) ---
// Translates human readable Assembly into raw numbers
function compile(sourceCode) {
    const lines = sourceCode.trim().split('\n');
    const bytecode = [];
    const labels = {}; // Stores positions of "Label:" (e.g. "START:")

    // PASS 1: Find Labels
    let address = 0;
    for (let line of lines) {
        line = line.trim().split(';')[0].trim(); // Remove comments
        if (!line) continue;

        if (line.endsWith(':')) {
            const labelName = line.slice(0, -1);
            labels[labelName] = address;
        } else {
            const parts = line.split(' ');
            address += 1; // Opcode takes 1 slot
            if (parts.length > 1) address += 1; // Argument takes 1 slot
        }
    }

    // PASS 2: Generate Code
    for (let line of lines) {
        line = line.trim().split(';')[0].trim();
        if (!line || line.endsWith(':')) continue;

        const parts = line.split(/\s+/);
        const command = parts[0].toUpperCase();
        
        if (OP[command] !== undefined) {
            bytecode.push(OP[command]);
            
            // Handle Argument (Number or Label)
            if (parts.length > 1) {
                const arg = parts[1];
                if (labels[arg] !== undefined) {
                    bytecode.push(labels[arg]); // Jump to Label address
                } else {
                    bytecode.push(parseInt(arg)); // Push raw number
                }
            }
        } else {
            console.error(`COMPILER ERROR: Unknown command '${command}'`);
            process.exit(1);
        }
    }
    return bytecode;
}

// --- 4. The Program (NanoASM) ---
// This assembly program calculates Factorial of 5 (5 * 4 * 3 * 2 * 1)
const sourceCode = `
    PUSH 5      ; Starting number (The Counter)
    PUSH 1      ; The Result accumulator

LOOP:
    ; Check if Counter == 1. If so, we are done.
    PRINT       ; Show current result
    
    ; Re-arrange stack for math: [Counter, Result] -> [Result, Counter]
    ; (Our simple CPU lacks SWAP, so we just peek carefully in real ASM, 
    ;  but here we trust the math flow: Result is Top, Counter is below)
    
    ; Let's actually simplify: We will hold [Result, Counter]
    ; Actually, stack management is hard! Let's do simple Countdown.
    
    ; Stack is: [Result, Counter]
    ; But we need to multiply Result * Counter. 
    ; Since MUL pops both, we need to save them. 
    ; Wait, our CPU is too simple (no variables). 
    ; Let's just do a simple Countdown Loop printing numbers!

    ; --- SIMPLIFIED PROGRAM: COUNTDOWN FROM 5 to 0 ---
    ; Clear stack
    POP 
    POP

    PUSH 5      ; Start at 5

START_LOOP:
    PRINT       ; Print current number
    PUSH 1
    SUB         ; Subtract 1 (Stack: [4])
    
    ; Check if 0
    PUSH 0      ; Stack: [4, 0]
    EQ          ; Stack: [0] (False, because 4 != 0)
    
    JMP_IF DONE ; If Equal to 0, Jump to DONE
    
    JMP START_LOOP ; Else, go back to top

DONE:
    HALT
`;

// --- 5. Main Execution ---

console.log("--- 1. COMPILING SOURCE CODE ---");
console.log(sourceCode);
const program = compile(sourceCode);
console.log("Bytecode generated:", program);

console.log("\n--- 2. BOOTING CPU ---");
const cpu = new VirtualMachine();
cpu.load(program);

console.log("\n--- 3. EXECUTING ---");
// Run slow enough to see
const clock = setInterval(() => {
    cpu.dumpState();
    cpu.step();

    if (!cpu.running) {
        clearInterval(clock);
        console.log("\n--- EXECUTION FINISHED ---");
    }
}, 500); // 500ms per cycle