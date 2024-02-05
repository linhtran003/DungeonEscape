// CSCI 1300 Fall 2022
// Author: Linh Tran
// Recitation: 206 - Baljot Kaur
// Project 3 - dungeonEscapeDriver

#include <iostream>
#include <fstream>
#include "DungeonEscape.h"
#include "Map.h"
using namespace std;

void randomizeMap(Map map);

int main()
{
    srand(time(NULL));

    // creating new map object
    Map map = Map();
    int random_row = -1;
    int random_column = -1;
    bool free = false;
    int explored_spaces = 0;
    int turns = 0;

    // add 5 rooms in random locations
    for (int i = 0; i < 5; i++)
    {
        random_row = rand() % 12;
        random_column = rand() % 12;

        free = map.isFreeSpace(random_row, random_column);

        // add to free space in the map
        if (free == true)
        {
            map.addRoom(random_row, random_column);
        }
        else
        {
            while (free == false)
            {
                random_row = rand() % 12;
                random_column = rand() % 12;
                free = map.isFreeSpace(random_row, random_column);
            }
            map.addRoom(random_row, random_column);
        }
    }

    // add 5 NPCs in random locations
    for (int i = 0; i < 5; i++)
    {
        random_row = rand() % 12;
        random_column = rand() % 12;

        free = map.isFreeSpace(random_row, random_column);

        // add to free space in the map
        if (free == true)
        {
            map.addNPC(random_row, random_column);
        }
        else
        {
            while (free == false)
            {
                random_row = rand() % 12;
                random_column = rand() % 12;
                free = map.isFreeSpace(random_row, random_column);
            }
            map.addNPC(random_row, random_column);
        }
    }

    map.displayMap();

    cout << "Welcome to Dungeon Escape!" << endl;
    cout << "To get started, let's get the names of all 5 party members." << endl;
    cout << "Please enter your name: " << endl;
    cout << endl;

    string player_name = "";
    cin >> player_name;

    cout << "Please enter party member #2's name: " << endl;
    cout << endl;
    string p2;
    cin >> p2;

    cout << "Please enter party member #3's name: " << endl;
    cout << endl;
    string p3;
    cin >> p3;

    cout << "Please enter party member #4's name: " << endl;
    cout << endl;
    string p4;
    cin >> p4;

    cout << "Please enter party member #5's name: " << endl;
    cout << endl;
    string p5;
    cin >> p5;

    DungeonEscape dun = DungeonEscape(player_name, p2, p3, p4, p5);

    cout << "Between the 5 of you, you have 100 gold pieces. " << endl;
    cout << "You will need to spend the some of your money on the following items:" << endl;
    cout << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl;
    cout << "- COOKWARE. If you want to cook, you have to have cookware first." << endl;
    cout << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    cout << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl;
    cout << endl;
    cout << "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way." << endl;
    cout << "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;
    cout << endl;

    dun.merchant();

    int gameGoing = -1;
    bool giveUp = false;

    while (gameGoing == -1)
    {
        int option = 0;
        dun.statusUpdate();
        map.displayMap();

        cout << "Choose a direction to move using w, a, s, d. " << endl;
        char dir;
        cin >> dir;

        // checking for valid direction
        while (!(dir == 'w' || dir == 'a' || dir == 's' || dir == 'd'))
        {
            cout << "Invalid direction. Please try again." << endl;
            cin >> dir;
        }

        map.move(dir); // party moves in that direction

        dun.move();

        int player_row = map.getPlayerRow();
        int player_col = map.getPlayerCol();

        // ROOM ACTIONS
        if (map.isRoomLocation(player_row, player_col) == true)
        {
            dun.addSorcererAnger(1); // adding 1 to sorcerer anger

            dun.displayRoomMenu();
            cin >> option;

            while (option < 1 || option > 3)
            {
                cout << "Invalid input. Enter option again." << endl;
                dun.displayRoomMenu();
                cin >> option;
            } 

            bool defeated_room_monster;

            switch(option)
            {
                case 1:
                    dun.move();
                    break;
                case 2:
                    defeated_room_monster = dun.openDoor();
                    // if the room is cleared
                    if (defeated_room_monster == true)
                    {
                        map.removeRoom(player_row, player_col); // removing room if monster defeated
                        dun.addRoomsCleared();
                    }
                    explored_spaces++;
                    break;
                case 3:
                    giveUp = true;
                    gameGoing = -2;
                    break;
            }
        }

        // NPC ACTIONS
        else if (map.isNPCLocation(player_row, player_col) == true)
        {
            dun.addSorcererAnger(1);

            cout << "A stranger is approaching you." << endl;
            dun.displayNPCMenu();
            cin >> option;

            while (option < 1 || option > 3)
            {
                cout << "Invalid input. Enter option again." << endl;
                dun.displayRoomMenu();
                cin >> option;
            } 

            switch(option)
            {
                case 1:
                    dun.move();
                    break;
                case 2:
                    dun.speakToNPC();
                    map.removeNPC(player_row, player_col);
                    map.exploreSpace(player_row, player_col);
                    explored_spaces++;
                    break;
                case 3:
                    giveUp = true;
                    gameGoing = -2;
                    break;
            }
        }

        // NORMAL SPACE ACTIONS
        else if (map.isNPCLocation(player_row, player_col) == false && map.isRoomLocation(player_row, player_col) == false && map.isDungeonExit(player_row, player_col) == false)
        {
            if (map.isExplored(player_row, player_col) == false)
            {
                dun.addSorcererAnger(1);
            }

            dun.displayNormalMenu();
            cin >> option;

            while (option < 1 || option > 5)
            {
                cout << "Invalid input. Enter option again." << endl;
                dun.displayRoomMenu();
                cin >> option;
            }

            switch(option)
            {
                case 1:
                    dun.move();
                    break;
                case 2:
                    if (map.isExplored(player_row, player_col) == true)
                    {
                        cout << "This space has already been explored." << endl;
                        break;
                    }
                    dun.investigate();
                    map.exploreSpace(player_row, player_col);
                    explored_spaces++;
                    break;
                case 3:
                    dun.fightMonster();
                    break;
                case 4:
                    dun.cook();
                    break;
                case 5:
                    giveUp = true;
                    gameGoing = -2;
                    break;
            }
        }

        else if (map.isDungeonExit(player_row, player_col) == true)
        {
            if (dun.getRoomsCleared() == 5)
            {
                cout << "CONGRATULATIONS! YOU'VE ESCAPED THE DUNGEON!" << endl;
                gameGoing = 3;
            }
            else if (dun.getRoomsCleared() < 5)
            {
                cout << "You have not cleared all of the rooms! Get back out there!" << endl;
            }
        }

        dun.checkFullness(); // check to see if there are hungry members or if any players hit 0 fullness

        // checking to see if the player has lost
        if (gameGoing != -2) // if the player still has not given up
        {
            gameGoing = dun.gameOver();
        }

        turns++; // incrementing number of turns at the end of while loop
    }

    if (giveUp == true)
    {
        cout << "You've given up! Sorry you and your party were unable to make it out of the dungeon." << endl;
        cout << endl;
    }

    if (gameGoing == 1)
    {
        cout << "Looks like you've lost all your party members. Game over!" << endl;
        cout << "Thanks for playing!" << endl;
        cout << endl;
    }
    else if (gameGoing == 2)
    {
        cout << "The sorcerer's anger level has reached 100! The sorcerer cast a spell to destroy the whole dungeon." << endl;
        cout << "You and your party members have failed. Game over!" << endl;
        cout << "Thanks for playing!" << endl;
        cout << endl;
    }

    dun.printStats();
    ifstream fin("stats.txt");

    if (fin.is_open())
    {
        std::cout << fin.rdbuf(); // reading and printing stats.txt file
    }
    cout << "Number of spaces explored: " << explored_spaces << endl;
    cout << "Number of turns elapsed: " << turns << endl;

    return 0;
}