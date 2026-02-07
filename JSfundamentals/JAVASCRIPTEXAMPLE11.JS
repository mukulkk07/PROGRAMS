/**
 * PROJECT: Terminal Doom (Ray Casting Engine)
 * CONCEPTS: Trigonometry, Field of View (FOV), Perspective Projection, Rendering Optimization
 */

const readline = require('readline');

// --- CONFIGURATION ---
const SCREEN_WIDTH = 120; // Number of columns in terminal
const SCREEN_HEIGHT = 30; // Number of rows
const MAP_SIZE = 16;      // Size of the world (16x16 blocks)
const FOV = Math.PI / 3;  // Field of View (60 degrees)
const DEPTH = 16.0;       // Max rendering distance

// --- THE MAP ---
// # = Wall, . = Empty Space
// We use a single string to represent the 2D grid
let map = "";
map += "################";
map += "#..............#";
map += "#.......########";
map += "#..............#";
map += "#......##......#";
map += "#......##......#";
map += "#..............#";
map += "###............#";
map += "##.............#";
map += "#......####....#";
map += "#......#.......#";
map += "#......#.......#";
map += "#..............#";
map += "#......#########";
map += "#..............#";
map += "################";

// --- PLAYER STATE ---
let playerX = 8.0;
let playerY = 8.0;
let playerA = 0.0; // Angle (Rotation)

// --- RENDER ENGINE ---
function renderFrame() {
    // Buffer to hold the frame before printing (optimization)
    const screen = [];

    // RAY CASTING LOOP
    // We scan from left to right across the screen
    for (let x = 0; x < SCREEN_WIDTH; x++) {
        
        // 1. Calculate Ray Angle
        // For each column 'x', we calculate the angle relative to the player
        const rayAngle = (playerA - FOV / 2.0) + (x / SCREEN_WIDTH) * FOV;

        const eyeX = Math.sin(rayAngle); // Unit vector for ray
        const eyeY = Math.cos(rayAngle);

        // 2. March the Ray forward until it hits a wall
        let distanceToWall = 0;
        let hitWall = false;
        let boundary = false; // For edge highlighting

        while (!hitWall && distanceToWall < DEPTH) {
            distanceToWall += 0.1; // Step size (Resolution)

            // Current test coordinate
            const testX = Math.floor(playerX + eyeX * distanceToWall);
            const testY = Math.floor(playerY + eyeY * distanceToWall);

            // Check if ray is out of bounds
            if (testX < 0 || testX >= MAP_SIZE || testY < 0 || testY >= MAP_SIZE) {
                hitWall = true;
                distanceToWall = DEPTH;
            } else {
                // Check map index
                if (map[testY * MAP_SIZE + testX] === '#') {
                    hitWall = true;
                    
                    // --- OPTIONAL: Edge Detection (Corner highlighting) ---
                    // This math checks if the ray hit the corner of a block perfectly
                    // It creates a nice visual outline for walls.
                    const p = [];
                    for (let tx = 0; tx < 2; tx++) {
                        for (let ty = 0; ty < 2; ty++) {
                            const vy = testY + ty - (playerY + eyeY * distanceToWall);
                            const vx = testX + tx - (playerX + eyeX * distanceToWall);
                            const d = Math.sqrt(vx*vx + vy*vy);
                            const dot = (eyeX * vx / d) + (eyeY * vy / d);
                            p.push({d: d, dot: dot});
                        }
                    }
                    // Sort by closeness
                    p.sort((a,b) => a.d - b.d);
                    
                    // If the angle is very narrow, we hit an edge
                    const bound = 0.01;
                    if (Math.acos(p[0].dot) < bound) boundary = true;
                }
            }
        }

        // 3. Calculate Ceiling and Floor
        // The further the wall, the smaller it appears on screen (Perspective)
        const ceiling = Math.floor((SCREEN_HEIGHT / 2.0) - (SCREEN_HEIGHT / distanceToWall));
        const floor = SCREEN_HEIGHT - ceiling;

        // 4. Shade the Wall based on distance
        let shade = ' ';
        if (distanceToWall <= DEPTH / 4.0)     shade = '\u2588'; // Full block (█)
        else if (distanceToWall < DEPTH / 3.0) shade = '\u2593'; // Dark shade (▓)
        else if (distanceToWall < DEPTH / 2.0) shade = '\u2592'; // Medium shade (▒)
        else if (distanceToWall < DEPTH)       shade = '\u2591'; // Light shade (░)
        else                                   shade = '.';      // Too far

        if (boundary) shade = '|'; // Draw edge

        // 5. Draw the vertical column
        for (let y = 0; y < SCREEN_HEIGHT; y++) {
            // We treat the screen array as a 1D stream
            const index = y * SCREEN_WIDTH + x;

            if (y < ceiling) {
                // Sky
                screen[index] = ' '; 
            } else if (y > ceiling && y <= floor) {
                // Wall
                screen[index] = shade;
            } else {
                // Floor (Shade based on distance for pseudo-depth)
                const b = 1.0 - ((y - SCREEN_HEIGHT / 2.0) / (SCREEN_HEIGHT / 2.0));
                if (b < 0.25)      screen[index] = '#';
                else if (b < 0.5)  screen[index] = 'x';
                else if (b < 0.75) screen[index] = '.';
                else               screen[index] = ' ';
            }
        }
    }

    // PRINT FRAME
    // \x1b[H resets cursor to top-left (much faster than clear screen)
    process.stdout.write('\x1b[H' + screen.join('').match(new RegExp('.{1,' + SCREEN_WIDTH + '}', 'g')).join('\n'));
    
    // Draw Stats
    console.log(`\nPOS: X:${playerX.toFixed(2)} Y:${playerY.toFixed(2)} A:${playerA.toFixed(2)}`);
    console.log(`CONTROLS: 'A' Left, 'D' Right, 'W' Forward, 'S' Back. (Ctrl+C to Quit)`);
}

// --- INPUT HANDLING ---
readline.emitKeypressEvents(process.stdin);
if (process.stdin.setRawMode) process.stdin.setRawMode(true);

process.stdin.on('keypress', (str, key) => {
    if (key.ctrl && key.name === 'c') process.exit();

    // Movement Logic
    // Notice we use Math.sin/cos again to move in the direction we are facing
    if (key.name === 'a') {
        playerA -= 0.1;
    } 
    else if (key.name === 'd') {
        playerA += 0.1;
    } 
    else if (key.name === 'w') {
        playerX += Math.sin(playerA) * 0.5;
        playerY += Math.cos(playerA) * 0.5;
        
        // Simple collision (if walked into wall, undo movement)
        if (map[Math.floor(playerY) * MAP_SIZE + Math.floor(playerX)] === '#') {
            playerX -= Math.sin(playerA) * 0.5;
            playerY -= Math.cos(playerA) * 0.5;
        }
    } 
    else if (key.name === 's') {
        playerX -= Math.sin(playerA) * 0.5;
        playerY -= Math.cos(playerA) * 0.5;
        
        if (map[Math.floor(playerY) * MAP_SIZE + Math.floor(playerX)] === '#') {
            playerX += Math.sin(playerA) * 0.5;
            playerY += Math.cos(playerA) * 0.5;
        }
    }
});

// --- GAME LOOP ---
console.clear();
setInterval(renderFrame, 33); // ~30 FPS