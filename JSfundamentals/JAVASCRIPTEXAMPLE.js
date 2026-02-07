/**
 * PROJECT: Node.js System Monitor Dashboard
 * CONCEPTS: HTTP Server, API Creation, Streams, OS Interaction, Frontend Serving
 */

const http = require('http');   // Core module to create a web server
const fs = require('fs');       // Core module for file system
const os = require('os');       // Core module to access Operating System details
const path = require('path');

// Configuration
const PORT = 3000;
const LOG_FILE = path.join(__dirname, 'server_activity.log');

// --- 1. The Logger Component ---
// Appends logs to a file asynchronously
function logEvent(message) {
    const timestamp = new Date().toISOString();
    const logEntry = `[${timestamp}] ${message}\n`;
    
    // appendFile creates the file if it doesn't exist
    fs.appendFile(LOG_FILE, logEntry, (err) => {
        if (err) console.error("Logging failed:", err);
    });
}

// --- 2. The Frontend (HTML/CSS/JS) ---
// Since we aren't using a separate frontend framework, we serve the HTML as a string.
// In the real world, this would be in a separate .html file.
const FRONTEND_HTML = `
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Node.js Dashboard</title>
    <style>
        body { font-family: 'Segoe UI', sans-serif; background: #222; color: #fff; padding: 20px; }
        .card { background: #333; padding: 20px; margin-bottom: 20px; border-radius: 8px; box-shadow: 0 4px 6px rgba(0,0,0,0.3); }
        h2 { border-bottom: 2px solid #4CAF50; padding-bottom: 10px; }
        .stat { font-size: 1.5rem; margin: 10px 0; }
        .highlight { color: #4CAF50; font-weight: bold; }
        pre { background: #111; padding: 10px; height: 200px; overflow-y: scroll; color: #0f0; }
    </style>
</head>
<body>
    <div class="card">
        <h2>🖥️ System Status</h2>
        <div class="stat">OS Type: <span id="osType" class="highlight">Loading...</span></div>
        <div class="stat">Free Memory: <span id="freeMem" class="highlight">Loading...</span></div>
        <div class="stat">Server Uptime: <span id="uptime" class="highlight">Loading...</span></div>
    </div>

    <div class="card">
        <h2>📜 Live Server Logs</h2>
        <pre id="logs">Waiting for data...</pre>
    </div>

    <script>
        // CLIENT-SIDE JAVASCRIPT (Runs in Chrome/Edge, not Node)
        async function updateDashboard() {
            try {
                // Fetch stats from our Node API
                const response = await fetch('/api/stats');
                const data = await response.json();

                document.getElementById('osType').innerText = data.osType;
                document.getElementById('freeMem').innerText = data.freeMem + " MB";
                document.getElementById('uptime').innerText = data.uptime + " seconds";
                
                // Update logs text
                document.getElementById('logs').innerText = data.logs;
            } catch (e) {
                console.error("Connection lost");
            }
        }

        // Poll the server every 2 seconds
        setInterval(updateDashboard, 2000);
        updateDashboard();
    </script>
</body>
</html>
`;

// --- 3. The Web Server Logic ---
const server = http.createServer((req, res) => {
    // req = Request (what the browser sent)
    // res = Response (what we send back)

    // ROUTE 1: The Dashboard (Home Page)
    if (req.url === '/') {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(FRONTEND_HTML); // Send the HTML string to the browser
        logEvent("User accessed Dashboard");
    } 
    
    // ROUTE 2: The API (JSON Data)
    // The frontend asks for this data every 2 seconds
    else if (req.url === '/api/stats') {
        // Read the last 1000 characters of the log file to show on screen
        fs.readFile(LOG_FILE, 'utf-8', (err, logData) => {
            const safeLogs = logData || ""; // Handle empty file case
            
            // Gather Real-Time System Data
            const systemData = {
                osType: os.type() + " " + os.release(),
                totalMem: Math.round(os.totalmem() / 1024 / 1024),
                freeMem: Math.round(os.freemem() / 1024 / 1024),
                uptime: Math.floor(process.uptime()),
                logs: safeLogs.slice(-2000) // Send only last 2000 chars
            };

            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify(systemData)); // Convert Object -> JSON String
        });
    } 
    
    // ROUTE 3: 404 Not Found
    else {
        res.writeHead(404, { 'Content-Type': 'text/plain' });
        res.end("404 Not Found");
        logEvent(`404 Error: Tried to access ${req.url}`);
    }
});

// --- 4. Start the Engine ---
// delete old log file on start so it's fresh
fs.unlink(LOG_FILE, () => { 
    server.listen(PORT, () => {
        console.log(`\n--- SERVER RUNNING ---`);
        console.log(`Dashboard available at: http://localhost:${PORT}`);
        console.log(`Press Ctrl+C to stop.`);
        logEvent("Server Started");
    });
});