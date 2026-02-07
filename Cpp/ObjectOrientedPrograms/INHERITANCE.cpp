#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. BASE CLASS (The Parent)
// Contains logic common to ALL characters.
// ==========================================
class GameCharacter {
protected: 
    // 'protected': Accessible inside this class AND inside Derived classes.
    // (Unlike 'private', which is hidden even from children).
    string name;
    int health;
    int level;

public:
    // Base Constructor
    GameCharacter(string n, int h, int l) {
        name = n;
        health = h;
        level = l;
        cout << "[Base] Character '" << name << "' created." << endl;
    }

    // A method common to everyone
    void displayStats() {
        cout << "\n--- Stats for " << name << " ---" << endl;
        cout << "Health: " << health << " | Level: " << level << endl;
    }

    void heal(int amount) {
        health += amount;
        cout << name << " heals for " << amount << " HP!" << endl;
    }
};

// ==========================================
// 2. DERIVED CLASS: Warrior (The Child)
// Inherits everything from GameCharacter.
// Adds armor logic and sword attacks.
// ==========================================
class Warrior : public GameCharacter {
private:
    int armorRating; // Unique to Warrior

public:
    // Constructor Chaining:
    // We pass 'n', 'h', 'l' up to the Base Constructor using ": GameCharacter(...)"
    Warrior(string n, int h, int l, int armor) : GameCharacter(n, h, l) {
        armorRating = armor;
        cout << "[Derived] Warrior class initialized." << endl;
    }

    // Unique Method for Warrior
    void swingSword() {
        cout << name << " swings a giant sword! (Damage: " << level * 5 << ")" << endl;
    }

    // Using 'protected' variable 'health' from Base class
    void takeDamage(int dmg) {
        int reducedDmg = dmg - (armorRating / 2);
        if (reducedDmg < 0) reducedDmg = 0;
        
        health -= reducedDmg;
        cout << name << " takes " << reducedDmg << " damage (Armor blocked " << (dmg - reducedDmg) << ")." << endl;
    }
};

// ==========================================
// 3. DERIVED CLASS: Mage (Another Child)
// Inherits from GameCharacter.
// Adds mana logic and spells.
// ==========================================
class Mage : public GameCharacter {
private:
    int mana; // Unique to Mage

public:
    Mage(string n, int h, int l, int m) : GameCharacter(n, h, l) {
        mana = m;
        cout << "[Derived] Mage class initialized." << endl;
    }

    // Unique Method for Mage
    void castFireball() {
        if (mana >= 10) {
            mana -= 10;
            cout << name << " casts Fireball! (Mana left: " << mana << ")" << endl;
        } else {
            cout << name << " is out of mana!" << endl;
        }
    }
};

// ==========================================
// 4. MAIN EXECUTION
// ==========================================
int main() {
    cout << "=========================================" << endl;
    cout << "      INHERITANCE IN RPG CHARACTERS" << endl;
    cout << "=========================================" << endl;

    // 1. Create a Warrior
    // Notice: It calls Base Constructor FIRST, then Warrior Constructor
    cout << "\n1. Spawning Warrior:" << endl;
    Warrior aragorn("Aragorn", 100, 5, 20); // Name, HP, Level, Armor

    // 2. Use Base Class Methods (Code Reusability)
    aragorn.displayStats(); // Defined in GameCharacter, used by Warrior
    
    // 3. Use Derived Class Methods (Specialization)
    aragorn.swingSword();   // Only Warrior has this
    aragorn.takeDamage(30); // Uses Armor logic specific to Warrior
    aragorn.displayStats(); // Check health update


    // 4. Create a Mage
    cout << "\n2. Spawning Mage:" << endl;
    Mage gandalf("Gandalf", 60, 10, 50); // Name, HP, Level, Mana

    gandalf.displayStats(); // Reusing Base code again
    gandalf.castFireball(); // Only Mage has this
    gandalf.heal(20);       // Inherited from Base

    cout << "\n=========================================" << endl;
    return 0;
}