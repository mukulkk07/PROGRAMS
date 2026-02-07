package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"net"
	"os"
)

// Configuration
const (
	address = "localhost:9000"
	typeMsg = "MSG"
)

// --- MAIN ENTRY POINT ---
func main() {
	// Flags to decide mode
	isServer := flag.Bool("server", false, "Run as the chat server")
	username := flag.String("user", "Anon", "Your username (client mode)")
	flag.Parse()

	if *isServer {
		startServer()
	} else {
		startClient(*username)
	}
}

// ==========================================
//              SERVER LOGIC
// ==========================================

// A channel to broadcast messages to all connected clients
var globalMessageChan = make(chan string)

// A list of connected clients (map of IP address -> connection)
var clients = make(map[net.Conn]bool)

func startServer() {
	fmt.Println("--- Chat Server Started on", address, "---")

	listener, err := net.Listen("tcp", address)
	if err != nil {
		log.Fatal(err)
	}

	// 1. Broadcaster Goroutine
	// It sits in the background and sends messages to everyone
	go func() {
		for msg := range globalMessageChan {
			fmt.Println("Broadcasting:", msg) // Log on server
			for client := range clients {
				fmt.Fprintln(client, msg) // Send to network
			}
		}
	}()

	// 2. Connection Accepter Loop
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Println(err)
			continue
		}

		clients[conn] = true

		// Handle each user in their own thread
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	defer conn.Close()
	defer delete(clients, conn) // Remove user when they leave

	// Announce arrival
	globalMessageChan <- ">> New user joined: " + conn.RemoteAddr().String()

	input := bufio.NewScanner(conn)
	for input.Scan() {
		// When user types something, send it to the global channel
		msg := input.Text()
		globalMessageChan <- msg
	}
}

// ==========================================
//              CLIENT LOGIC
// ==========================================

func startClient(name string) {
	fmt.Println("--- Connecting to Chat Server ---")

	conn, err := net.Dial("tcp", address)
	if err != nil {
		log.Fatal("Could not connect. Is the server running? ", err)
	}
	defer conn.Close()

	fmt.Println("Connected! Type a message and press Enter.")

	// 1. Listener Goroutine (Incoming messages)
	// listens for messages FROM the server
	go func() {
		serverReader := bufio.NewScanner(conn)
		for serverReader.Scan() {
			fmt.Println(serverReader.Text())
		}
	}()

	// 2. Sender Loop (Outgoing messages)
	// listens for keyboard input
	keyboard := bufio.NewScanner(os.Stdin)
	for keyboard.Scan() {
		text := keyboard.Text()
		if text == "quit" {
			break
		}
		// Send formatted message to server
		fmt.Fprintf(conn, "[%s]: %s\n", name, text)
	}
}
