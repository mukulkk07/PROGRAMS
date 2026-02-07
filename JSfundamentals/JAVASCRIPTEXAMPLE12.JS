/**
 * PROJECT: Pathfinder (A* Algorithm & Maze Generation)
 * CONCEPTS: Graph Theory, Heuristics, Recursion, Stack Data Structures
 */

// --- CONFIGURATION ---
const ROWS = 21; // Must be odd numbers for the maze gen to work nicely
const COLS = 51;
const SPEED = 20; // Lower is faster

// Symbols for rendering
const WALL = '█';
const PATH = ' ';
const START = 'S';
const END = 'E';
const VISITED = '.'; // Nodes the algorithm has checked
const FINAL_PATH = 'O'; // The best route found

// --- 1. The Maze Generator (Recursive Backtracker) ---
class Maze {
    constructor(rows, cols) {
        this.rows = rows;
        this.cols = cols;
        // Create a grid full of walls
        this.grid = Array(rows).fill().map(() => Array(cols).fill(WALL));
    }

    generate() {
        // Start carving from top-left (1,1)
        this.carve(1, 1);
        
        // Set Start and End points
        this.grid[1][1] = START;
        this.grid[this.rows - 2][this.cols - 2] = END;
        
        return { 
            start: { r: 1, c: 1 }, 
            end: { r: this.rows - 2, c: this.cols - 2 } 
        };
    }

    carve(r, c) {
        this.grid[r][c] = PATH;

        // Randomly shuffle directions: Up, Down, Left, Right
        const directions = [
            { dr: -2, dc: 0 }, { dr: 2, dc: 0 }, // Vertical (jump 2 to skip walls)
            { dr: 0, dc: -2 }, { dr: 0, dc: 2 }  // Horizontal
        ].sort(() => Math.random() - 0.5);

        for (let { dr, dc } of directions) {
            const nr = r + dr;
            const nc = c + dc;

            // Check bounds and if the neighbor is currently a Wall
            if (nr > 0 && nr < this.rows - 1 && nc > 0 && nc < this.cols - 1 && this.grid[nr][nc] === WALL) {
                // Knock down the wall between current and neighbor
                this.grid[r + dr / 2][c + dc / 2] = PATH;
                // Recursively carve from the neighbor
                this.carve(nr, nc);
            }
        }
    }
}

// --- 2. The Solver (A* Algorithm) ---
class Solver {
    constructor(mazeObj, start, end) {
        this.grid = mazeObj.grid;
        this.start = start;
        this.end = end;
        
        // Open Set: Nodes we need to check
        // Closed Set: Nodes we have already checked
        this.openSet = [];
        this.closedSet = new Set();
        
        // 'cameFrom': Tracks the path (Breadcrumbs)
        this.cameFrom = new Map();

        // G-Score: Cost from Start to Current
        this.gScore = new Map();
        
        // F-Score: Estimated Total Cost (G + H)
        this.fScore = new Map();

        // Initialize Start Node
        const startKey = this.key(start);
        this.openSet.push(start);
        this.gScore.set(startKey, 0);
        this.fScore.set(startKey, this.heuristic(start, end));
    }

    // Heuristic: Manhattan Distance (Taxicab geometry)
    // Helps the algo guess which direction is "closer" to the exit
    heuristic(a, b) {
        return Math.abs(a.r - b.r) + Math.abs(a.c - b.c);
    }

    // Convert coord object to string key "row,col"
    key(node) {
        return `${node.r},${node.c}`;
    }

    // Reconstruct the best path backwards
    reconstructPath() {
        let current = this.end;
        while (this.cameFrom.has(this.key(current))) {
            const k = this.key(current);
            const [r, c] = k.split(',').map(Number);
            
            if (this.grid[r][c] !== END && this.grid[r][c] !== START) {
                this.grid[r][c] = FINAL_PATH; // Mark the winning path
            }
            current = this.cameFrom.get(k);
        }
    }

    // One step of the algorithm (for animation)
    step() {
        if (this.openSet.length === 0) return 'fail';

        // 1. Get node with lowest F-Score (Best guess)
        // (Simple sort for priority queue behavior)
        this.openSet.sort((a, b) => {
            const fA = this.fScore.get(this.key(a)) || Infinity;
            const fB = this.fScore.get(this.key(b)) || Infinity;
            return fA - fB;
        });

        const current = this.openSet.shift(); // Pop the best node
        const currentKey = this.key(current);

        // 2. Check if we reached the end
        if (current.r === this.end.r && current.c === this.end.c) {
            this.reconstructPath();
            return 'success';
        }

        this.closedSet.add(currentKey);

        // Visual: Mark visited nodes (unless it's start/end)
        if (this.grid[current.r][current.c] === PATH) {
            this.grid[current.r][current.c] = VISITED;
        }

        // 3. Check Neighbors
        const neighbors = [
            { r: current.r - 1, c: current.c },
            { r: current.r + 1, c: current.c },
            { r: current.r, c: current.c - 1 },
            { r: current.r, c: current.c + 1 }
        ];

        for (let neighbor of neighbors) {
            // Skip walls and already checked nodes
            if (this.grid[neighbor.r][neighbor.c] === WALL) continue;
            if (this.closedSet.has(this.key(neighbor))) continue;

            // Calculate provisional G-Score (Current G + 1 step)
            const tentativeG = (this.gScore.get(currentKey) || Infinity) + 1;

            const neighborKey = this.key(neighbor);
            if (tentativeG < (this.gScore.get(neighborKey) || Infinity)) {
                // We found a better path to this neighbor!
                this.cameFrom.set(neighborKey, current);
                this.gScore.set(neighborKey, tentativeG);
                this.fScore.set(neighborKey, tentativeG + this.heuristic(neighbor, this.end));

                // Add to Open Set if not there
                if (!this.openSet.some(n => n.r === neighbor.r && n.c === neighbor.c)) {
                    this.openSet.push(neighbor);
                }
            }
        }
        return 'searching';
    }
}

// --- 3. Rendering & Execution ---
const maze = new Maze(ROWS, COLS);
const points = maze.generate();
const solver = new Solver(maze, points.start, points.end);

function draw() {
    // Optimization: Join strings to print 1 giant frame
    const output = maze.grid.map(row => row.join('')).join('\n');
    process.stdout.write('\x1b[H' + output); // Move cursor home + print
}

console.clear();
console.log("Generating Maze...");
draw();

console.log("\nSolving...");

const timer = setInterval(() => {
    const status = solver.step();
    draw();

    if (status === 'success') {
        clearInterval(timer);
        console.log("\n\n✅ PATH FOUND! Follow the 'O's.");
    } else if (status === 'fail') {
        clearInterval(timer);
        console.log("\n\n❌ NO PATH POSSIBLE.");
    }
}, SPEED);