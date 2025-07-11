# Zoo Battle Arena

Welcome to Zoo Battle Arena! This is a simple, console-based C++ game where you can create teams of animals and have them battle against each other in an arena. The project is a practical demonstration of several key Object-Oriented Programming (OOP) principles.

## How It Works

The game prompts two players to build their teams, the "Warriors" and the "Pacers." Each player can choose from a selection of animals, each with unique stats (health and attack power), and give them custom names. Once the teams are assembled, the battle begins! The animals from each team take turns attacking the opposing team's active animal until one team has no conscious fighters left.

## How to Compile and Run

To compile and run this project, you will need a C++ compiler (like G++).

```bash
# Compile the code
g++ zooBattleArena.cpp -o zoo_battle

# Run the executable
./zoo_battle
```

## Key OOP Concepts Illustrated

This program is structured around fundamental OOP concepts to create a flexible and extensible system. Here's a breakdown of the OOP features used:

### 1. Abstraction

Abstraction is about hiding complex implementation details and showing only the essential features of the object. In this code, the Animal class is a perfect example of an abstract base class.

It provides a general template for what an "Animal" is (it has a name, health, and attack power).
It declares functions that every animal must be able to perform, but it doesn't define how they do it. These are called pure virtual functions, like performAttack() and getAnimalType(). This ensures that any class inheriting from Animal must provide its own specific implementation for these actions.

```cpp
class Animal {
protected:
    // ... attributes
public:
    // ... common methods
    virtual void performAttack(Animal* targetAnimal) = 0; // Pure virtual function
    virtual string getAnimalType() = 0; // Pure virtual function
};
```

### 2. Inheritance

Inheritance allows a new class (subclass or derived class) to inherit properties and methods from an existing class (base class or parent class). This promotes code reuse.

Specific animal classes like Lion, Eagle, Elephant, and Shark inherit from the base Animal class. This means they automatically get the name, health, and attackPower attributes, as well as common methods like takeDamage() and isAlive().

Multiple Inheritance is also demonstrated. The Eagle and Shark classes inherit from two base classes. The Eagle inherits from both Animal and Flyable, while the Shark inherits from Animal and Swimmable. This allows them to have behaviors from both parent classes.

```cpp
class Lion : public Animal { /* ... */ };
class Eagle : public Animal, public Flyable { /* ... */ };
class Shark : public Animal, public Swimmable { /* ... */ };
```

### 3. Encapsulation

Encapsulation is the bundling of data (attributes) and the methods that operate on that data into a single unit, a class. It also involves restricting direct access to some of an object's components.

The Animal class encapsulates the name, health, and attackPower data. These are declared as protected, meaning they can only be accessed by the Animal class itself and its subclasses (Lion, Eagle, etc.).

Public methods like getHealth() and getAttackPower() are provided to allow controlled access to this data from outside the class. This prevents the data from being modified in unexpected ways.

### 4. Polymorphism

Polymorphism, which means "many forms," allows objects of different classes to be treated as objects of a common superclass. This is achieved through virtual functions and method overriding.

The performAttack() function is declared as virtual in the Animal class and is then overridden in each specific animal subclass.

This means that when the BattleArena calls attacker->performAttack(defender), the program knows to execute the correct version of the attack based on the attacker's actual type (e.g., the Lion's claw attack or the Eagle's aerial strike), even though the attacker is stored as a pointer to the base Animal class. This makes the battle logic clean and easy to manage, as the arena doesn't need to know the specific type of animal that is fighting.

```cpp
// In the Eagle class, overriding the performAttack method
void performAttack(Animal* target) override {
    fly(); // Eagle's unique action
    cout << name << " attacks from above to " << target->getName() << endl;
    target->takeDamage(attackPower);
}
```

By using these OOP principles, the code is organized, easy to maintain, and can be easily extended with new animals or abilities without having to rewrite existing logic.
