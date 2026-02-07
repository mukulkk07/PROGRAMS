/**
 * PROJECT: High-Performance Server Cluster
 * CONCEPTS: Multi-threading, Load Balancing, CPU Forks, Shared Ports, Stress Testing
 */

const cluster = require('cluster'); // Core module to manage threads
const http = require('http');
const os = require('os');

// --- CONFIGURATION ---
const PORT = 8000;

/* * PART 1: THE MASTER PROCESS (The Manager)
 * The Master's only job is to create workers and replace them if they die.
 */
if (cluster.isPrimary) {
    const numCPUs = os.cpus().length; // Detect your hardware (e.g., 8 cores)
    
    console.log(`\n--- 🚀 SYSTEM DETECTED ${numCPUs} CPU CORES ---`);
    console.log(`Master Process (PID: ${process.pid}) is setting up the farm...`);

    // Fork a worker for every CPU core
    for (let i = 0; i < numCPUs; i++) {
        cluster.fork();
    }

    // Listen for workers coming online
    cluster.on('online', (worker) => {
        console.log(`✅ Worker ${worker.process.pid} is online and ready.`);
    });

    // AUTO-RECOVERY: If a worker crashes (dies), spawn a new one immediately!
    cluster.on('exit', (worker, code, signal) => {
        console.log(`❌ Worker ${worker.process.pid} died. Spawning replacement...`);
        cluster.fork();
    });

    console.log(`\n[Load Balancer Active] listening on http://localhost:${PORT}`);
    console.log(`Open your browser and refresh rapidly to see different IDs!\n`);

} 
/* * PART 2: THE WORKER PROCESS (The Employee)
 * This code runs on EACH of your CPU cores simultaneously.
 */
else {
    // Each worker shares the same Port 8000. 
    // The OS automatically distributes incoming traffic between them.
    http.createServer((req, res) => {
        
        // ROUTE 1: A light task (Fast)
        if (req.url === '/') {
            res.writeHead(200);
            res.end(`Handled by Worker ${process.pid} (I am fast!)`);
        } 
        
        // ROUTE 2: A CPU-Intensive task (Simulating heavy calculation)
        // If this was single-threaded, this would FREEZE the whole server.
        // In a cluster, only ONE worker freezes; the others keep serving!
        else if (req.url === '/heavy') {
            const start = Date.now();
            
            // Calculate a massive Fibonacci number to burn CPU cycles
            const result = calculateFibonacci(43); 
            
            const duration = Date.now() - start;
            res.writeHead(200);
            res.end(`Worker ${process.pid} finished heavy task in ${duration}ms. Result: ${result}`);
        }

        // ROUTE 3: Simulate a Crash
        else if (req.url === '/kill') {
            res.end(`Worker ${process.pid} is committing suicide...`);
            process.exit(1); // Crashes this specific worker
        }

    }).listen(PORT);
}

// --- HELPER FUNCTION: Heavy Math ---
function calculateFibonacci(n) {
    if (n <= 1) return 1;
    return calculateFibonacci(n - 1) + calculateFibonacci(n - 2);
}