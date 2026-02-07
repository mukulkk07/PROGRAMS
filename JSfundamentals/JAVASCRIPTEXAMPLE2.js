/**
 * PROJECT: Node.js TCP LAN Chatroom
 * CONCEPTS: TCP Sockets, Streams, Buffers, Piping, Process Arguments
 */

const net = require('net');       // Core module for raw network communication
const readline = require('readline');

// Configuration
const CONFIG = {
    port: 9000,
    host: '127.0.0.1' // Localhost
};

// We check the command line arguments to see what mode to run
// Usage: "node chat.js server" OR "node chat.js client <Username>"
const mode = process.argv[2]; 

if (mode === 'server') {
    runServer();
} else if (mode === 'client') {
    const username = process.argv[3] || "Anonymous";
    runClient(username);
} else {
    console.log("Usage:");
    console.log("  Run Server: node chat.js server");
    console.log("  Run Client: node chat.js client <YourName>");
}

/* ----------------------------------------------------------------
 * PART 1: THE SERVER (The Hub)
 * - Listens for connections
 * - Broadcasts messages to everyone connected
 * ---------------------------------------------------------------- */
function runServer() {
    // Array to keep track of all connected users (sockets)
    const clients = [];

    const server = net.createServer((socket) => {
        // 'socket' is the actual connection object for a specific user
        
        // 1. Handshake
        socket.name = `User-${socket.remotePort}`;
        clients.push(socket);
        
        const welcomeMsg = `[SYSTEM]: New user joined from ${socket.remotePort}\n`;
        console.log(welcomeMsg.trim());
        broadcast(welcomeMsg, socket); // Tell everyone else

        // 2. Handle Incoming Data (Messages)
        socket.on('data', (data) => {
            // Data comes in as binary "Buffer", convert to String
            const message = data.toString();
            broadcast(message, socket);
        });

        // 3. Handle Disconnect
        socket.on('end', () => {
            clients.splice(clients.indexOf(socket), 1); // Remove from list
            const leftMsg = `[SYSTEM]: ${socket.name} left the chat.\n`;
            console.log(leftMsg.trim());
            broadcast(leftMsg, socket);
        });

        // 4. Handle Errors (e.g., sudden crash of client)
        socket.on('error', (err) => {
            // Just ignore connection resets, don't crash the server
            if (err.code !== 'ECONNRESET') console.error(err);
        });
    });

    // Helper function to send a message to everyone EXCEPT the sender
    function broadcast(message, senderSocket) {
        clients.forEach(client => {
            if (client !== senderSocket) {
                client.write(message);
            }
        });
    }

    server.listen(CONFIG.port, () => {
        console.log(`\n--- CHAT SERVER STARTED on Port ${CONFIG.port} ---`);
        console.log("Waiting for connections...");
    });
}

/* ----------------------------------------------------------------
 * PART 2: THE CLIENT (The User)
 * - Connects to the server
 * - Sends keyboard input to server
 * - Prints server messages to screen
 * ---------------------------------------------------------------- */
function runClient(username) {
    const client = new net.Socket();

    client.connect(CONFIG.port, CONFIG.host, () => {
        console.log(`\n--- Connected to Chat as ${username} ---`);
        console.log("Type a message and press ENTER. (Ctrl+C to exit)\n");
        
        // Send a notification that we joined (sets the name on the server effectively)
        client.write(`[SYSTEM]: ${username} has joined the room.\n`);
    });

    // RECEIVING: When the server sends data, print it
    client.on('data', (data) => {
        // 'process.stdout.write' is like console.log but doesn't force a new line
        process.stdout.write(data); 
    });

    // SENDING: Read from keyboard (stdin) and send to Server
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    // When user hits Enter
    rl.on('line', (line) => {
        // Move cursor up one line to prevent double-printing your own text
        readline.moveCursor(process.stdout, 0, -1);
        readline.clearLine(process.stdout, 0);

        // Format: [Name]: Message
        const fullMessage = `[${username}]: ${line}\n`;
        
        // Show it on my own screen
        console.log(`[Me]: ${line}`);
        
        // Send it to the server (to show everyone else)
        client.write(fullMessage);
    });

    client.on('close', () => {
        console.log('\n--- Connection closed ---');
        process.exit(0);
    });
}