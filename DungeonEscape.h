#include <iostream>
#include "Monster.h"
#include "Character.h"
#include "Inventory.h"
#include <vector>
using namespace std;

class DungeonEscape
{
    public:
    // constructors
    DungeonEscape();
    DungeonEscape(string name1, string name2, string name3, string name4, string name5);

    // displays/prints
    void displayNormalMenu();
    void displayNPCMenu();
    void displayRoomMenu();
    void statusUpdate();
    void printPartyMembers(); // a function for game development testing
    void printInventory(); // prints the party's current inventory
    void printMerchantOptions();
    void printWeapons();
    void printStats();

    // normal actions
    void move();
    void investigate();
    void merchant();
    bool fightMonster(); // party fights monster, returns true if monster defeated, false else

    // NPC actions
    void speakToNPC();
    void readPuzzles();
    bool NPCPuzzle(); // returns true if player successfully answers riddle, returns false if player fails

    // room actions
    bool openDoor();
    bool doorPuzzle(); // returns true if the player successfully beats door, false otherwise
    void removeMember(string name); // removes a member from the party
    void addRoomsCleared();
    int getRoomsCleared();
    
    // other
    void cook();
    bool checkPrice(int price);
    void misfortune(bool openingDoor);

    // functions that have been used to test code

    // functions related to monsters
    void readMonsters(string file_name); // reads a text file of monsters and stores in data member vectors
    int getSorcererAnger(); // returns the sorcerer's current anger level
    void addSorcererAnger(int anger); // adds to the sorcerer's anger
    int randomMonster(int rooms_cleared); // generates a random number for the party to fight random monster
    void defeatMonster(int level, string name); // removes the monster from its vector and adds to defeated vector
    void readMonsters();
    
    void checkFullness(); // checks the fullness of each player, removes a player if they hit fullness 0
    int gameOver(); // determines whether the game is over and the player lost

    private:
    Inventory inv_; // a collective inventory for this game of dungeon escape
    vector<Character> party_; // a vector of Character objects to act as the party
    int anger_; // the sorcerer's anger level
    int size_; // how many characters in the party
    int roomsCleared_; // number of rooms that the party has cleared

    // monsters
    vector<Monster> monster_1; // a vector of Level 1 Monster objects
    vector<Monster> monster_2; // a vector of Level 2 Monster objects
    vector<Monster> monster_3; // a vector of Level 3 Monster objects
    vector<Monster> monster_4; // a vector of Level 4 Monster objects
    vector<Monster> monster_5; // a vector of Level 5 Monster objects
    Monster sorcerer_; // the sorcerer
    vector<Monster> defeated_monsters; // a vector that stores all defeated monsters
    vector<Monster> monster_vects[5]; // an array that stores all of the monster vectors

    // riddles
    string riddles_ [20]; // array of riddles
    string answers_ [20]; // corresponding riddle answers
};