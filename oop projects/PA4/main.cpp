#include <iostream>
#include <string>
#include <time.h>

using namespace std;
// INITIAL CONSTANT VARIABLES
const int WORLDSIZE = 10;
const int INITIAL_ROBOT_NUMBER = 5;
const int KAMIKAZE = 1;
const int BULLDOZER = 2;
const int ROOMBA = 3;
const int OPTIMUSPRIME = 4;
const int ROBOCOP = 5;
int TOTAL_ROBOT = 0; 

// FORWARD DECLARATIONS OF CLASSES
class Robot;
class Kamikaze;
class Bulldozer;
class Roomba;
class Humanic;
class Optimusprime;
class Robocop;

// ------------------------------------------------------------------------------------------

class World {
//                     FRIEND CLASSES OF WORLD TO CHANGE IT
friend class Robot;
friend class Kamikaze;
friend class Bulldozer;
friend class Roomba;
friend class Humanic;
friend class Optimusprime;
friend class Robocop;

public : 
World(); // CONSTRUCTOR
~World(); // DESTRUCTOR OF MAP
Robot* getAt(int x, int y); // GETTER OF A ROBOT
void setAt(int x, int y, Robot *rob); // SETTER OF A ROBOT
void Simulate(); // SIMULATE THE GAME


private:
Robot* grid[WORLDSIZE][WORLDSIZE]; // IT'S ARENA IN WHICH ROBOTS FIGHT (MAP)

};

World::World() {
    for(int i=0;i<WORLDSIZE;i++) {
        for(int j=0;j<WORLDSIZE;j++) {
            grid[i][j] = NULL; // MAKE ALL OBJECTS NULL AT THE FIRST
        }
    }
}

Robot* World::getAt(int x, int y) {
if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE))
return grid[x][y]; // GET OBJECT WITH COORDINATES

return NULL;
}

void World::setAt(int x, int y, Robot *rob) {
if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE)) {
grid[x][y] = rob; // SET OBJECT ON A COORDINATE
}
}

// ------------------------------------------------------------------------------------------

class Robot
{
friend class World;

protected: // ROBOT PRORPERTIES
string name;
int strength;
int hitpoint;
int x,y;
bool moved;
World* world;

public :
Robot();
Robot(World *wrld, int x, int y);
bool fight(Robot& opponent);
int* move();
virtual ~Robot();
virtual int getType() = 0;
virtual int getDamage();

};

World::~World() {

    for (int i=0; i<WORLDSIZE; i++) {
        for (int j=0; j<WORLDSIZE; j++) { // DESTRUCTOR OF MAP DELETING ALL OBJECTS
            if (grid[i][j]!=NULL) delete (grid[i][j]);
        }
    }
}

Robot::Robot() { // ROBOT DEFAULT CONSTRUCTOR
name = "";
hitpoint = 0;
strength = 0;
world = NULL;
moved = false;
x=0;
y=0;
}

Robot::Robot(World* wrld, int x, int y) { // ROBOT PARAMETERIZED CONSTRUCTOR
name = "";
hitpoint = 0;
strength = 0;
this->world = wrld;
moved = false;
this->x=x;
this->y=y;
wrld->setAt(x,y,this);
}

Robot::~Robot() {

}

int Robot::getDamage() { // MAKE A RANDOM DAMAGE BETWEEN STRENGTH AND ZERO
    int damage;
    damage = (rand() % strength) + 1 ;

    return damage;
}

bool Robot::fight(Robot& opponent) { // FINGHT FUNCTION TO DETERMINE WHETER KILLED OR BECOME KILLED

    int damage;

    while( this->hitpoint > 0 ) { // FIGHT AS LONG AS ONE OF THEM ALIVE
    damage = this->getDamage();
    opponent.hitpoint -= damage;
    cout << this->name << "(" << this->hitpoint << ") hits " << opponent.name << "(" << opponent.hitpoint+damage << ") with " << damage << endl;
    cout << "The new hitpoints of " << opponent.name << " is ";
    
    if(opponent.hitpoint <= 0) cout << "0" << endl;
    else cout << opponent.hitpoint << endl;
    

    if(this->getType() == KAMIKAZE) { // KAMIKAZE DIES AFTER SHOT
        cout << endl << endl;
        return false;
    }

    if(opponent.hitpoint <= 0) { // CHECK IF ENEMY DIED
        cout << endl << endl;
        return true;
    }
    else {
        damage = opponent.getDamage(); // OPPONENT ATTACKS
        this->hitpoint -= damage;
        cout << opponent.name << "(" << opponent.hitpoint << ") hits " << this->name << "(" << this->hitpoint+damage << ") with " << damage << endl;
        cout << "The new hitpoints of " << this->name << " is ";

        if(this->hitpoint <= 0) cout << "0" << endl;
        else cout << this->hitpoint << endl;

        if(opponent.getType() == KAMIKAZE ) { // CHECK IF THE OPPONENT IS TYPE OF KAMIKAZE SO IT DIES
            cout << endl << endl;
            return true;
        }
    }
    }

    cout << endl << endl;
    return false;

}



// ------------------------------------------------------------------------------------------

// This class represents a Kamikaze robot, which is a subclass of the Robot class.

class Kamikaze : public Robot {

public:
    // Constructor without parameters
    Kamikaze();

    // Constructor with parameters
    Kamikaze(World* world, int x, int y, int strength, int hp);

    // Static variable to keep track of the total number of Kamikaze robots
    static int total;

    // Method to get the type of the robot
    int getType();

    // Method to get the damage inflicted by the robot
    int getDamage();

};

// Initializing the static variable total outside the class definition
int Kamikaze::total = 0;

// Implementation of the default constructor
Kamikaze::Kamikaze() : Robot() {
    // Incrementing the total count of Kamikaze robots
    total++;
    // Incrementing the total count of robots (inherited from Robot class)
    TOTAL_ROBOT++;
}

// Implementation of the parameterized constructor
Kamikaze::Kamikaze(World* world, int x, int y, int strngth, int hp) : Robot(world, x, y) {
    // Assigning values to the strength and hitpoint attributes
    strength = strngth;
    hitpoint = hp;
    // Generating a name for the Kamikaze robot based on its total count
    name = "kamikaze_" + to_string(total);
    // Incrementing the total count of Kamikaze robots
    total++;
    // Incrementing the total count of robots (inherited from Robot class)
    TOTAL_ROBOT++;
}

// Implementation of the getType method
int Kamikaze::getType() {
    // Returning the type identifier for Kamikaze robots
    return KAMIKAZE;
}

// Implementation of the getDamage method
int Kamikaze::getDamage() {
    // Returning the damage inflicted by the Kamikaze robot
    int damage = strength;
    return damage;
}


// ------------------------------------------------------------------------------------------

// Bulldozer class inheriting from Robot
class Bulldozer : public Robot {
public:
    // Constructors
    Bulldozer();
    Bulldozer(World* world, int x, int y, int strength, int hp);

    // Static member to track total Bulldozers created
    static int total;

    // Member functions
    int getType();
    int getDamage();
};

// Initialize static member total
int Bulldozer::total = 0;

// Default constructor
Bulldozer::Bulldozer() : Robot() {
    // Increment total Bulldozers and total robots
    total++;
    TOTAL_ROBOT++;
}

// Parameterized constructor
Bulldozer::Bulldozer(World* world, int x, int y, int strngth, int hp) : Robot(world, x, y) {
    // Set strength, hitpoints, and name of the Bulldozer
    strength = strngth;
    hitpoint = hp;
    name = "bulldozer_" + to_string(total);
    // Increment total Bulldozers and total robots
    total++;
    TOTAL_ROBOT++;
}

// Function to get the type of the Bulldozer
int Bulldozer::getType() {
    return BULLDOZER;
}

// Function to calculate the damage of the Bulldozer
int Bulldozer::getDamage() {
    // Calculate damage using base class function
    int damage = Robot::getDamage();
    return damage;
}


// ------------------------------------------------------------------------------------------

class Roomba : public Robot {

public : 
static int total;
Roomba();
Roomba(World* world, int x, int y, int strength, int hp);
int getType();
int getDamage();
};

int Roomba::total = 0;

Roomba::Roomba() : Robot() {
    total++;
    TOTAL_ROBOT++;
}

Roomba::Roomba(World* world, int x, int y, int strngth, int hp) : Robot(world,x,y) {
    
    strength = strngth;
    hitpoint = hp;
    name = "roomba_" + to_string(total);
    total++;
    TOTAL_ROBOT++;
    
}

int Roomba::getType() {
    return ROOMBA;
}

int Roomba::getDamage() {

    int damage=0;
    damage += Robot::getDamage();
    damage += Robot::getDamage();

    return damage;
}

// ------------------------------------------------------------------------------------------

class Humanic : public Robot {

public : 
Humanic();
Humanic(World* world, int x, int y);
virtual int getDamage();

};

Humanic::Humanic() : Robot() {

};

Humanic::Humanic(World* world,int x,int y) : Robot(world,x,y) {

};

int Humanic::getDamage() { 

    int damage;
    damage = Robot::getDamage();

    int randomVar;
    randomVar = (rand()%10) + 1;

    if(randomVar == 1) { // %10 CHANGE TO HIT EXTRA 50 DAMAGE
        damage += 50;
    }

    return damage;
}


// ------------------------------------------------------------------------------------------

// OPTIMUSPRIME ROBOT INHERITED FROM HUMANIC ROBOTS
class Optimusprime : public Humanic {

public : 
Optimusprime();
Optimusprime(World* world, int x, int y, int strength, int hp);
static int total;
int getType();
int getDamage();
};

int Optimusprime::total = 0;

Optimusprime::Optimusprime() : Humanic() {
    name = "optimusprime_" + to_string(total); // DEFAULT CONSTRUCTOR FOR OPTIMUSPRIME
    total++;
    TOTAL_ROBOT++;
}

Optimusprime::Optimusprime(World* world, int x, int y, int strngth, int hp) : Humanic(world,x,y) {
    strength = strngth;
    hitpoint = hp;
    name = "optimusprime_" + to_string(total); // CONSTRUCTOR FOR OPTIMUSPRIME
    total++;
    TOTAL_ROBOT++;
}

int Optimusprime::getType() { // FUNCTION RETURNS TYPE
    return OPTIMUSPRIME;
}

int Optimusprime::getDamage() {
    
    int damage = Humanic::getDamage(); 

    int randomVar;
    randomVar = (rand()%100) + 1; // %15 CHANCE TO DOUBLE ATTACK

    if( randomVar >= 1 && randomVar <= 15) {
        damage*=2;
    }

    

    return damage;
}

// ------------------------------------------------------------------------------------------

class Robocop : public Humanic {

public : 
static int total;
Robocop();
Robocop(World* world, int x, int y, int strngth, int hp);
int getType();
int getDamage();
};

int Robocop::total = 0;

Robocop::Robocop() : Humanic() {
    name = "robocop_" + to_string(total);
    total++;
    TOTAL_ROBOT++; // UPDATE TOTAL NUMBER OF ROBOTS
}

Robocop::Robocop(World* world, int x, int y, int strngth, int hp) : Humanic(world, x, y) {
    strength = strngth;
    hitpoint = hp;
    name = "robocop_" + to_string(total);
    total++;
    TOTAL_ROBOT++; // UPDATE TOTAL NUMBER OF ROBOTS
}

int Robocop::getType() {
    return ROBOCOP; // RETURNS TYPE
}

int Robocop::getDamage() {

    int damage = Humanic::getDamage(); // RETURNS DAMAGE
    
    return damage;
}

int* Robot::move() {

bool winner;
int* coordinates = new int(2);

while(1) {

if ((y>0) && (world->getAt(x,y-1)!=NULL)) { // CHECK LEFT CELL IF IT'S AVAILABLE TO MOVE IN
winner = fight(*(world->grid[x][y-1]));

if(winner) {
TOTAL_ROBOT--;
delete (world->grid[x][y-1]);
world->grid[x][y-1] = this; // Move to spot
world->setAt(x,y,NULL);
y--;

if(hitpoint <= 0) { // IF ROBOT DIES ITSELF AFTER BATTLE (FOR KAMIKAZE)
coordinates[0] = x;
coordinates[1] = y;
return coordinates;
}

return NULL;
}
else {
    if(world->grid[x][y-1]->hitpoint <= 0) { // FOR KAMIKAZE
        TOTAL_ROBOT--;
        delete (world->grid[x][y-1]);
        world->setAt(x,y-1,NULL);
    }
    coordinates[0] = x;
    coordinates[1] = y;
    return coordinates;
}

}

else if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)!=NULL))  { // CHECK RIGHT CELL IF IT'S AVAILABLE TO MOVE IN
winner = fight(*(world->grid[x][y+1]));

if(winner) {
TOTAL_ROBOT--;
delete (world->grid[x][y+1]);
world->grid[x][y+1] = this; // Move to spot
world->setAt(x,y,NULL);
y++;

if(hitpoint <= 0) { // IF ROBOT DIES ITSELF AFTER BATTLE (FOR KAMIKAZE)
coordinates[0] = x;
coordinates[1] = y;
return coordinates;
}

return NULL;
}
else {

    if(world->grid[x][y+1]->hitpoint <= 0) { // FOR KAMIKAZE
    TOTAL_ROBOT--;    
    delete (world->grid[x][y+1]);
    world->setAt(x,y+1,NULL);
    }
    coordinates[0] = x;
    coordinates[1] = y;
    return coordinates;
}

}


else if ((x>0) && (world->getAt(x-1,y)!=NULL)) { // CHECK UPPER CELL IF IT'S AVAILABLE TO MOVE IN
winner = fight(*(world->grid[x-1][y]));

if(winner) {
TOTAL_ROBOT--;
delete (world->grid[x-1][y]);
world->grid[x-1][y] = this; // Move to spot
world->setAt(x,y,NULL);
x--;

if(hitpoint <= 0) { // IF ROBOT DIES ITSELF AFTER BATTLE (FOR KAMIKAZE)
coordinates[0] = x;
coordinates[1] = y;
return coordinates;
}

return NULL;
}
else {

    if(world->grid[x-1][y]->hitpoint <= 0) { // FOR KAMIKAZE
    TOTAL_ROBOT--;
    delete (world->grid[x-1][y]);
    world->setAt(x-1,y,NULL);
    }
    coordinates[0] = x;
    coordinates[1] = y;
    return coordinates;
}
}

else if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)!=NULL)) { // CHECK DOWN CELL IF IT'S AVAILABLE TO MOVE IN
winner = fight(*(world->grid[x+1][y]));

if(winner) {
TOTAL_ROBOT--;
delete (world->grid[x+1][y]);
world->grid[x+1][y] = this; // Move to spot
world->setAt(x,y,NULL);
x++;

if(hitpoint <= 0) { // IF ROBOT DIES ITSELF AFTER BATTLE (FOR KAMIKAZE)
coordinates[0] = x;
coordinates[1] = y;
return coordinates;
}

return NULL;
}
else {

    if(world->grid[x+1][y]->hitpoint <= 0) { // FOR KAMIKAZE
    TOTAL_ROBOT--;
    delete (world->grid[x+1][y]);
    world->setAt(x+1,y,NULL);
    }
    coordinates[0] = x;
    coordinates[1] = y;
    return coordinates;
}
}

// If we got here, then we didn't find enemy. Move
// to a random spot.
bool randomMoved = false;

while(!randomMoved) {
int dir = rand() % 4;

if (dir==0) {
    if ((y>0) && (world->getAt(x,y-1)==NULL)) {
        world->setAt(x,y-1,world->getAt(x,y)); // Move to new spot
        world->setAt(x,y,NULL); // Set current spot to empty
        y--; // UPDATE COORDINATES
        randomMoved = true; // SET AS RANDOM MOVED
    }
}

else if (dir==1) {
    if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL)) {
        world->setAt(x,y+1,world->getAt(x,y)); // Move to new spot
        world->setAt(x,y,NULL); // Set current spot to empty
        y++;
        randomMoved = true;
}
}

else if (dir==2) {
    if ((x>0) && (world->getAt(x-1,y)==NULL)) {
        world->setAt(x-1,y,world->getAt(x,y)); // Move to new spot
        world->setAt(x,y,NULL); // Set current spot to empty
        x--;
        randomMoved = true;
    }
}

else if (dir==3) {
    if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL)) {
        world->setAt(x+1,y,world->getAt(x,y)); // Move to new spot
        world->setAt(x,y,NULL); // Set current spot to empty
        x++;
        randomMoved = true;
    }
}

}
}

}


void World::Simulate() {

int x,y; // VARIABLES TO STORE COORDINATES IN ORDER TO DELETE OUT OF MOVE FUNCTION
int *moveResult;

while(TOTAL_ROBOT > 1) {

// First reset all robots to not moved
for (int i=0; i<WORLDSIZE; i++) {
    for (int j=0; j<WORLDSIZE; j++) {
        if (grid[i][j]!=NULL) grid[i][j]->moved = false;
    }
}

// Loop through cells in order
for (int i=0; i<WORLDSIZE; i++) {
    for (int j=0; j<WORLDSIZE; j++) {
        if (grid[i][j]!=NULL) {
            if (grid[i][j]->moved == false) {
                
                grid[i][j]->moved = true; // Mark as moved
                if(TOTAL_ROBOT > 1) { 
                moveResult = grid[i][j]->move();
                if(moveResult != NULL ) {
                x=moveResult[0];
                y=moveResult[1];
                delete grid[x][y];
                TOTAL_ROBOT--;
                grid[x][y]=NULL;
                delete moveResult;
                }
                
                }
            }
            
        }
    } 
}

}
}

// ------------------------------------------------------------------------------------------

int main() {

srand(time(NULL));

World w;

//INITALIZING ALL KINDS OF ROBOTS

int c = 0;
while (c < INITIAL_ROBOT_NUMBER) {
int x = rand() % WORLDSIZE;   //             INITALIZING KAMIKAZE ROBOTS
int y = rand() % WORLDSIZE;
if (w.getAt(x,y)==NULL) {
c++;
Kamikaze *k = new Kamikaze(&w,x,y,10,10);
}
}

int c1 = 0;
while (c1 < INITIAL_ROBOT_NUMBER) {
int x = rand() % WORLDSIZE;
int y = rand() % WORLDSIZE;  //             INITALIZING BULLDOZER ROBOTS
if (w.getAt(x,y)==NULL) {
c1++;
Bulldozer *k = new Bulldozer(&w,x,y,50,200);
}
}

int c2 = 0;
while (c2 < INITIAL_ROBOT_NUMBER) {
int x = rand() % WORLDSIZE;
int y = rand() % WORLDSIZE; //             INITALIZING ROOMBA ROBOTS
if (w.getAt(x,y)==NULL) {
c2++;
Roomba *k = new Roomba(&w,x,y,3,10);
}
}

int c3 = 0;
while (c3 < INITIAL_ROBOT_NUMBER) {
int x = rand() % WORLDSIZE; //             INITALIZING OPTIMUSPRIME ROBOTS
int y = rand() % WORLDSIZE;
if (w.getAt(x,y)==NULL) {
c3++;
Optimusprime *k = new Optimusprime(&w,x,y,100,100);
}
}

int c4 = 0;
while (c4 < INITIAL_ROBOT_NUMBER) {
int x = rand() % WORLDSIZE; //             INITALIZING ROBOCOP ROBOTS
int y = rand() % WORLDSIZE;
if (w.getAt(x,y)==NULL) {
c4++;
Robocop *k = new Robocop(&w,x,y,30,40);
}
}


w.Simulate(); // SIMULATE THE GAME

    return 0;
}