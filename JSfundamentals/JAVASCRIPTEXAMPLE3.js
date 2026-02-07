/**
 * PROJECT: NodeChain (A Custom Blockchain Implementation)
 * CONCEPTS: Cryptography, Linked Lists, Proof-of-Work, Data Integrity
 */

const crypto = require('crypto'); // Built-in Node.js module for encryption

// --- 1. The Block (The Container) ---
class Block {
    constructor(index, timestamp, data, previousHash = '') {
        this.index = index;
        this.timestamp = timestamp;
        this.data = data;              // Transaction details (e.g., "A paid B $10")
        this.previousHash = previousHash; // Link to the block before this one
        this.hash = this.calculateHash(); // The unique ID of *this* block
        this.nonce = 0;                // A random number used for mining
    }

    // Creates a unique fingerprint (Hash) based on the block's contents
    calculateHash() {
        const rawData = this.index + this.previousHash + this.timestamp + JSON.stringify(this.data) + this.nonce;
        // Uses SHA256 algorithm (same as Bitcoin)
        return crypto.createHash('sha256').update(rawData).digest('hex');
    }

    // PROOF OF WORK: The "Mining" process.
    // We force the computer to recalculate the hash over and over until
    // it finds one that starts with enough zeros (difficulty).
    mineBlock(difficulty) {
        const target = Array(difficulty + 1).join("0"); // e.g., "0000"
        
        console.log(`⛏️  Mining Block ${this.index}...`);
        const start = Date.now();

        while (this.hash.substring(0, difficulty) !== target) {
            this.nonce++; // Change one tiny variable...
            this.hash = this.calculateHash(); // ...to get a completely new hash result
        }

        const end = Date.now();
        console.log(`✅ BLOCK MINED: ${this.hash}`);
        console.log(`   Time taken: ${(end - start)}ms | Nonce: ${this.nonce}\n`);
    }
}

// --- 2. The Chain (The Ledger) ---
class Blockchain {
    constructor() {
        this.chain = [this.createGenesisBlock()]; // Start with the first block
        this.difficulty = 4; // Higher number = Slower mining (more security)
    }

    createGenesisBlock() {
        return new Block(0, "01/01/2026", "Genesis Block", "0");
    }

    getLatestBlock() {
        return this.chain[this.chain.length - 1];
    }

    addBlock(newBlock) {
        // 1. Link to the previous block
        newBlock.previousHash = this.getLatestBlock().hash;
        
        // 2. Mine the block (Make it valid)
        newBlock.mineBlock(this.difficulty);
        
        // 3. Add to chain
        this.chain.push(newBlock);
    }

    // SECURITY CHECK: Scans the entire chain to ensure no data was altered
    isChainValid() {
        for (let i = 1; i < this.chain.length; i++) {
            const currentBlock = this.chain[i];
            const previousBlock = this.chain[i - 1];

            // Check 1: Did someone tamper with the data inside the block?
            // If data changes, the hash recalculation will yield a different result.
            if (currentBlock.hash !== currentBlock.calculateHash()) {
                return false;
            }

            // Check 2: Is the block pointing to the correct previous block?
            // If the previous block changed, its hash changed, breaking this link.
            if (currentBlock.previousHash !== previousBlock.hash) {
                return false;
            }
        }
        return true;
    }
}

// --- 3. Simulation (Running the System) ---

// Setup ANSI Colors for terminal output
const RED = '\x1b[31m';
const GREEN = '\x1b[32m';
const CYAN = '\x1b[36m';
const RESET = '\x1b[0m';

console.log(`${CYAN}--- INITIALIZING NODECHAIN v1.0 ---${RESET}\n`);

const myCoin = new Blockchain();

// 1. Add some valid blocks
console.log("Adding Block 1...");
myCoin.addBlock(new Block(1, "20/07/2026", { amount: 100, sender: "Alice", receiver: "Bob" }));

console.log("Adding Block 2...");
myCoin.addBlock(new Block(2, "22/07/2026", { amount: 50, sender: "Bob", receiver: "Charlie" }));

// 2. Print the Valid Chain
console.log(`${CYAN}--- CURRENT BLOCKCHAIN DATA ---${RESET}`);
console.log(JSON.stringify(myCoin, null, 4));

console.log(`\nIs blockchain valid? ${GREEN}${myCoin.isChainValid()}${RESET}`);

// 3. SIMULATE A HACK ATTACK
console.log(`\n${RED}!!! HACKER ATTACK INITIATED !!!${RESET}`);
console.log("Attempting to change Block 1 transaction (Alice -> Bob)...");

// Hacker changes the data directly in memory
myCoin.chain[1].data = { amount: 100000, sender: "Alice", receiver: "HACKER" };

// Hacker tries to cover tracks by recalculating the hash for that block
// (But they fail because they can't re-mine the entire chain fast enough)
myCoin.chain[1].hash = myCoin.chain[1].calculateHash();

console.log(`\nIs blockchain valid after attack? ${RED}${myCoin.isChainValid()}${RESET}`);
if (!myCoin.isChainValid()) {
    console.log(`${RED}[SYSTEM ALERT] Tampering detected! The chain is broken.${RESET}`);
}