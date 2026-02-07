package main

import (
	"errors"
	"fmt"
	"sync"
)

// --- 1. CUSTOM ERROR HANDLING ---
// Go allows you to define static errors for easy checking later
var ErrInsufficientFunds = errors.New("transaction declined: insufficient funds")

// --- 2. INTERFACES (Polymorphism) ---
// Any struct that has a Pay() method satisfies this interface.
// This is how Go achieves flexibility without "inheritance".
type PaymentProcessor interface {
	Pay(amount float64) string
}

// --- 3. STRUCTS & COMPOSITION ---

// A "CreditCard" is one way to pay
type CreditCard struct {
	Owner      string
	CardNumber string
}

// Only CreditCard has this specific logic
func (cc CreditCard) Pay(amount float64) string {
	return fmt.Sprintf("Paid $%.2f using Card *%s (Owner: %s)",
		amount, cc.CardNumber[len(cc.CardNumber)-4:], cc.Owner)
}

// A "BitcoinWallet" is another way to pay
type BitcoinWallet struct {
	Address string
}

func (btc BitcoinWallet) Pay(amount float64) string {
	return fmt.Sprintf("Sent $%.2f equivalent to Crypto Addr: %s...",
		amount, btc.Address[:8])
}

// --- 4. THREAD-SAFE STRUCT (Mutex) ---

type BankAccount struct {
	Owner   string
	balance float64
	// Mutex protects the balance from being changed by two things at once
	mu sync.Mutex
}

// Constructor "Factory" Pattern
func NewAccount(owner string, initialBalance float64) *BankAccount {
	return &BankAccount{
		Owner:   owner,
		balance: initialBalance,
	}
}

// Method with "Pointer Receiver" (*BankAccount)
// We use a pointer because we want to modify the ACTUAL account, not a copy.
func (a *BankAccount) Deposit(amount float64) {
	a.mu.Lock()         // Lock the door
	defer a.mu.Unlock() // Unlock when function finishes

	fmt.Printf("[Log] Depositing $%.2f...\n", amount)
	a.balance += amount
}

func (a *BankAccount) Withdraw(amount float64) error {
	a.mu.Lock()
	defer a.mu.Unlock()

	if a.balance < amount {
		return ErrInsufficientFunds
	}

	fmt.Printf("[Log] Withdrawing $%.2f...\n", amount)
	a.balance -= amount
	return nil
}

func (a *BankAccount) GetBalance() float64 {
	a.mu.Lock()
	defer a.mu.Unlock()
	return a.balance
}

// --- MAIN EXECUTION ---

func main() {
	// 1. Create a new account
	myAccount := NewAccount("Admin User", 500.00)
	fmt.Println("--- Banking System Initialized ---")

	// 2. Simulate concurrent transactions (Stress Test)
	// We launch 5 transactions at the exact same time.
	// Without the 'mutex' in the struct, this would cause calculation errors.
	var wg sync.WaitGroup

	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			myAccount.Deposit(100.00)
		}(i)
	}

	wg.Wait() // Wait for all deposits to finish
	fmt.Printf("Balance after deposits: $%.2f\n\n", myAccount.GetBalance())

	// 3. Demonstrate Interfaces
	// We can put different types into a list of "PaymentProcessor"
	// because they both have the Pay() method.
	methods := []PaymentProcessor{
		CreditCard{Owner: "Admin", CardNumber: "1234567812349999"},
		BitcoinWallet{Address: "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"},
	}

	fmt.Println("--- Processing Payments ---")
	for _, method := range methods {
		// Go figures out which Pay() function to call automatically
		receipt := method.Pay(49.99)
		fmt.Println(receipt)
	}

	// 4. Error Handling Check
	err := myAccount.Withdraw(2000.00)
	if err != nil {
		if errors.Is(err, ErrInsufficientFunds) {
			fmt.Println("\nAlert: You are broke!")
		} else {
			fmt.Println("\nError:", err)
		}
	}
}
