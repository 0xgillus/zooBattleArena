#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Animal {
protected:

string name;  
int health;  
int attackPower;

public:

Animal(string animalName, int hp, int attack) {  
    name = animalName;  
    health = hp;  
    attackPower = attack;  
}  
  
  
string getName() {   
    return name; }  


int getHealth() {   
    return health; }  


int getAttackPower() {   
    return attackPower; }  
  


void takeDamage(int damage) {  
    health = health - damage;  
    if (health < 0) {  
        health = 0;  
    }    
    cout << name << " takes " << damage << " damage Health now: " << health << endl;  
}  
  

bool isAlive() {  
    return health > 0;  
}  
  
virtual void performAttack(Animal* targetAnimal) = 0;  
  
virtual void displayStats() {  
    cout << name << " HP: " << health << ", Attack: " << attackPower <<endl;  
}  
  

virtual string getAnimalType() = 0;

};

class Flyable {
public:

virtual void fly() = 0;

};

class Swimmable {
public:

virtual void swim() = 0;

};

class Lion : public Animal {

private:  
    string lion;  

public:  
Lion(string lionName) : lion(lionName), Animal(lionName, 100, 25) {}  
  
void performAttack(Animal* target) override {  
    if (target && target->isAlive()) {  
        cout << name << " attacks with its claws to " << target->getName() << endl;  
        target->takeDamage(attackPower);  
    }  
}  
  
string getAnimalType() override {   
    return lion; }  
  

void displayStats() override {  
    Animal::displayStats();  

}

};

class Eagle : public Animal, public Flyable {

private:  
        string eagle_name;  
public:  
Eagle(string eagleName) : eagle_name(eagleName), Animal(eagleName, 75, 20) {}  
  
void fly() override {  
    cout << name << " flys thru the sky" << endl;  
}  

void performAttack(Animal* target) override {  
    fly();  
    if (target && target->isAlive()) {  
        cout << name << " attacks from above to " << target->getName() << endl;  
        target->takeDamage(attackPower);  
    }  
}  


string getAnimalType() override {   
    return eagle_name; }  
  
void displayStats() override {  
    Animal::displayStats();  
}

};

class Elephant : public Animal {
private:
string elephant_Name;
public:

Elephant(string elephantName) : elephant_Name(elephantName), Animal(elephantName, 150, 30) {}  
  
void performAttack(Animal* target) override {  
    if (target && target->isAlive()) {  
        cout << name << " attacks with its trunk to " << target->getName() << endl;  
        target->takeDamage(attackPower);  
    }  
}  
  
string getAnimalType() override {   
    return elephant_Name; }  
  
void displayStats() override {  
    Animal::displayStats();  

}

};

class Shark : public Animal, public Swimmable {
private:
string sharkName;

public:

Shark(string sharkName) : Animal(sharkName, 85, 35), sharkName(sharkName) {}  
  
void swim() override {  
    cout << name << " goes deep in water" << endl;  
}  
  
void performAttack(Animal* target) override {  
    swim();  
    if (target && target->isAlive()) {  
        cout << name << " strikes with sharp tooth below to " << target->getName() << endl;  
        target->takeDamage(attackPower);  
    }  
}  
  

  
string getAnimalType() override {   
    return sharkName; }  
  
void displayStats() override {  
    Animal::displayStats();  
}

};

class Team {
private:
string teamName;
vector<Animal*> fighters;

public:

Team(string name) : teamName(name) {}  
  
  
void addFighter(Animal* a) {  
    if (a) {  
        fighters.push_back(a);  
        cout << a->getName() << " joins Team " << teamName <<  endl;  
    }  
}  
  

Animal* getNextFighter() {  
    for (Animal* fighter : fighters) {  
        if (fighter && fighter->isAlive()) {  
            return fighter;  
        }  
    }  

    return nullptr;  
}  
  
bool hasAliveFighters() {  
    for (Animal* fighter : fighters) {  
        if (fighter && fighter->isAlive()) {  
            return true;  
        }  
    }  

    return false;  
}  
  

void displayTeam() {  
    cout << "\nTeam " << teamName <<  endl;  
    for (Animal* fighter : fighters) {  
        if (fighter) {  
            fighter->displayStats();  
              
        }  
    }  
}  
  

string getTeamName() {   
    return teamName; }  

int getTeamSize() {   
    return fighters.size(); }

};

class BattleArena {
private:
Team* team1;
Team* team2;

public:

BattleArena(Team* team_One, Team* team_Two) {  
    team1 = team_One;  
    team2 = team_Two;  
}  
  

void conductBattle() {  
    cout << "\nBATTLE BEGINS: " << team1->getTeamName()   
         << " vs " << team2->getTeamName() << endl;  
      
    int round = 1;  
      

    while (team1->hasAliveFighters() && team2->hasAliveFighters()) {  
        cout << "\nRound " << round <<  endl;  
          
        Animal* attacker = team1->getNextFighter();  
        Animal* defender = team2->getNextFighter();  
          
        if (attacker && defender) {  
            attacker->performAttack(defender);  
        }  
          
        if (!team2->hasAliveFighters()) {  
             break;  
        }  
          

        attacker = team2->getNextFighter();  
        defender = team1->getNextFighter();  
          
        if (attacker && defender) {  
            attacker->performAttack(defender);  
        }  
          

        round++;  
          
        if (round > 15) {  
            cout << "\nBattle timeout - it's a draw" << endl;  
            return;  
        }  
    }  
      
    if (team1->hasAliveFighters()) {  
        cout << team1->getTeamName() << " win" << endl;  

    }   
    else {  
            cout << team2->getTeamName() << " win" << endl;  

    }  
}

};

Animal* createAnimal(int choice, string name) {
switch (choice) {
case 1:
return new Lion(name);
case 2:
return new Eagle(name);
case 3:
return new Elephant(name);
case 4:
return new Shark(name);
default:
cout << "Invalid choice! Creating a Lion by default";
return new Lion(name);
}
}

Team* buildTeam(string teamName, int maxAnimals) {
Team* team = new Team(teamName);

cout << "\nBuilding Team " << teamName << endl;  
cout << "You can add up to " << maxAnimals << " animals to your team." << endl;  
  
for (int i = 0; i < maxAnimals; i++) {  
        cout << "\nAdding Fighter" << (i + 1) << endl;  
    cout << "\nAvailable Animals:" << endl;  
    cout << "1. Lion - Fighter HP: 100, Attack: 25" << endl;  
    cout << "2. Eagle - Striker HP: 75, Attack: 20" << endl;  
    cout << "3. Elephant - Tank HP: 150, Attack: 30" << endl;  
    cout << "4. Shark - Duelist HP: 85,Attack: 35" << endl;  
      
    int choice;  
    cout << "Choose animal type 1-4: ";  
    cin >> choice;  
      
    string animalName;  
    cout << "Give your animal a name: ";  
    cin >> animalName;  
      
    Animal* newAnimal = createAnimal(choice, animalName);  

    team->addFighter(newAnimal);  
      

    cout << "Added: ";  
    newAnimal->displayStats();  
      
      
    if (i < maxAnimals - 1) {  
        char continueChoice;  
        cout << "Add another animal? y/n: ";  
        cin >> continueChoice;  
        if (continueChoice != 'y' && continueChoice != 'Y') {  
            break;  
        }  

    }  
}  
  
return team;

}

void modifyTeamOption(Team* team, string teamName, int maxAnimals) {

if (team->getTeamSize() >= maxAnimals) {  
    cout << "Team is already at maximum capacity" << endl;  
}  
  
char modify;  
cout << "\nWould you like to add more animals to " << teamName << "? y/n: ";  
cin >> modify;  
  
if (modify == 'y' || modify == 'Y') {  
    int remainingSlots = maxAnimals - team->getTeamSize();  
    cout << "You can add " << remainingSlots << " more animals" << endl;  
      
    for (int i = 0; i < remainingSlots; i++) {  
        cout << "\nAvailable Animals:" << endl;  
        cout << "1. Lion - Fighter HP: 100, Attack: 25" << endl;  
        cout << "2. Eagle - Striker HP: 75, Attack: 20" << endl;  
        cout << "3. Elephant - Tank HP: 150, Attack: 30" << endl;  
        cout << "4. Shark - Duelist HP: 85,Attack: 35" << endl;  
          
        int choice;  
        cout << "Choose animal type 1-4, or 0 to stop: ";  
        cin >> choice;  
          
        if (choice == 0) {  
            break;  
        }   
          
        string animalName;  
        cout << "Give your animal a name: " <<endl;  
        cin >> animalName;  
          
        Animal* newAnimal = createAnimal(choice, animalName);  
        team->addFighter(newAnimal);  
          
        cout << "Added: ";  
        newAnimal->displayStats();  
          
    }  
}

}

int main() {
cout << "\nWELCOME TO ZOO BATTLE ARENA!" << endl;
cout << "Build your team and fight for victory!" << endl;

int MAX_TEAM_SIZE = 3;

Team* t1 = buildTeam("Warriors", MAX_TEAM_SIZE);  
  
 
Team* t2 = buildTeam("Pacers", MAX_TEAM_SIZE);  
  
  

modifyTeamOption(t1, "Warriors", MAX_TEAM_SIZE);  
modifyTeamOption(t2, "Pacers", MAX_TEAM_SIZE);  
  

cout << "\nFINAL TEAMS:" << endl;  
t1->displayTeam();  
t2->displayTeam();  

BattleArena arena(t1, t2);  
arena.conductBattle();  
 
 
return 0;

}