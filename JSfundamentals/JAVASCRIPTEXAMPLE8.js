/**
 * PROJECT: Newton's Sandbox (2D Physics Engine)
 * CONCEPTS: Vectors, Velocity, Acceleration, Gravity, Elastic collision
 */

const readline = require('readline');

// --- CONFIGURATION ---
const WIDTH = 60;
const HEIGHT = 20;
const FPS = 30;
const GRAVITY = 0.8;      // Downward force
const FRICTION = 0.99;    // Air resistance (1.0 = vacuum, 0.9 = thick air)
const BOUNCE = 0.75;      // Energy kept after hitting floor (0.75 = 75%)

// --- 1. The Math Core (Vector Class) ---
class Vector {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }

    add(v) {
        this.x += v.x;
        this.y += v.y;
    }
}

// --- 2. The Physical Object ---
class Ball {
    constructor(id, x, y) {
        this.id = id; // The character to draw (e.g., "@" or "O")
        this.pos = new Vector(x, y);      // Position
        this.vel = new Vector(1, 0);      // Velocity (Speed + Direction)
        this.acc = new Vector(0, 0);      // Acceleration (Force changing the speed)
    }

    applyForce(forceX, forceY) {
        this.acc.x += forceX;
        this.acc.y += forceY;
    }

    update() {
        // 1. Apply Gravity
        this.applyForce(0, GRAVITY);

        // 2. Add Acceleration to Velocity
        this.vel.add(this.acc);
        
        // 3. Apply Air Friction
        this.vel.x *= FRICTION;
        this.vel.y *= FRICTION;

        // 4. Add Velocity to Position (Move the object)
        this.pos.add(this.vel);

        // 5. Reset Acceleration (Forces must be reapplied every frame)
        this.acc.x = 0;
        this.acc.y = 0;

        // --- COLLISION DETECTION (The Floor) ---
        if (this.pos.y >= HEIGHT - 1) {
            this.pos.y = HEIGHT - 1; // Snap to floor (prevent sinking)
            
            // Reverse velocity (Bounce up)
            // Multiply by BOUNCE to lose some energy
            this.vel.y *= -BOUNCE; 
            
            // Apply slight ground friction to stop infinite rolling
            this.vel.x *= 0.9;
            
            // Stop micro-bouncing when near rest
            if (Math.abs(this.vel.y) < GRAVITY) {
                this.vel.y = 0;
            }
        }

        // --- COLLISION (The Walls) ---
        if (this.pos.x >= WIDTH - 1) {
            this.pos.x = WIDTH - 1;
            this.vel.x *= -BOUNCE;
        } else if (this.pos.x <= 0) {
            this.pos.x = 0;
            this.vel.x *= -BOUNCE;
        }
    }
}

// --- 3. The Engine ---
class World {
    constructor() {
        this.objects = [];
    }

    addBall(ball) {
        this.objects.push(ball);
    }

    // Run physics calculations for everyone
    tick() {
        this.objects.forEach(obj => obj.update());
    }

    // Draw the scene
    render() {
        // Create empty buffer (2D Array representing screen)
        let buffer = Array(HEIGHT).fill(null).map(() => Array(WIDTH).fill(' '));

        // Place objects into buffer
        this.objects.forEach(obj => {
            const x = Math.floor(obj.pos.x);
            const y = Math.floor(obj.pos.y);
            
            // Safety check to ensure we don't draw outside array bounds
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                buffer[y][x] = obj.id;
            }
        });

        // Convert buffer to string
        // \x1b[2J clears screen, \x1b[0f resets cursor
        let output = '\x1b[2J\x1b[0f'; 
        
        // Draw Top Border
        output += '+' + '-'.repeat(WIDTH) + '+\n';
        
        // Draw World
        buffer.forEach(row => {
            output += '|' + row.join('') + '|\n';
        });

        // Draw Floor
        output += '+' + '-'.repeat(WIDTH) + '+';
        output += `\n Objects: ${this.objects.length} (Press SPACE to drop ball, Ctrl+C to quit)`;

        process.stdout.write(output);
    }
}

// --- 4. Main Execution ---
const world = new World();

// Add an initial ball
const b1 = new Ball('O', 5, 2);
b1.vel.x = 1.5; // Give it a push to the right
world.addBall(b1);

// Handle Keyboard Input
readline.emitKeypressEvents(process.stdin);
if (process.stdin.setRawMode) process.stdin.setRawMode(true);

process.stdin.on('keypress', (str, key) => {
    if (key.ctrl && key.name === 'c') process.exit();
    
    // Spacebar spawns a new ball
    if (key.name === 'space') {
        const randomX = Math.floor(Math.random() * (WIDTH - 10)) + 5;
        const newBall = new Ball('@', randomX, 2);
        
        // Random initial push
        newBall.vel.x = (Math.random() - 0.5) * 4; 
        newBall.vel.y = -1; // Slight pop up
        world.addBall(newBall);
    }
});

// The Game Loop
setInterval(() => {
    world.tick();   // 1. Calculate Math
    world.render(); // 2. Draw Result
}, 1000 / FPS);