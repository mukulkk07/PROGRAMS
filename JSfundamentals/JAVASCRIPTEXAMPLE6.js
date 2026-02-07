/**
 * PROJECT: PocketSQL (A Light-weight SQL Database Engine)
 * CONCEPTS: Parsing, Indexing, Hash Maps, File Persistence, REPL Interface
 */

const fs = require('fs');
const path = require('path');
const readline = require('readline');

const DB_FILE = path.join(__dirname, 'mydb.json');

// --- 1. The Storage Engine ---
class Table {
    constructor(name) {
        this.name = name;
        this.rows = {}; // The Primary Key Index (Hash Map)
        this.autoIncrement = 1;
    }
}

class Database {
    constructor() {
        this.tables = {};
        this.load();
    }

    // Load from disk
    load() {
        try {
            if (fs.existsSync(DB_FILE)) {
                const data = fs.readFileSync(DB_FILE, 'utf-8');
                const rawData = JSON.parse(data);
                // Rehydrate the plain objects into our structure
                this.tables = rawData;
                console.log("disk_io: Database loaded from file.");
            }
        } catch (e) {
            console.log("disk_io: Starting with empty database.");
        }
    }

    // Save to disk
    save() {
        fs.writeFileSync(DB_FILE, JSON.stringify(this.tables, null, 2));
    }

    createTable(tableName) {
        if (this.tables[tableName]) {
            throw new Error(`Table '${tableName}' already exists.`);
        }
        this.tables[tableName] = new Table(tableName);
        this.save();
        return `Query OK. Table '${tableName}' created.`;
    }

    insert(tableName, values) {
        if (!this.tables[tableName]) throw new Error(`Table '${tableName}' not found.`);
        
        const table = this.tables[tableName];
        // We assume the first value is the ID, or we auto-generate if needed.
        // For this simple engine, we force the user to provide ID as first arg.
        const id = values[0]; 
        
        if (table.rows[id]) throw new Error(`Duplicate entry '${id}' for key 'PRIMARY'.`);

        // Store data
        table.rows[id] = values;
        this.save();
        return `Query OK. 1 row affected.`;
    }

    select(tableName, whereClause = null) {
        if (!this.tables[tableName]) throw new Error(`Table '${tableName}' not found.`);
        
        const table = this.tables[tableName];
        let results = Object.values(table.rows);

        // Handle WHERE clause (Simple equality check only: WHERE id = 1)
        if (whereClause) {
            const [colIndex, operator, value] = whereClause;
            // In our simple engine, columns are just indices (0, 1, 2...)
            // So "WHERE id = 5" usually means checking index 0
            
            if (operator === '=') {
                results = results.filter(row => row[colIndex] == value); // usage of == allows string/int match
            }
        }

        return results;
    }

    delete(tableName, id) {
        if (!this.tables[tableName]) throw new Error(`Table '${tableName}' not found.`);
        
        if (this.tables[tableName].rows[id]) {
            delete this.tables[tableName].rows[id];
            this.save();
            return `Query OK. Row '${id}' deleted.`;
        } else {
            return `Query OK. 0 rows affected (ID not found).`;
        }
    }
}

// --- 2. The Query Parser (The Interpreter) ---
// This translates human text into Engine Commands
const db = new Database();

function executeCommand(cmd) {
    const parts = cmd.trim().split(/\s+/); // Split by spaces
    const command = parts[0].toUpperCase();

    try {
        switch (command) {
            case 'CREATE':
                // SYNTAX: CREATE TABLE users
                if (parts[1].toUpperCase() === 'TABLE') {
                    return db.createTable(parts[2]);
                }
                break;

            case 'INSERT':
                // SYNTAX: INSERT INTO users VALUES (1, Tim, CEO)
                // Regex to capture table name and the content inside parenthesis
                const insertMatch = cmd.match(/INSERT INTO (\w+) VALUES \((.+)\)/i);
                if (insertMatch) {
                    const table = insertMatch[1];
                    const values = insertMatch[2].split(',').map(v => v.trim());
                    return db.insert(table, values);
                }
                break;

            case 'SELECT':
                // SYNTAX: SELECT * FROM users
                // SYNTAX: SELECT * FROM users WHERE 0 = 1 (Column 0 equals 1)
                const selectMatch = cmd.match(/SELECT \* FROM (\w+)(?: WHERE (\d+) (=) (.+))?/i);
                if (selectMatch) {
                    const table = selectMatch[1];
                    let where = null;
                    if (selectMatch[2]) {
                        where = [parseInt(selectMatch[2]), selectMatch[3], selectMatch[4]];
                    }
                    const rows = db.select(table, where);
                    
                    // Pretty Print
                    if (rows.length === 0) return "Empty set.";
                    console.table(rows);
                    return `${rows.length} rows in set.`;
                }
                break;
            
            case 'DELETE':
                // SYNTAX: DELETE FROM users WHERE 0 = 1
                const deleteMatch = cmd.match(/DELETE FROM (\w+) WHERE (\d+) = (.+)/i);
                if (deleteMatch) {
                    const table = deleteMatch[1];
                    // We only support deleting by Primary Key (index 0) in this version
                    const id = deleteMatch[3]; 
                    return db.delete(table, id);
                }
                break;

            case 'EXIT':
                process.exit(0);

            default:
                return `Syntax Error: Unknown command '${command}'`;
        }
    } catch (err) {
        return `Error: ${err.message}`;
    }
    return "Syntax Error: Check your SQL spelling.";
}

// --- 3. The REPL (Read-Eval-Print Loop) ---
// This simulates the MySQL Terminal interface
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: 'PocketSQL> '
});

console.log("\n--- PocketSQL Engine v1.0 ---");
console.log("Supported Commands:");
console.log("  CREATE TABLE <name>");
console.log("  INSERT INTO <name> VALUES (<id>, <val1>, <val2>...)");
console.log("  SELECT * FROM <name> [WHERE <col_index> = <value>]");
console.log("  DELETE FROM <name> WHERE 0 = <id>");
console.log("  EXIT\n");

rl.prompt();

rl.on('line', (line) => {
    if (line.trim()) {
        const result = executeCommand(line);
        if (result) console.log(result);
    }
    rl.prompt();
});