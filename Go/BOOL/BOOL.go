package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// ============================================================================
// STRUCTS & TYPES
// ============================================================================

// BinaryOp defines a function that takes two booleans and returns a boolean (e.g., AND, OR).
type BinaryOp func(bool, bool) bool

// UnaryOp defines a function that takes one boolean and returns a boolean (e.g., NOT).
type UnaryOp func(bool) bool

// Color codes for terminal output to make it readable.
const (
	Reset  = "\033[0m"
	Bold   = "\033[1m"
	Red    = "\033[31m"
	Green  = "\033[32m"
	Yellow = "\033[33m"
	Blue   = "\033[34m"
	Cyan   = "\033[36m"
)

// ============================================================================
// MAIN EXECUTION
// ============================================================================

func main() {
	clearScreen()
	printHeader()

	reader := bufio.NewReader(os.Stdin)

	for {
		fmt.Println("\n" + Bold + "=== MASTER MENU ===" + Reset)
		fmt.Println("1. " + Cyan + "The Basics (True/False & Go Syntax)" + Reset)
		fmt.Println("2. " + Cyan + "Fundamental Operators (AND, OR, NOT)" + Reset)
		fmt.Println("3. " + Cyan + "Derived Logic (NAND, NOR, XOR, XNOR)" + Reset)
		fmt.Println("4. " + Cyan + "Truth Table Generator" + Reset)
		fmt.Println("5. " + Cyan + "Proving De Morgan's Laws" + Reset)
		fmt.Println("6. " + Cyan + "Boolean Associativity & Distributivity" + Reset)
		fmt.Println("Q. " + Red + "Quit" + Reset)
		fmt.Print("\nSelect a module: ")

		input, _ := reader.ReadString('\n')
		choice := strings.TrimSpace(strings.ToUpper(input))

		switch choice {
		case "1":
			runBasics()
		case "2":
			runFundamentalOps()
		case "3":
			runDerivedOps()
		case "4":
			runTruthTables()
		case "5":
			runDeMorgans()
		case "6":
			runLaws()
		case "Q":
			fmt.Println("Exiting Boolean Master. Goodbye!")
			return
		default:
			fmt.Println(Red + "Invalid selection. Please try again." + Reset)
		}
		pause()
	}
}

// ============================================================================
// MODULE 1: BASICS
// ============================================================================

func runBasics() {
	printSectionHeader("1. The Basics of Boolean Algebra")
	
	fmt.Printf("In Boolean Algebra, there are only two possible values:\n")
	fmt.Printf(" - %s1%s (represented in Go as %s%v%s)\n", Green, Reset, Green, true, Reset)
	fmt.Printf(" - %s0%s (represented in Go as %s%v%s)\n", Red, Reset, Red, false, Reset)
	
	fmt.Println("\nIn Go, we define these using the `bool` type.")
	
	var a bool = true
	var b bool = false
	
	fmt.Printf("Variable 'a' is: %v\n", a)
	fmt.Printf("Variable 'b' is: %v\n", b)
}

// ============================================================================
// MODULE 2: FUNDAMENTAL OPERATORS
// ============================================================================

func runFundamentalOps() {
	printSectionHeader("2. Fundamental Operators")

	// NOT
	fmt.Println(Yellow + "A. The NOT Operator (Inversion)" + Reset)
	fmt.Println("Symbol: " + Bold + "!" + Reset + " (Go), ¬ or ̅ (Math)")
	fmt.Println("Logic: Flips the value. True becomes False, False becomes True.")
	drawGate("NOT")
	printUnaryTruthTable("NOT (!A)", func(a bool) bool { return !a })

	pause()

	// AND
	fmt.Println(Yellow + "B. The AND Operator (Conjunction)" + Reset)
	fmt.Println("Symbol: " + Bold + "&&" + Reset + " (Go), ∧ or · (Math)")
	fmt.Println("Logic: Returns True ONLY if both inputs are True.")
	drawGate("AND")
	printBinaryTruthTable("AND (A && B)", func(a, b bool) bool { return a && b })

	pause()

	// OR
	fmt.Println(Yellow + "C. The OR Operator (Disjunction)" + Reset)
	fmt.Println("Symbol: " + Bold + "||" + Reset + " (Go), ∨ or + (Math)")
	fmt.Println("Logic: Returns True if AT LEAST one input is True.")
	drawGate("OR")
	printBinaryTruthTable("OR (A || B)", func(a, b bool) bool { return a || b })
}

// ============================================================================
// MODULE 3: DERIVED OPERATORS
// ============================================================================

func runDerivedOps() {
	printSectionHeader("3. Derived Logic Gates")
	fmt.Println("These operators are built by combining AND, OR, and NOT.")

	// NAND
	fmt.Println(Blue + "\nA. NAND (Not AND)" + Reset)
	fmt.Println("Logic: The opposite of AND. True unless both are True.")
	fmt.Println("Go Code: !(a && b)")
	printBinaryTruthTable("NAND", func(a, b bool) bool { return !(a && b) })

	// XOR
	fmt.Println(Blue + "\nB. XOR (Exclusive OR)" + Reset)
	fmt.Println("Logic: True if inputs are DIFFERENT. False if they are the same.")
	fmt.Println("Go Code: a != b")
	printBinaryTruthTable("XOR", func(a, b bool) bool { return a != b })

	// XNOR
	fmt.Println(Blue + "\nC. XNOR (Exclusive NOR)" + Reset)
	fmt.Println("Logic: True if inputs are the SAME (Equivalence).")
	fmt.Println("Go Code: a == b")
	printBinaryTruthTable("XNOR", func(a, b bool) bool { return a == b })
}

// ============================================================================
// MODULE 4: TRUTH TABLE GENERATOR
// ============================================================================

func runTruthTables() {
	printSectionHeader("4. Dynamic Truth Table Generator")
	fmt.Println("Let's compare Complex Logic vs Simplified Logic.")
	
	// Example: (A || B) && !A  should simplify to (!A && B)
	complexOp := func(a, b bool) bool {
		return (a || b) && !a
	}
	
	fmt.Println(Bold + "\nFunction: f(A,B) = (A OR B) AND (NOT A)" + Reset)
	printBinaryTruthTable("(A || B) && !A", complexOp)
	
	fmt.Println("\nNotice the result? It is identical to: " + Bold + "(!A && B)" + Reset)
	fmt.Println("This proves that logic can be simplified!")
}

// ============================================================================
// MODULE 5: DE MORGAN'S LAWS
// ============================================================================

func runDeMorgans() {
	printSectionHeader("5. De Morgan's Laws")
	fmt.Println("Augustus De Morgan gave us two transformation rules that allow us")
	fmt.Println("to convert ANDs to ORs (and vice-versa) by inverting inputs/outputs.")

	// First Law
	fmt.Println(Cyan + "\nLaw 1: !(A && B) == !A || !B" + Reset)
	fmt.Println("The negation of a conjunction is the disjunction of the negations.")
	
	verifyLaw("De Morgan 1", func(a, b bool) (bool, bool) {
		lhs := !(a && b)
		rhs := !a || !b
		return lhs, rhs
	})

	// Second Law
	fmt.Println(Cyan + "\nLaw 2: !(A || B) == !A && !B" + Reset)
	fmt.Println("The negation of a disjunction is the conjunction of the negations.")
	
	verifyLaw("De Morgan 2", func(a, b bool) (bool, bool) {
		lhs := !(a || b)
		rhs := !a && !b
		return lhs, rhs
	})
}

// ============================================================================
// MODULE 6: OTHER LAWS
// ============================================================================

func runLaws() {
	printSectionHeader("6. Other Important Boolean Laws")

	fmt.Println(Yellow + "Distributive Law:" + Reset + " A && (B || C) == (A && B) || (A && C)")
	
	// Since our verifyLaw only takes 2 inputs, we will do a manual check here for 3 inputs
	fmt.Println("\nChecking for all combinations of A, B, C...")
	fmt.Printf("%-5s %-5s %-5s | %-15s | %-15s | %s\n", "A", "B", "C", "LHS", "RHS", "Match?")
	fmt.Println(strings.Repeat("-", 65))

	inputs := []bool{false, true}
	
	for _, a := range inputs {
		for _, b := range inputs {
			for _, c := range inputs {
				lhs := a && (b || c)
				rhs := (a && b) || (a && c)
				match := "❌"
				if lhs == rhs { match = "✅" }
				
				fmt.Printf("%-5v %-5v %-5v | %-15v | %-15v | %s\n", 
					boolToInt(a), boolToInt(b), boolToInt(c), lhs, rhs, match)
			}
		}
	}
}

// ============================================================================
// HELPER FUNCTIONS & VISUALS
// ============================================================================

func printUnaryTruthTable(name string, op UnaryOp) {
	fmt.Printf("\nTruth Table: %s\n", name)
	fmt.Println("+-------+-------+")
	fmt.Println("|   A   |  OUT  |")
	fmt.Println("+-------+-------+")
	for _, a := range []bool{false, true} {
		result := op(a)
		fmt.Printf("|   %d   |   %d   |  (%v -> %v)\n", boolToInt(a), boolToInt(result), a, result)
	}
	fmt.Println("+-------+-------+")
}

func printBinaryTruthTable(name string, op BinaryOp) {
	fmt.Printf("\nTruth Table: %s\n", name)
	fmt.Println("+-------+-------+-------+")
	fmt.Println("|   A   |   B   |  OUT  |")
	fmt.Println("+-------+-------+-------+")
	inputs := []bool{false, true}
	for _, a := range inputs {
		for _, b := range inputs {
			result := op(a, b)
			fmt.Printf("|   %d   |   %d   |   %d   |\n", boolToInt(a), boolToInt(b), boolToInt(result))
		}
	}
	fmt.Println("+-------+-------+-------+")
}

// verifyLaw iterates inputs, calculates Left Hand Side and Right Hand Side, and checks equality
func verifyLaw(name string, lawFunc func(bool, bool) (bool, bool)) {
	fmt.Printf("\nVerifying %s:\n", name)
	inputs := []bool{false, true}
	allPassed := true
	
	fmt.Println(" A | B | LHS Result | RHS Result | Match?")
	fmt.Println("---|---|------------|------------|-------")
	
	for _, a := range inputs {
		for _, b := range inputs {
			lhs, rhs := lawFunc(a, b)
			match := lhs == rhs
			if !match { allPassed = false }
			
			symbol := "✅"
			if !match { symbol = "❌" }
			
			fmt.Printf(" %d | %d | %-10v | %-10v | %s\n", 
				boolToInt(a), boolToInt(b), lhs, rhs, symbol)
		}
	}
	
	if allPassed {
		fmt.Println(Green + ">>> LAW PROVEN VALID" + Reset)
	} else {
		fmt.Println(Red + ">>> LAW DISPROVEN" + Reset)
	}
}

func boolToInt(b bool) int {
	if b { return 1 }
	return 0
}

func printHeader() {
	fmt.Println(Blue + "==========================================")
	fmt.Println("     THE GO BOOLEAN ALGEBRA MASTER       ")
	fmt.Println("==========================================" + Reset)
	fmt.Println("Written in Go. Concepts valid everywhere.")
}

func printSectionHeader(title string) {
	clearScreen()
	fmt.Println(Bold + "\n" + strings.Repeat("=", len(title)))
	fmt.Println(title)
	fmt.Println(strings.Repeat("=", len(title)) + Reset + "\n")
}

func pause() {
	fmt.Print("\nPress 'Enter' to continue...")
	bufio.NewReader(os.Stdin).ReadBytes('\n')
}

func clearScreen() {
	fmt.Print("\033[H\033[2J") // ANSI escape code to clear screen
}

func drawGate(gateType string) {
	switch gateType {
	case "AND":
		fmt.Println(`
    A ─────┐
           │D──── OUT
    B ─────┘
		`)
	case "OR":
		fmt.Println(`
    A ────┐
          )──── OUT
    B ────┘
		`)
	case "NOT":
		fmt.Println(`
    A ───▷o─── OUT
		`)
	}
}