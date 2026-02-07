/**
 * PROJECT: Terminal Snake (Node.js Arcade Game)
 * CONCEPTS: Game Loops, Raw Mode TTY, 2D Coordinate Systems, Collision Logic
 */

const readline = require('readline');

// --- CONFIGURATION ---
const BOARD_WIDTH = 30;
const BOARD_HEIGHT = 15;
const SPEED = 100; // Milliseconds per frame (Lower = Faster)

// ANSI Color Codes for Graphics
const COLORS = {
    Reset: "\x1b[0m",
    Snake: "\x1b[32m", // Green
    Food: "\x1b[31m",  // Red
    Border: "\x1b[37m",// White
    Text: "\x1b[36m"   // Cyan
};

class Game {
    constructor() {
        // Game State
        this.score = 0;
        this.gameOver = false;
        
        // Snake State (Array of coordinates)
        // Head is at index 0
        this.snake = [
            { x: 10, y: 5 }, // Head
            { x: 9, y: 5 },  // Body
            { x: 8, y: 5 }   // Tail
        ];

        // Direction: x: 1 = Right, -1 = Left | y: 1 = Down, -1 = Up
        this.direction = { x: 1, y: 0 }; 
        
        this.food = this.generateFood();

        // Setup Input
        this.setupInput();
    }

    setupInput() {
        readline.emitKeypressEvents(process.stdin);
        
        // "Raw Mode" allows us to capture keys without pressing Enter
        if (process.stdin.setRawMode) {
            process.stdin.setRawMode(true);
        }

        process.stdin.on('keypress', (str, key) => {
            if (key.ctrl && key.name === 'c') process.exit(); // Allow quitting

            // Prevent reversing directly into oneself (e.g., can't go Left if going Right)
            const dir = this.direction;
            
            switch (key.name) {
                case 'up':
                    if (dir.y === 0) this.direction = { x: 0, y: -1 };
                    break;
                case 'down':
                    if (dir.y === 0) this.direction = { x: 0, y: 1 };
                    break;
                case 'left':
                    if (dir.x === 0) this.direction = { x: -1, y: 0 };
                    break;
                case 'right':
                    if (dir.x === 0) this.direction = { x: 1, y: 0 };
                    break;
            }
        });
    }

    generateFood() {
        // Keep generating random spots until we find one not occupied by the snake
        let newFood;
        while (true) {
            newFood = {
                x: Math.floor(Math.random() * BOARD_WIDTH),
                y: Math.floor(Math.random() * BOARD_HEIGHT)
            };

            // Check if food spawned inside snake body
            const collision = this.snake.some(segment => segment.x === newFood.x && segment.y === newFood.y);
            if (!collision) break;
        }
        return newFood;
    }

    update() {
        if (this.gameOver) return;

        // 1. Calculate new Head Position based on velocity
        const head = this.snake[0];
        const newHead = {
            x: head.x + this.direction.x,
            y: head.y + this.direction.y
        };

        // 2. Check Death Conditions
        // Hit Walls
        if (newHead.x < 0 || newHead.x >= BOARD_WIDTH || newHead.y < 0 || newHead.y >= BOARD_HEIGHT) {
            this.gameOver = true;
            return;
        }
        // Hit Self (Loop through body to see if newHead matches any segment)
        for (let segment of this.snake) {
            if (newHead.x === segment.x && newHead.y === segment.y) {
                this.gameOver = true;
                return;
            }
        }

        // 3. Move Snake
        // Add new head to the front of the array
        this.snake.unshift(newHead);

        // 4. Check Food
        if (newHead.x === this.food.x && newHead.y === this.food.y) {
            this.score += 10;
            this.food = this.generateFood();
            // Don't pop the tail, so snake grows!
        } else {
            // Remove the tail to maintain length (movement)
            this.snake.pop();
        }
    }

    draw() {
        // Clear screen logic (Optimized for different terminals)
        // \x1b[2J = Clear entire screen, \x1b[0f = Move cursor to top-left
        process.stdout.write('\x1b[2J\x1b[0f');

        // Draw Title
        console.log(`${COLORS.Text}--- NODE.JS SNAKE --- Score: ${this.score}${COLORS.Reset}\n`);

        // Draw Board
        let output = "";
        
        // Top Border
        output += COLORS.Border + "+" + "-".repeat(BOARD_WIDTH) + "+\n" + COLORS.Reset;

        for (let y = 0; y < BOARD_HEIGHT; y++) {
            output += COLORS.Border + "|" + COLORS.Reset; // Left Edge
            
            for (let x = 0; x < BOARD_WIDTH; x++) {
                let char = " ";
                
                // Is this coordinate the Snake Head?
                if (this.snake[0].x === x && this.snake[0].y === y) {
                    char = `${COLORS.Snake}O${COLORS.Reset}`;
                }
                // Is this coordinate a Snake Body part?
                else if (this.snake.some(s => s.x === x && s.y === y)) {
                    char = `${COLORS.Snake}o${COLORS.Reset}`;
                }
                // Is this coordinate Food?
                else if (this.food.x === x && this.food.y === y) {
                    char = `${COLORS.Food}*${COLORS.Reset}`;
                }

                output += char;
            }
            
            output += COLORS.Border + "|\n" + COLORS.Reset; // Right Edge
        }

        // Bottom Border
        output += COLORS.Border + "+" + "-".repeat(BOARD_WIDTH) + "+" + COLORS.Reset;

        if (this.gameOver) {
            output += `\n\n${COLORS.Food}GAME OVER!${COLORS.Reset}`;
            output += `\nFinal Score: ${this.score}`;
            output += `\nPress Ctrl+C to exit.`;
        }

        process.stdout.write(output);
    }

    start() {
        setInterval(() => {
            this.update();
            this.draw();
            if (this.gameOver) {
                // We don't stop the interval, so the "Game Over" text persists
                // But update() stops processing logic.
            }
        }, SPEED);
    }
}

// Start the game
new Game().start();