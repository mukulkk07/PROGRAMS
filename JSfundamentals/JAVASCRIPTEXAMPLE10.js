/**
 * PROJECT: MindForge (Deep Learning Neural Network)
 * CONCEPTS: Matrix Math, Gradient Descent, Backpropagation, Activation Functions
 */

// --- 1. The Math Core (Linear Algebra Helper) ---
// AI is essentially just multiplying big arrays of numbers together.
class Matrix {
    constructor(rows, cols) {
        this.rows = rows;
        this.cols = cols;
        this.data = Array(this.rows).fill().map(() => Array(this.cols).fill(0));
    }

    // Initialize with random numbers between -1 and 1
    randomize() {
        this.data = this.data.map(row => row.map(() => Math.random() * 2 - 1));
    }

    // Convert an Array to a Matrix (1 column)
    static fromArray(arr) {
        const m = new Matrix(arr.length, 1);
        m.data = arr.map(el => [el]);
        return m;
    }

    // Convert Matrix back to Array
    toArray() {
        let arr = [];
        this.data.forEach(row => row.forEach(val => arr.push(val)));
        return arr;
    }

    // Matrix Multiplication (Dot Product)
    static multiply(a, b) {
        if (a.cols !== b.rows) {
            console.error("Columns of A must match rows of B.");
            return undefined;
        }
        let result = new Matrix(a.rows, b.cols);
        for (let i = 0; i < result.rows; i++) {
            for (let j = 0; j < result.cols; j++) {
                let sum = 0;
                for (let k = 0; k < a.cols; k++) {
                    sum += a.data[i][k] * b.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    // Element-wise addition
    add(n) {
        if (n instanceof Matrix) {
            this.data = this.data.map((row, i) => row.map((val, j) => val + n.data[i][j]));
        } else {
            this.data = this.data.map(row => row.map(val => val + n));
        }
    }

    // Apply a function to every element (e.g., Sigmoid)
    map(func) {
        this.data = this.data.map((row, i) => row.map((val, j) => func(val, i, j)));
    }

    static map(matrix, func) {
        let result = new Matrix(matrix.rows, matrix.cols);
        result.data = matrix.data.map((row, i) => row.map((val, j) => func(val, i, j)));
        return result;
    }

    static subtract(a, b) {
        let result = new Matrix(a.rows, a.cols);
        result.data = a.data.map((row, i) => row.map((val, j) => val - b.data[i][j]));
        return result;
    }
    
    // Element-wise multiplication (Hadamard product)
    multiply(n) {
        if (n instanceof Matrix) {
            this.data = this.data.map((row, i) => row.map((val, j) => val * n.data[i][j]));
        } else {
            this.data = this.data.map(row => row.map(val => val * n));
        }
    }
}

// --- 2. The Neural Network Class ---
class NeuralNetwork {
    constructor(input_nodes, hidden_nodes, output_nodes) {
        this.input_nodes = input_nodes;
        this.hidden_nodes = hidden_nodes;
        this.output_nodes = output_nodes;

        // Weights: The connection strength between neurons
        // weights_ih = Input -> Hidden
        // weights_ho = Hidden -> Output
        this.weights_ih = new Matrix(this.hidden_nodes, this.input_nodes);
        this.weights_ho = new Matrix(this.output_nodes, this.hidden_nodes);
        
        this.weights_ih.randomize();
        this.weights_ho.randomize();

        // Biases: The threshold for a neuron to fire
        this.bias_h = new Matrix(this.hidden_nodes, 1);
        this.bias_o = new Matrix(this.output_nodes, 1);
        this.bias_h.randomize();
        this.bias_o.randomize();

        this.learning_rate = 0.1;
    }

    // The Activation Function (Squishes numbers between 0 and 1)
    sigmoid(x) {
        return 1 / (1 + Math.exp(-x));
    }

    // The Derivative (Used for calculating gradient during learning)
    dsigmoid(y) {
        // We assume y has already passed through sigmoid
        return y * (1 - y);
    }

    // FEED FORWARD: Guess the answer
    predict(input_array) {
        // 1. Input -> Hidden Layer
        let inputs = Matrix.fromArray(input_array);
        let hidden = Matrix.multiply(this.weights_ih, inputs);
        hidden.add(this.bias_h);
        hidden.map(this.sigmoid); // Apply Activation

        // 2. Hidden -> Output Layer
        let output = Matrix.multiply(this.weights_ho, hidden);
        output.add(this.bias_o);
        output.map(this.sigmoid); // Apply Activation

        return output.toArray();
    }

    // BACKPROPAGATION: Learn from mistakes
    train(input_array, target_array) {
        // --- A. Feed Forward (Same as predict) ---
        let inputs = Matrix.fromArray(input_array);
        let hidden = Matrix.multiply(this.weights_ih, inputs);
        hidden.add(this.bias_h);
        hidden.map(this.sigmoid);

        let outputs = Matrix.multiply(this.weights_ho, hidden);
        outputs.add(this.bias_o);
        outputs.map(this.sigmoid);

        // --- B. Calculate Errors ---
        // ERROR = TARGET - OUTPUT
        let targets = Matrix.fromArray(target_array);
        let output_errors = Matrix.subtract(targets, outputs);

        // --- C. Calculate Gradients (Output Layer) ---
        // gradient = learning_rate * error * dsigmoid(output)
        let gradients = Matrix.map(outputs, this.dsigmoid);
        gradients.multiply(output_errors);
        gradients.multiply(this.learning_rate);

        // --- D. Adjust Weights (Hidden -> Output) ---
        // deltaWeight = gradient * hidden_transposed
        let hidden_T = new Matrix(hidden.cols, hidden.rows); // Transpose
        hidden_T.data = hidden.data[0].map((_, colIndex) => hidden.data.map(row => row[colIndex])); // manual transpose
        
        let weight_ho_deltas = Matrix.multiply(gradients, hidden_T);
        this.weights_ho.add(weight_ho_deltas); // Tweak the weights
        this.bias_o.add(gradients);            // Tweak the bias

        // --- E. Calculate Hidden Errors ---
        // We calculate how much the Hidden layer was responsible for the output error
        // hidden_error = weights_ho_transposed * output_errors
        let who_T = new Matrix(this.weights_ho.cols, this.weights_ho.rows); // Transpose
        who_T.data = this.weights_ho.data[0].map((_, colIndex) => this.weights_ho.data.map(row => row[colIndex]));

        let hidden_errors = Matrix.multiply(who_T, output_errors);

        // --- F. Calculate Hidden Gradients ---
        let hidden_gradient = Matrix.map(hidden, this.dsigmoid);
        hidden_gradient.multiply(hidden_errors);
        hidden_gradient.multiply(this.learning_rate);

        // --- G. Adjust Weights (Input -> Hidden) ---
        let inputs_T = new Matrix(inputs.cols, inputs.rows); // Transpose
        inputs_T.data = inputs.data[0].map((_, colIndex) => inputs.data.map(row => row[colIndex]));

        let weight_ih_deltas = Matrix.multiply(hidden_gradient, inputs_T);
        this.weights_ih.add(weight_ih_deltas);
        this.bias_h.add(hidden_gradient);
    }
}

// --- 3. The Experiment: Teaching XOR ---
// XOR is the "Hello World" of Deep Learning.
// Input 0,0 -> 0
// Input 0,1 -> 1
// Input 1,0 -> 1
// Input 1,1 -> 0

const training_data = [
    { inputs: [0, 0], targets: [0] },
    { inputs: [0, 1], targets: [1] },
    { inputs: [1, 0], targets: [1] },
    { inputs: [1, 1], targets: [0] }
];

// Initialize Brain: 2 Inputs, 2 Hidden Neurons, 1 Output
const brain = new NeuralNetwork(2, 2, 1);

console.log("\n--- MINDFORGE AI: INITIALIZED ---");
console.log("Status: Untrained. Predictions will be random guesses.");
console.log(`[0,0] guess: ${brain.predict([0,0])}`);
console.log(`[1,0] guess: ${brain.predict([1,0])}`);

console.log("\n--- TRAINING SEQUENCE STARTED ---");
const EPOCHS = 20000; // How many times we show the data to the brain

const start = Date.now();
for (let i = 0; i < EPOCHS; i++) {
    // Pick a random data piece
    const data = training_data[Math.floor(Math.random() * training_data.length)];
    brain.train(data.inputs, data.targets);

    // Progress bar
    if (i % (EPOCHS / 10) === 0) {
        process.stdout.write(`Training... ${Math.floor((i/EPOCHS)*100)}%\r`);
    }
}
const duration = (Date.now() - start) / 1000;

console.log(`\n✅ Training Complete in ${duration}s (${EPOCHS} iterations)`);

console.log("\n--- FINAL EXAM RESULTS ---");
// Pretty print the results
training_data.forEach(data => {
    const guess = brain.predict(data.inputs)[0];
    const correct = guess > 0.5 ? 1 : 0; // Round to nearest integer
    const formattedGuess = guess.toFixed(4);
    
    // Color coding output
    const check = correct === data.targets[0] ? "✅ PASS" : "❌ FAIL";
    
    console.log(`Input: [${data.inputs}] | Target: ${data.targets} | AI Guess: ${formattedGuess} | ${check}`);
});