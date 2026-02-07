/**
 * PROJECT: TinySearch (Search Engine & PageRank)
 * CONCEPTS: Inverted Index, Graph Theory, Matrix Convergence, Tokenization
 */

const readline = require('readline');

// --- 1. THE FAKE INTERNET ---
// A graph of pages. 'links' points to other page IDs (like <a href="...">)
const internet = [
    { id: 0, title: "Node.js Home", content: "Node.js is a runtime for JavaScript.", links: [1, 2] },
    { id: 1, title: "NPM Registry", content: "NPM is the package manager for Node.js.", links: [0] },
    { id: 2, title: "Google",       content: "Search the world's information.", links: [0, 3] },
    { id: 3, title: "Wikipedia",    content: "The free encyclopedia about everything.", links: [2, 4] },
    { id: 4, title: "Spam Site",    content: "Buy cheap watches! Free money!", links: [4] }, // Self-linking trap
    { id: 5, title: "JS Dev Blog",  content: "I love Node.js and JavaScript.", links: [0, 1] }
];

// --- 2. THE INDEXER (The Librarian) ---
class SearchIndex {
    constructor() {
        // The Inverted Index: Maps "Word" -> [List of Page IDs]
        // Example: "node" -> [0, 1, 5]
        this.index = {};
    }

    // Tokenization: Splits text into clean words
    tokenize(text) {
        return text.toLowerCase()
            .replace(/[.,!?;:]/g, '') // Remove punctuation
            .split(/\s+/)             // Split by spaces
            .filter(w => w.length > 2); // Ignore short words like "is", "a"
    }

    build(pages) {
        console.log("Building Inverted Index...");
        
        pages.forEach(page => {
            const words = this.tokenize(page.title + " " + page.content);
            
            // Add every word to the index
            words.forEach(word => {
                if (!this.index[word]) {
                    this.index[word] = new Set();
                }
                this.index[word].add(page.id);
            });
        });
        
        console.log(`Indexed ${Object.keys(this.index).length} unique keywords.\n`);
    }

    search(query) {
        const words = this.tokenize(query);
        if (words.length === 0) return [];

        // Find pages that contain ANY of the search terms
        let results = new Set();
        words.forEach(word => {
            if (this.index[word]) {
                this.index[word].forEach(id => results.add(id));
            }
        });

        return Array.from(results);
    }
}

// --- 3. THE RANKER (The Algorithm) ---
// This is the simplified "PageRank" logic (Larry Page, 1996).
// A page is important if other important pages link to it.
class PageRank {
    constructor(pages) {
        this.pages = pages;
        this.ranks = {};
        this.damping = 0.85; // Probability user continues clicking (vs closing tab)
        this.iterations = 20; // How many times to refine the math
    }

    calculate() {
        console.log("Calculating PageRank Authority...");
        const N = this.pages.length;
        
        // Step 1: Initialize everyone with equal rank (1 / N)
        this.pages.forEach(p => this.ranks[p.id] = 1 / N);

        // Step 2: Iterate to converge on the true values
        for (let i = 0; i < this.iterations; i++) {
            const newRanks = {};

            this.pages.forEach(page => {
                let incomingRank = 0;

                // Find all pages that link TO this page
                const backlinks = this.pages.filter(p => p.links.includes(page.id));

                backlinks.forEach(linker => {
                    const numOutgoing = linker.links.length;
                    // The linker shares its rank equally among all people it links to
                    incomingRank += this.ranks[linker.id] / numOutgoing;
                });

                // The PageRank Formula
                newRanks[page.id] = (1 - this.damping) / N + (this.damping * incomingRank);
            });

            this.ranks = newRanks;
        }
        
        // Normalization (Make readable score out of 10)
        const maxScore = Math.max(...Object.values(this.ranks));
        this.pages.forEach(p => {
            this.ranks[p.id] = (this.ranks[p.id] / maxScore) * 10;
        });
    }

    getRank(id) {
        return this.ranks[id] || 0;
    }
}

// --- 4. THE SEARCH ENGINE CORE ---
class TinySearch {
    constructor(data) {
        this.data = data;
        this.indexer = new SearchIndex();
        this.ranker = new PageRank(data);
        
        // Boot up
        this.indexer.build(data);
        this.ranker.calculate();
    }

    runQuery(query) {
        console.log(`\n🔎 Searching for: "${query}"`);
        const hitIds = this.indexer.search(query);

        if (hitIds.length === 0) {
            console.log("No results found.");
            return;
        }

        // Map IDs to actual Page Objects and add their Rank
        const results = hitIds.map(id => {
            const page = this.data.find(p => p.id === id);
            return {
                ...page,
                score: this.ranker.getRank(id)
            };
        });

        // SORT by PageRank Score (Highest first)
        results.sort((a, b) => b.score - a.score);

        // Display
        console.log(`Found ${results.length} results:\n`);
        results.forEach((r, i) => {
            const stars = "★".repeat(Math.round(r.score));
            console.log(`[${i+1}] ${r.title} (Authority: ${r.score.toFixed(1)}/10) ${stars}`);
            console.log(`    "${r.content}"`);
            console.log(`    Links to: [${r.links.join(', ')}]\n`);
        });
    }
}

// --- 5. INTERFACE ---
const engine = new TinySearch(internet);

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

console.log("--- TinySearch Engine v1.0 ---");
console.log("Try searching for: 'node', 'google', 'javascript', 'free'");

function prompt() {
    rl.question('Search > ', (query) => {
        if (query.trim() === 'exit') return rl.close();
        
        engine.runQuery(query);
        prompt();
    });
}

prompt();