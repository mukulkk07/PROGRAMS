/**
 * PROJECT: Project Darwin (Genetic Algorithm Simulation)
 * CONCEPTS: Artificial Intelligence, Heuristics, Probability, Array Manipulation
 */

// --- CONFIGURATION ---
const TARGET_PHRASE = "To be, or not to be, that is the question.";
const POPULATION_SIZE = 600;  // How many "creatures" live in each generation
const MUTATION_RATE = 0.01;   // 1% chance a gene will mutate randomly

// The characters available to form the DNA
const GENES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;!?-";

class DNA {
    constructor(length) {
        // The DNA is an array of characters
        this.genes = new Array(length);
        this.fitness = 0;
    }

    // 1. Create a completely random creature (for Generation 1)
    static random(length) {
        const dna = new DNA(length);
        for (let i = 0; i < length; i++) {
            dna.genes[i] = GENES.charAt(Math.floor(Math.random() * GENES.length));
        }
        return dna;
    }

    // 2. Calculate how good this creature is (0.0 to 1.0)
    // A score of 1.0 means it matches the target perfectly.
    calculateFitness(target) {
        let score = 0;
        for (let i = 0; i < this.genes.length; i++) {
            if (this.genes[i] === target[i]) {
                score++;
            }
        }
        // Squaring the score amplifies the difference between "okay" and "great"
        // This makes the best candidates stand out much more to the selection algorithm.
        this.fitness = Math.pow(score / target.length, 2); 
    }

    // 3. CROSSOVER (Mating)
    // Combine this DNA with a partner's DNA to create a child
    crossover(partner) {
        const child = new DNA(this.genes.length);
        
        // Pick a random midpoint to split the genes
        const midpoint = Math.floor(Math.random() * this.genes.length);

        for (let i = 0; i < this.genes.length; i++) {
            if (i > midpoint) {
                child.genes[i] = this.genes[i]; // Take from Dad
            } else {
                child.genes[i] = partner.genes[i]; // Take from Mom
            }
        }
        return child;
    }

    // 4. MUTATION
    // Rarely, a gene changes randomly. This prevents the species from getting stuck.
    mutate() {
        for (let i = 0; i < this.genes.length; i++) {
            if (Math.random() < MUTATION_RATE) {
                this.genes[i] = GENES.charAt(Math.floor(Math.random() * GENES.length));
            }
        }
    }

    // Convert genes array back to string
    getPhrase() {
        return this.genes.join("");
    }
}

class Population {
    constructor(target, size) {
        this.target = target;
        this.population = [];
        this.generation = 1;
        this.bestPhrase = "";
        this.finished = false;

        // Fill population with random DNA
        for (let i = 0; i < size; i++) {
            this.population.push(DNA.random(target.length));
        }
    }

    // Evaluate everyone
    evaluate() {
        let worldRecord = 0.0;
        let index = 0;

        for (let i = 0; i < this.population.length; i++) {
            this.population[i].calculateFitness(this.target);
            
            if (this.population[i].fitness > worldRecord) {
                worldRecord = this.population[i].fitness;
                index = i;
            }
        }

        this.bestPhrase = this.population[index].getPhrase();
        
        // Perfect score (1.0 fitness before squaring logic adjustment check)
        // If the best phrase matches target exactly
        if (this.bestPhrase === this.target) {
            this.finished = true;
        }
    }

    // Create the next generation
    naturalSelection() {
        // Create a "Mating Pool" based on fitness
        // Higher fitness = More entries in the pool = Higher chance to be picked
        const matingPool = [];

        // Determine max fitness in this round to normalize
        let maxFitness = 0;
        for (let i = 0; i < this.population.length; i++) {
            if (this.population[i].fitness > maxFitness) {
                maxFitness = this.population[i].fitness;
            }
        }

        // Build pool
        for (let i = 0; i < this.population.length; i++) {
            const partner = this.population[i];
            // Normalize fitness to 0-1 range relative to max
            // and add to pool multiple times (Probabilistic Selection)
            const n = Math.floor((partner.fitness / maxFitness) * 100); 
            for (let j = 0; j < n; j++) {
                matingPool.push(partner);
            }
        }

        // Reproduction
        const nextGen = [];
        for (let i = 0; i < this.population.length; i++) {
            // Pick two random parents from the weighted pool
            const parentA = matingPool[Math.floor(Math.random() * matingPool.length)];
            const parentB = matingPool[Math.floor(Math.random() * matingPool.length)];

            // Create child
            const child = parentA.crossover(parentB);
            
            // Apply Mutation
            child.mutate();

            nextGen.push(child);
        }

        this.population = nextGen;
        this.generation++;
    }
}

// --- MAIN EXECUTION ---
const darwin = new Population(TARGET_PHRASE, POPULATION_SIZE);
const startTime = Date.now();

console.log("\n--- PROJECT DARWIN: EVOLUTION ENGINE STARTED ---");
console.log(`Target: "${TARGET_PHRASE}"`);
console.log(`Population: ${POPULATION_SIZE} | Mutation Rate: ${MUTATION_RATE * 100}%`);
console.log("------------------------------------------------\n");

// Use setInterval to create an animation loop
const timer = setInterval(() => {
    darwin.evaluate();
    
    // Visualization
    process.stdout.write(`\rGen: ${darwin.generation} | Best: ${darwin.bestPhrase}`);

    if (darwin.finished) {
        clearInterval(timer);
        const duration = ((Date.now() - startTime) / 1000).toFixed(2);
        console.log(`\n\n✅ EVOLUTION COMPLETE in ${duration} seconds!`);
        console.log(`The computer learned to write using biology.`);
    } else {
        darwin.naturalSelection();
    }
}, 20); // Run every 20 milliseconds