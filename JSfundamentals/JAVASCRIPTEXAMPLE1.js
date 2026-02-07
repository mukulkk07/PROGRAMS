/**
 * PROJECT: Node.js Algorithmic Trading Bot Simulation
 * CONCEPTS: Event Emitters, Mathematical Simulation, State Management, ASCII Visualization
 */

const EventEmitter = require('events'); // Core module for handling signals
const fs = require('fs');
const path = require('path');

// Configuration
const CONFIG = {
    symbol: 'GEMINI',
    startPrice: 100.00,
    volatility: 0.05, // How wild the price swings are
    speed: 1000,      // Market tick speed in ms
    startBalance: 10000 // Starting fake money
};

const LOG_FILE = path.join(__dirname, 'trade_history.json');

// --- 1. The Market (The Engine) ---
// Extends EventEmitter so it can "broadcast" price updates
class Market extends EventEmitter {
    constructor(symbol, startPrice) {
        super();
        this.symbol = symbol;
        this.price = startPrice;
        this.history = []; // Keep track of past prices for the chart
        this.running = false;
    }

    start() {
        this.running = true;
        console.log(`\n--- Market Open: ${this.symbol} started at $${this.price.toFixed(2)} ---`);
        
        setInterval(() => {
            if (!this.running) return;

            // Math Magic: Random Walk Theory to simulate stock movement
            const changePercent = (Math.random() - 0.5) * CONFIG.volatility;
            const changeAmount = this.price * changePercent;
            this.price += changeAmount;

            // Ensure price never goes below $1
            if (this.price < 1) this.price = 1;

            this.history.push(this.price);
            if (this.history.length > 20) this.history.shift(); // Keep only last 20 ticks

            // BROADCAST THE EVENT: "New Price Available!"
            this.emit('tick', this.price); 
        }, CONFIG.speed);
    }
}

// --- 2. The Portfolio (The Wallet) ---
class Portfolio {
    constructor(balance) {
        this.cash = balance;
        this.holdings = 0;
        this.trades = [];
    }

    // Calculate total net worth (Cash + Value of Stocks)
    getValue(currentPrice) {
        return this.cash + (this.holdings * currentPrice);
    }

    buy(price) {
        if (this.cash >= price) {
            this.cash -= price;
            this.holdings += 1;
            this.logTrade("BUY", price);
            return true;
        }
        return false;
    }

    sell(price) {
        if (this.holdings > 0) {
            this.cash += price;
            this.holdings -= 1;
            this.logTrade("SELL", price);
            return true;
        }
        return false;
    }

    logTrade(type, price) {
        const trade = {
            type,
            price: parseFloat(price.toFixed(2)),
            time: new Date().toLocaleTimeString()
        };
        this.trades.push(trade);
        
        // Asynchronously save to disk
        fs.writeFile(LOG_FILE, JSON.stringify(this.trades, null, 2), () => {});
    }
}

// --- 3. The Trader Bot (The Brain) ---
class TradingBot {
    constructor(market, portfolio) {
        this.market = market;
        this.portfolio = portfolio;
        this.prices = []; // Internal memory for analysis
    }

    analyze(currentPrice) {
        this.prices.push(currentPrice);
        if (this.prices.length > 5) this.prices.shift(); // track last 5 prices

        // Calculate Simple Moving Average (SMA)
        const sum = this.prices.reduce((a, b) => a + b, 0);
        const average = sum / this.prices.length;

        // STRATEGY:
        // If price is 2% lower than average -> Buy the dip
        // If price is 2% higher than average -> Sell the spike
        const diff = ((currentPrice - average) / average) * 100;

        // Visual Indicator of Market Sentiment
        const trend = currentPrice > average ? "📈 BULLISH" : "📉 BEARISH";
        this.renderDashboard(currentPrice, average, trend);

        if (diff < -2) {
            if (this.portfolio.buy(currentPrice)) {
                console.log(`\n💰 [BOT ACTION] BOUGHT at $${currentPrice.toFixed(2)} (Buying the dip!)`);
            }
        } else if (diff > 2) {
            if (this.portfolio.sell(currentPrice)) {
                console.log(`\n💸 [BOT ACTION] SOLD at $${currentPrice.toFixed(2)} (Taking profit!)`);
            }
        }
    }

    renderDashboard(price, avg, trend) {
        // Clear console for a "Static UI" effect (works best in full terminal)
        // console.clear(); // Uncomment this line if you want the screen to wipe every second

        const netWorth = this.portfolio.getValue(price).toFixed(2);
        const profit = (netWorth - CONFIG.startBalance).toFixed(2);
        const color = profit >= 0 ? "+" : "";

        console.log(`
        -------------------------------------------
        SYMBOL: ${CONFIG.symbol}  | PRICE: $${price.toFixed(2)}
        TREND:  ${trend}  | SMA(5): $${avg.toFixed(2)}
        -------------------------------------------
        WALLET: $${this.portfolio.cash.toFixed(2)} | STOCKS HELD: ${this.portfolio.holdings}
        NET WORTH: $${netWorth} (${color}${profit})
        -------------------------------------------
        `);
    }
}

// --- 4. Initialization ---
const market = new Market(CONFIG.symbol, CONFIG.startPrice);
const myWallet = new Portfolio(CONFIG.startBalance);
const bot = new TradingBot(market, myWallet);

console.log("Initializing Auto-Trader System...");
console.log("Simulating volatile market conditions...");

// Start the engine
market.start();

// CONNECT THE WIRES:
// When market emits 'tick', trigger the bot's 'analyze' function
market.on('tick', (price) => {
    bot.analyze(price);
});