#include <iostream>
#include "DungeonEscape.h"
#include <vector>
#include <fstream>
using namespace std;

int rollDice();
int split (string input_string, char separator, string arr [], int arr_size);

// default constructor
DungeonEscape::DungeonEscape()
{
    inv_ = Inventory();

    // creating a new party of characters
    for (int i = 0; i < 5; i++)
    {
        Character c = Character();
        party_.push_back(c);
    }
    party_[0].setPlayer(true);

    size_ = 5;
    roomsCleared_ = 0;
    anger_ = 0;

    readMonsters("monsters.txt");
    readPuzzles();
    
}

// parameterized constructor
DungeonEscape::DungeonEscape(string name1, string name2, string name3, string name4, string name5)
{
    inv_ = Inventory();

    // creating a new party of characters
    for (int i = 0; i < 5; i++)
    {
        Character c = Character();
        party_.push_back(c);
    }
    party_[0].setPlayer(true);

    party_[0].setName(name1);
    party_[1].setName(name2);
    party_[2].setName(name3);
    party_[3].setName(name4);
    party_[4].setName(name5);

    size_ = 5;
    roomsCleared_ = 0;
    anger_ = 0;

    readMonsters("monsters.txt");
    readPuzzles();
}

/*
    Algorithm: prints out the status update for each turn in Dungeon Escape
    1. Prints rooms cleared
    2. Prints keys in inventory
    3. Prints sorcerer anger
    4. Prints inventory
    5. Prints party members and their fullness
*/
void DungeonEscape::statusUpdate()
{
    cout << "+-------------+" << endl;
    cout << "| STATUS      |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Rooms Cleared: " << roomsCleared_ << " | Keys: " << inv_.getKeys() << " | Anger Level: " << anger_ << endl;
    printInventory();
    cout << "+-------------+" << endl;
    printPartyMembers();
    cout << endl;
    return;
}

/*
    Algorithm: prints out the menu for a normal action space
    1. Prints out all options for the player on a normal action space: move, investigate, pick a fight, cook and eat, give up
*/
void DungeonEscape::displayNormalMenu()
{
    cout << "  Select one:" << endl;
    cout << "  1. Move" << endl;
    cout << "  2. Investigate" << endl;
    cout << "  3. Pick a Fight" << endl;
    cout << "  4. Cook and Eat" << endl;
    cout << "  5. Give up" << endl;
    cout << endl;
}

/*
    Algorithm: prints out the menu for a NPC space
    1. Prints out all options for the player on a NPC space: move, speak to NPC, give up
*/
void DungeonEscape::displayNPCMenu()
{
    cout << "  Select one:" << endl;
    cout << "  1. Move" << endl;
    cout << "  2. Speak to NPC" << endl;
    cout << "  3. Give up" << endl;
    cout << endl;
}

/*
    Algorithm: prints out the menu for a room space
    1. Prints out all options for the player on a room space: move, open the door, give up
*/
void DungeonEscape::displayRoomMenu()
{
    cout << "  Select one:" << endl;
    cout << "  1. Move" << endl;
    cout << "  2. Open the door" << endl;
    cout << "  3. Give up" << endl;
    cout << endl;
}

/*
    Algorithm: calculates the 20% chance of a party member's fullness dropping by 1
    For each party member:
    1. call rollDice() function
    2. if function returns a value between 1 and 20, subtract 1 fullness from that party member
*/
void DungeonEscape::move()
{
    // 20% chance of party member's fullness dropping by 1
    for (int i = 0; i < size_; i++)
    {
        int full_chance = rollDice();
        if (full_chance >= 1 && full_chance <= 20)
        {
            party_[i].subFullness(1); // take away one fullness point from that party member
        }
    }
    return;
}

/*
    Algorithm: the events that occur when the player chooses to investigate a normal space
    1. call rollDice() function
    2. If the function returns number between 1 and 10 (10% chance):
        Print that the party found a key
        Add key to inventory
    3. If the function returns number between 11 and 30 (20% chance):
        If the rooms cleared is 0, add a ring to inventory, print message to console
        If the rooms cleared is 1, add a ring to inventory, print message to console
        If the rooms cleared is 2, add a necklace to inventory, print message to console
        If the rooms cleared is 3, add a bracelet to inventory, print message to console
        If the rooms cleared is 4, add a circlet to inventory, print message to console
        If the rooms cleared is 5, add a goblet to inventory, print message to console
    4. If the function returns number between 31 and 50 (20% chance):
        The party fights a monster (call fightMonster() function)
    5. Regardless of whether the party found key/treasure, each party member has 50% chance of dropping one fullness point
*/
void DungeonEscape::investigate()
{
    int result = rollDice();

    if (result >=1 && result <= 10)
    {
        cout << "You've found a key! Well done." << endl;
        inv_.addKeys(1);
    }
    else if (result >= 11 && result <= 30)
    {
        int rooms = roomsCleared_;
        switch (rooms)
        {
            case 0: 
                inv_.addRings(1);
                cout << "You've found a silver ring!" << endl;
                break;
            case 1:
                inv_.addRings(1);
                cout << "You've found a silver ring!" << endl;
                break;
            case 2:
                inv_.addNecklaces(1);
                cout << "You've found a ruby necklace!" << endl;
                break;
            case 3:
                inv_.addBracelets(1);
                cout << "You've found an emerald bracelet!" << endl;
                break;
            case 4:
                inv_.addCirclets(1);
                cout << "You've found a diamond circlet!" << endl;
                break;
            case 5:
                inv_.addGoblets(1);
                cout << "You've found a gem-encrusted goblet!" << endl;
                break;
            default:
                break;
        }
    }
    else if (result >= 31 && result <= 50)
    {
        cout << "Oh no! You've encountered a monster!" << endl;
        cout << endl;
        fightMonster();
        return;
    }
    else 
    {
        cout << "No keys or treasures were found. Better luck next time!" << endl;

        // if the party fought a monster, don't apply the 50% hunger decrease again
        if (result >= 31 && result <= 50)
        {
            return;
        }
    }

    // regardless of whether the party found key/treasure, each party member has 50% chance of dropping one fullness point
            
    for (int i = 0; i < size_; i++)
    {
        int result2 = rollDice();
        if (result2 >= 1 && result2 <= 50)
        {
            cout << "Unfortunately, " << party_[i].getName() << " has lost one fullness point." << endl;
            party_[i].subFullness(1); // take away one fullness point
            cout << party_[i].getName() << "'s current fullness: " << party_[i].getFullness() << endl;
        }
    }
    return;
}

/*
    Algorithm: the events that occur when the player chooses to open the door on a room space and return whether the party defeat the
    room or not
    1. call rollDice() function
    
    If the party has a key in inventory:
        2. Print that a key has been used
        3. Remove key from inventory
        4. Have the party fight a monster
        If the party didn't defeat the monster:
            Print that the monster wasn't defeated
            If the dice roll is between 1 and 40 (40% chance), call misfortune(false) and return false
        If the party defeated the monster:
            Print message giving congrats for beating the room
            If the dice roll is between 1 and 60 (60% chance), call misfortune(false) and return true
    If the Pary doesn't have a key in inventory:
        2. Have the party complete the door puzzle
        If the party beat the door:
            3. Have the party fight a monster
            If the party didn't defeat the monster:
                4. Print that the monster wasn't defeated
                5. If the dice roll is between 1 and 40 (40% chance), call misfortune(false) and return false
            If the party defeated the monster:
                4. Print message giving congrats for beating the room
                5. If the dice roll is between 1 and 60 (60% chance), call misfortune(false) and return true
        If the party didn't beat the door:
            3. The party loses 1 member at random (not the main player)
*/
bool DungeonEscape::openDoor()
{
    int dice = rollDice();
    if (inv_.getKeys() > 0)
    {
        cout << "You've now used one key to open the door." << endl;
        inv_.addKeys(-1); // removing a key from inventory
        bool result = false;

        result = fightMonster(); // whether the party won or lost against the monster

        if (result == false)
        {
            cout << "Looks like you were unable to defeat the monster." << endl;
            cout << "Better luck next time!" << endl;

            if (dice <= 40)
            {
                misfortune(false);
                return false;
            }
        }
        else
        {
            cout << "Well done on defeating the room!" << endl;
            
            if (dice <= 60)
            {
                misfortune(false);
                return true;
            }
        }
    }
    else
    {
        bool result2 = doorPuzzle();
        if (result2 == true)
        {
            bool result3 = fightMonster();
            if (result3 == false)
            {
                cout << "Looks like you were unable to defeat the monster." << endl;
                cout << "Better luck next time!" << endl;

                if (dice <= 40)
                {
                    misfortune(true);
                    return false;
                }
            }
            else
            {
                cout << "Well done on defeating the room!" << endl;
            
                if (dice <= 60)
                {
                    misfortune(true);
                    return true;
                }
            }
        }
        else
        {
            cout << "You've lost all three attempts." << endl;
            cout << "Unfortunately, you lose one party member." << endl;

            int bounds = size_ - 1; // bounds are excluding the player
            int rand_member = rand() % bounds + 1; // random number between 1 and number of other party members
            string mem = party_[rand_member].getName();

            removeMember(mem);

            cout << mem << "has died." << endl;
            cout << endl;
            return false;
        }
    }
    return false;
}

/*
    Algorithm: the events that occur when the player chooses to speak to NPC on a NPC space
    1. Have the player answer a riddle (call NPCPuzzle() function)
    If the player answers correctly:
        2. Ask if player wants to buy items from NPC
        If the player says yes:
            3. call merchant() function
        If the player says no:
            3. NPC says bye
    If the player answers incorrectly:
        2. Print that the NPC is summoning a monster
        3. call fightMonster() function
*/
void DungeonEscape::speakToNPC()
{
    bool result = NPCPuzzle();
    string input1 = "";
    if (result == true)
    {
        cout << "Well done! You have solved my riddle." << endl;
        cout << "Would you like to buy some items from me? (y/n)" << endl;
        cout << "If you say no, I we both shall be on our ways." << endl;
        cout << endl;
        cin >> input1;

        if (input1 == "y")
        {
            merchant();
            return;
        }
        else
        {
            cout << "Alright. Farewell then! Safe travels." << endl;
            cout << endl;
            return;
        }
    }
    else
    {
        cout << "Incorrect! I'm summoning a monster now. You'll never escape!" << endl;
        cout << endl;
        fightMonster();
        return;
    }
    return;
}

/*
    Algorithm: reads riddles from a text file and stores all riddles in one vector and all the corresponding answers in another vector
    1. Open the file "riddles.txt"
    While the file is open:
        2. Get the current line on the file
        3. Call split() function to split riddles into riddles and answers
        4. Add riddles to riddles_ vector
        5. Add answers to answers_ vector
    6. Close the text file
*/
void DungeonEscape::readPuzzles()
{
    ifstream file_input;
    string line = ""; // holding the current line being read
    string arr [2];
    int split_result;
    int counter = 0;

    // open the file
    file_input.open("riddles.txt");

    if (file_input.is_open()) 
    {
        // while the file is open
        while (!file_input.eof())
        {
            // gets line of text from file_input, stores it in line
            getline(file_input, line);

            // split line into array of size 2
            split_result = split(line, '~', arr, 2);

            // if the split function successfully splits the line into four parts
            if (split_result == 2)
            {
                riddles_[counter] = arr[0];
                answers_[counter] = arr[1];
                counter++;
            }
        }
        file_input.close();
    }
}


/*
    Algorithm: Asks player a riddle if they choose to speak to NPC on NPC space
    1. Open the file "riddles.txt"
    While the file is open:
        2. Get the current line on the file
        3. Call split() function to split riddles into riddles and answers
        4. Add riddles to riddles_ vector
        5. Add answers to answers_ vector
    6. Close the text file
*/
bool DungeonEscape::NPCPuzzle()
{
    string guess = "";
    int rand_riddle = rand() % 20;
    string riddle = riddles_[rand_riddle];
    string answer = answers_[rand_riddle];

    cout << "Hello there traveler!" << endl;
    cout << "I will sell you some objects if you are able to successfully answer this riddle." << endl;
    cout << "However, if you answer incorrectly... you may face danger." << endl;
    cout << endl;
    cout << riddle << endl;
    cin >> guess;

    if (guess == answer)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    Algorithm: Function is called when player attempts to open door without key - prompted to play Boulder/Parchment/Shears
    Returns true if the player beat the door within 3 attempts
    Returns false if the player didn't beat the door within attempts
    1. Prompt player to choose boulder, parchment, or shears
    2. If the option is invalid, repeatedly ask for valid input
    3. Generate random number between 1 and 3 - 1 is boulder, 2 is parchment, 3 is shears
    If:
        player chooses boulder and computer chooses shears
        player chooses parchment and computer chooses boulder
        player chooses shears and computer chooses parchment
    4. Player wins, return true
    Otherwise: player has 3 total attempts to try to beat door
    If player loses all 3 attempts:
        4. Player loses, return false
*/
bool DungeonEscape::doorPuzzle()
{
    bool win = false;
    int option = 0;
    int r = 0;
    int tries = 3;

    cout << "You have attempted to open this door without a key." << endl;
    cout << "In order to enter, you must beat the door in three attempts of Boulder/Parchment/Shears. " << endl;
    cout << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "Select an object: " << endl;
        cout << " 1. Boulder" << endl;
        cout << " 2. Parchment" << endl;
        cout << " 3. Shears" << endl;
        cout << endl;

        cin >> option;

        while (option < 1 || option > 3)
        {
            cout << "Invalid input. Please enter number between 1 and 3." << endl;
            cout << "Select an object: " << endl;
            cout << " 1. Boulder" << endl;
            cout << " 2. Parchment" << endl;
            cout << " 3. Shears" << endl;
            cout << endl;

            cin >> option;
        }

        r = rand() % 3 + 1;

        if (option == 1 && r == 3)
        {
            win = true;
            cout << "The door has selected shears. You win!" << endl;
            cout << "You have entered the room." << endl;
            cout << endl;
            break;
        }
        else if (option == 2 && r == 1)
        {
            win = true;
            cout << "The door has selected boulder. You win!" << endl;
            cout << "You have entered the room." << endl;
            cout << endl;
            break;
        }
        else if (option == 3 && r == 2)
        {
            win = true;
            cout << "The door has selected parchment. You win!" << endl;
            cout << "You have entered the room." << endl;
            cout << endl;
            break;
        }
        else
        {
            cout << "The door has selected parchment. You lose!" << endl;
            tries--;
            cout << "You have " << tries << " attempt(s) left to try to beat the door." << endl;
            cout << endl;
        }
    }

    return win;
}


/*
    Algorithm: Function is called when player attempts to open door without key - prompted to play Boulder/Parchment/Shears
    Returns true if the party defeated the monster
    Returns false if the player didn't defeat the monster
    1. Prompt the player to either attack or surrender
    If player attacks:
        2. Set the level of the monster to be number of rooms cleared + 1
        3. If the party is on the final room, set the level of the monster to 6
        4. Calculate the probability of party winning based on weapons, variety of weapons, armor, and monster level
        If the party won the battle
            5. Add 10 * difficulty of monster gold coins to inventory
            6. Add 5 * difficulty of monster kg of ingredients to inventory
            7. 10% chance that the monster dropped a key - if so, add key to inventory
            8. Print message to console explaining addition of gold, food, and possibly a key
            9. call the defeatMonster() function
            10. Return true
        If the party lost the battle
            5. Party loses 1/4 of their gold
            6. Party loses up to 30 kg of their ingredients
            7. Each party member (excluding player) has 5% chance of dying if they have armor, 10% chance if they don't
            If par7y member dies:
                8. call removeMember() function
            8. Print out the party's losses or member deaths
            9. Each player has 50% chance of losing 1 fullness point
            10. Return false
    If player surrenders:
        2. Remove random party member (excluding player) by calling removeMember() function
        3. Notify player of their loss
        4. Return false
*/
bool DungeonEscape::fightMonster()
{
    bool defeated = false;

    cout << "Choose an action: " << endl;
    cout << "1. Attack - one player must have a weapon" << endl;
    cout << "2. Surrender - you will lose one party member" << endl;

    int option;
    cin >> option;

    // checking for a valid input
    while (!(option == 1 || option == 2))
    {
        cout << "Invalid input" << endl;
        cout << "Choose an action: " << endl;
        cout << "1. Attack - one player must have a weapon" << endl;
        cout << "2. Surrender - you will lose one party member" << endl;
    
        cin >> option;
    }

    if (option == 1)
    {
        int c = 0;
        int rand_monster = 0;
        Monster mon;

        if (roomsCleared_ == 5)
        {
            cout << "You've reached the final monster - the sorcerer!" << endl;
            cout << endl;
            c = 6;
            rand_monster = 0;
            mon = sorcerer_;
        }
        else
        {
            rand_monster = randomMonster(roomsCleared_); // random index in the vector
            c = roomsCleared_ + 1; // level of the monster
            mon = monster_vects[roomsCleared_][rand_monster]; // the monster that the players will fight
            cout << mon.getName() << " ahead! It looks ferocious!" << endl;
            cout << endl;
        }

        int w = inv_.getTotalWeapons() + inv_.getRapiers() + 2 * inv_.getAxes() + 3 * inv_.getLongswords();

        int d;
        if (inv_.getAxes() == 1 && inv_.getClubs() == 1 && inv_.getLongswords() == 1 && inv_.getRapiers() == 1 && inv_.getSpears() == 1)
        {
            d = 4;
        }
        else 
        {
            d = 0;
        }

        int a = inv_.getArmor();

        if (a == 0) // just to avoid dividing by 0 in the later calculation
        {
            a = 1;
        }

        int r1 = rand() % 6 + 1;
        int r2 = rand() % 6 + 1;

        double fight_result = (r1 * w + d) - ((r2 * c) / a);

        // if the party won the battle
        if (fight_result > 0)
        {
            defeated = true;
            // add gold to inventory
            int won_gold = 10 * c;
            inv_.addGold(won_gold);

            // add food to inventory
            int ing = 5 * c;
            inv_.addFood(ing);

            // there is a 10% chance that the monster dropped a key
            int dice = rollDice();
            if (dice <= 10)
            {
                cout << "Congrats! You have defeated the " << mon.getName() << "! The monster has dropped gold, food, and a key!" << endl;
                inv_.addKeys(1);
            }
            else
            {
                cout << "Congrats! You have defeated the " << mon.getName() << "! The monster has dropped gold and food." << endl;
            }

            if (roomsCleared_ == 5)
            {
                sorcerer_.setStatus(false); // setting the sorcerer's status to dead
            }
            else
            {
                defeatMonster(c, mon.getName()); // call the defeatMonster function
            }
        }
        // if the party lost the battle
        else
        {
            defeated = false;
            // party loses a quarter of their gold
            int quarter_gold = (int)(.25 * inv_.getGold());
            inv_.subGold(quarter_gold);
            
            // party loses up to 30 kg of ingredients
            int rand_ingredients = rand() % 31;
            inv_.subFood(rand_ingredients);

            // each party member (excluding player) has chance of death
            vector<string> death;
            bool dies = false;
            for (int i = 1; i < size_; i++)
            {
                int dice2 = rollDice();

                // if the party member has armor, they have 5% chance of death
                if (party_[i].getArmor() == true)
                {
                    if (dice2 <= 5)
                    {
                        dies = true;
                        death.push_back(party_[i].getName());
                    }
                }
                // if the party member doesn't have armor, they have 10% chance of death
                else
                {
                    if (dice2 <= 10)
                    {
                        dies = true;
                        death.push_back(party_[i].getName());
                    }
                }
            }
            
            // if there was at least 1 party member that died
            if (dies == true)
            {
                // print out the party's loss
                cout << "Unfortunately, your party has lost the battle against the monster." << endl;
                cout << "You have lost a quarter of your gold supply and " << rand_ingredients << " kg of your ingredients." << endl;
                cout << "These players have also been slain by the monster: " << endl;

                int s = death.size();
                for (int i = 0; i < s; i++)
                {
                    cout << death[i] << endl;
                    removeMember(death[i]);
                }
            }
            // if no party members died
            else
            {
                cout << "Unfortunately, your party has lost the battle against the monster." << endl;
                cout << "You have lost a quarter of your gold supply and " << rand_ingredients << " kg of your ingredients." << endl;
            }
        }

        // with any outcome of battle, each member's fullness level has 50% chance to drop 1 point
        vector<string> full;
        bool lost_full = false;
        for (int i = 0; i < size_; i++)
        {
            int full_chance = rollDice();
            if (full_chance >= 1 && full_chance <= 50)
            {
                party_[i].subFullness(1); // take away one fullness point from that party member
                full.push_back(party_[i].getName());
                lost_full = true;
            }
        }

        if (lost_full == true)
        {
            cout << "Unfortunately, these members have lost one fullness point: " << endl;
            int full_size = full.size();
            for (int i = 0; i < full_size; i++)
            {
                cout << full[i] << endl;
            }
        }
    }
    else
    {
        defeated = false;
        int bounds = size_ - 1; // bounds are excluding the player
        int rand_member = rand() % bounds + 1; // random number between 1 and number of other party members
        string mem = party_[rand_member].getName();

        removeMember(mem);

        cout << mem << " was unable to escape the monster! They are now being held captive and must be left behind." << endl;
    }
    return defeated;
}

/*
    Algorithm: Function is called at beginning of game and when player speaks to NPC and successfully solves riddle
                Sells party items or offers to buy party's treasures
    1. Print inventory by calling printInventory() function
    2. Print merchant options by calling printMerchantOptions() function
    Whle the player hasn't selected 6:
        3. Takes options between 1 and 6
        If the player selected 1
            4. Asks how many kg of ingredients needed
            5. Calculate ingredient price based on price increase from number of rooms the player has defeated
            6. Ask to confirm purchase
            7. Check to see if player can afford object (call the checkPrice() function)
            8. Subtract gold from inventory
            9. Add ingredients to inventory
        If the player selected 2
            4. Asks which cookware to buy
            5. Asks how many of that cookware the player wants to buy
            6. Calculate cookware price based on price increase from number of rooms the player has defeated
            7. Ask to confirm purchase
            8. Check to see if player can afford object (call the checkPrice() function)
            9. Subtract gold from inventory
            10. Add cookware to inventory
        If the player selected 3
            4. Asks which weapon to buy
            5. Asks which party member gets the weapon
            6. Calculate weapon price based on price increase from number of rooms the player has defeated
            7. Ask to confirm purchase
            8. Check to see if player can afford object (call the checkPrice() function)
            9. Subtract gold from inventory
            10. Add weapon to inventory
        If the player selected 4
            4. Asks how many suits of armor to buy
            5. Calculate armor price based on price increase from number of rooms the player has defeated
            6. Ask to confirm purchase
            7. Check to see if player can afford object (call the checkPrice() function)
            8. Subtract gold from inventory
            9. Add armor to inventory
            10. Set corresponding party member armor characteristic to true
        If the player selected 5
            4. Check to see if player has any treasures
            5. Prompt for which treasure to sell
            6. If the player doesn't have that treasure in inventory, cancel the sale
            7. Otherwise, calculate price for treasure based on price increase from number of rooms player defeated
            8. Add price to inventory
            9. Remove treasure from inventory
        If the player selected 6
            4. Confirm that player wants to exit merchant
            5. Exit if yes
            6. Continue to loop if no
        
*/
void DungeonEscape::merchant()
{
    double price_increase = ((roomsCleared_ * 25.0) / 100.0) + 1.0;
    int price = 0;
    int input1 = 0;
    string input2 = "";
    int input3 = 0;
    int ing_price = (int)(1.0 * price_increase);
    int member = -1;

    string item_name = "";
    
    cout << "If you're looking to get supplies, you've come to the right place." << endl;
    cout << "I would be happy to part with some of my wares...for the proper price!" << endl;

    int option = -1;

    while (option != 6)
    {
        bool canceled = false;
        bool in_stock = true;
        printInventory();
        cout << endl;
        printMerchantOptions();

        cin >> option;

        // if the user has an invalid input
        while (!(option > 0 && option <= 6))
        {
            cout << "Invalid input. Please try again." << endl;
            printMerchantOptions();

            cin >> option;
        }

        // switch statement for what type of item player wants to buy
        switch (option)
        {
            // buying ingredients
            case 1:
                cout << "How many kg of ingredients do you need [" << ing_price << " Gold/kg]? (Enter a positive multiple of 5, or 0 to cancel)" << endl;
                cin >> input1;

                if (input1 == 0)
                {
                    cout << "Okay. Your request has been canceled. " << endl;
                    cout << endl;
                    break;
                }

                price = (int)(double(input1) * ing_price);
                
                cout << "You want to buy " << input1 << " kg of ingredients for " << price << " Gold? (y/n)" << endl;
                cin >> input2;

                if (input2 == "y")
                {
                    if (checkPrice(price) == false)
                    {
                        cout << "You don't have enough gold to get this item. Please pick a different item to purchase or end your visit." << endl;
                        break;
                    }
                    inv_.subGold(price);
                    inv_.addFood(input1);
                }
                else
                {
                    cout << "Okay. Your request has been canceled." << endl;
                    cout << endl;
                    break;
                }

                break;
            // buying cookware
            case 2:
                cout << "I have a several types of cookware, which one would you like?" << endl;
                cout << "Each type has a different probability of breaking when used, marked with (XX%)." << endl;
                cout << endl;
                cout << "Choose one of the following:" << endl;
                cout << " 1. (25%) Ceramic Pot [" << (int)(2.0 * price_increase) << " Gold]" << endl;
                cout << " 2. (10%) Frying Pan [" << (int)(10.0 * price_increase) << " Gold]" << endl;
                cout << " 3. ( 2%) Cauldron [" << (int)(20.0 * price_increase) << " Gold]" << endl;
                cout << " 4. Cancel" << endl;
                cout << endl;

                cin >> input1;

                // checking for cancel
                if (input1 == 4)
                {
                    cout << "Okay. Your request has been canceled. " << endl;
                    break;
                }

                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                cin >> input3;

                // checking for cancel
                if (input3 == 0)
                {
                    cout << "Okay. Your request has been canceled. " << endl;
                    break;
                }

                // switch statement for the different cookware options
                switch(input1)
                {
                    case 1: 
                        // calculating price for the pot(s)
                        price = input3 * 2 * price_increase;
                        item_name = "Ceramic Pot(s)";
                        break;
                    case 2:
                        price = input3 * 10 * price_increase;
                        item_name = "Frying Pan(s)";
                        break;
                    case 3:
                        price = input3 * 20 * price_increase;
                        item_name = "Cauldron(s)";
                        break;
                    default: // LATER BUILD IN AN OPTION FOR INVALID INPUT
                        break;
                }

                cout << "You want to buy " << input3 << " " << item_name << " for " << price << " Gold? (y/n)" << endl;
                cin >> input2;

                if (input2 == "y")
                {
                    // checking to see if player has enough money
                    if (checkPrice(price) == false)
                    {
                        cout << "You don't have enough gold to get this item. Please pick a different item to purchase or end your visit." << endl;
                        break;
                    }
                    // if they do, then subtract the price from their gold and add the item to inventory
                    inv_.subGold(price);

                    switch(input1)
                    {
                        case 1:
                            inv_.addPots(input3);
                            break;
                        case 2:
                            inv_.addPans(input3);
                            break;
                        case 3:
                            inv_.addCauldrons(input3);
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    cout << "Okay. Your request has been canceled." << endl;
                    cout << endl;
                    break;
                }
                break;

            // buying weapons
            case 3:
                cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl;
                cout << "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;
                cout << endl;
                cout << "Choose one of the following:" << endl;
                cout << " 1. Stone Club [" << (int)(2.0 * price_increase) << " Gold]" << endl;
                cout << " 2. Iron Spear [" << (int)(2.0 * price_increase) << " Gold]" << endl;
                cout << " 3. (+1) Mythril Rapier [" << (int)(5.0 * price_increase) << " Gold]" << endl;
                cout << " 4. (+2) Flaming Battle-Axe [" << (int)(15.0 * price_increase) << " Gold]" << endl;
                cout << " 5. (+3) Vorpal Longsword [" << (int)(50.0 * price_increase) << " Gold]" << endl;
                cout << " 6. Cancel" << endl;
                cout << endl;

                cin >> input1;

                // checking for cancel
                if (input1 == 6)
                {
                    cout << "Okay. Your request has been canceled. " << endl;
                    break;
                }

                // switch statement for the different cookware options
                switch(input1)
                {
                    case 1: 
                        // calculating price for the pot(s)
                        price = 2 * price_increase;
                        item_name = "Stone Club";
                        break;
                    case 2:
                        price = 2 * price_increase;
                        item_name = "Iron Spear";
                        break;
                    case 3:
                        price = 5 * price_increase;
                        item_name = "(+1) Mythril Rapier";
                        break;
                    case 4:
                        price = 15 * price_increase;
                        item_name = "(+2) Flaming Battle-Axe";
                        break;
                    case 5:
                        price = 50 * price_increase;
                        item_name = "(+3) Vorpal Longsword(s)";
                    default: // LATER BUILD IN AN OPTION FOR INVALID INPUT
                        break;
                }

                cout << "You want to buy a " << item_name << " for " << price << " Gold? (y/n)" << endl;
                cin >> input2;

                if (input2 == "y")
                {
                    // checking to see if player has enough money
                    if (checkPrice(price) == false)
                    {
                        cout << "You don't have enough gold to get this item. Please pick a different item to purchase or end your visit." << endl;
                        break;
                    }

                    cout << "Who in your party would you like to give the " << item_name << " to?" << endl;
                    for (int i = 0; i < size_; i++)
                    {
                        cout << i+1 << ". " << party_[i].getName() << endl;
                    }

                    cin >> member;
                    
                    if (member > size_ || member < 1)
                    {
                        cout << "Invalid input. Purchase canceled." << endl;
                        cout << endl;
                        break;
                    }
                    else if (party_[member-1].getWeapon() > 0)
                    {
                        cout << "Looks like that party member already has a weapon. Purchase canceled." << endl;
                        cout << endl;
                        break;
                    }
                    else
                    {
                        party_[member-1].setWeapon(input1);
                        cout << party_[member-1].getName() << " now has a " << item_name << endl;
                        cout << endl;
                    }

                    // if they do, then subtract the price from their gold
                    inv_.subGold(price);
                    // and add the item(s) to inventory
                    switch(input1)
                    {
                        case 1:
                            inv_.addClubs(1);
                            break;
                        case 2:
                            inv_.addSpears(1);
                            break;
                        case 3:
                            inv_.addRapiers(1);
                            break;
                        case 4:
                            inv_.addAxes(1);
                            break;
                        case 5:
                            inv_.addLongswords(1);
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    cout << "Okay. Your request has been canceled." << endl;
                    cout << endl;
                    break;
                }
                break;
            case 4:
                cout << "How many suits of armor can I get you? [" << (int)(5.0 * price_increase) << " Gold/Armor] (Enter a positive integer, or 0 to cancel)" << endl;
                cout << "(if you purchase less than " << size_ << " suits of armor, then the armor will be given to the party in your original order of players)" << endl;
                cout << endl;
                cin >> input1;

                // checking for cancel
                if (input1 == 0)
                {
                    cout << "Okay. Your request has been canceled." << endl;
                    cout << endl;
                    break;
                }

                price = input1 * (int)(5.0 * price_increase);

                cout << "You want to buy " << input1 << " suit(s) of armor for " << price << " Gold? (y/n)" << endl;
                cin >> input2;

                if (input2 == "y")
                {
                    // checking to see if player has enough money
                    if (checkPrice(price) == false)
                    {
                        cout << "You don't have enough gold to get this item. Please pick a different item to purchase or end your visit." << endl;
                        break;
                    }
                    // if they do, then subtract the price from their gold
                    inv_.subGold(price);

                    // and add armor to inventory and set the party member(s) armor to true
                    for (int i = 0; i < input1; i++)
                    {
                        party_[i].setArmor(true);
                        inv_.addArmor(1);
                    }
                }
                else
                {
                    cout << "Okay. Your request has been canceled." << endl;
                    cout << endl;
                    break;
                }

                break;
            // selling the merchant treasure
            case 5:
                if (inv_.getTotalTreasure() == 0)
                {
                    cout << "It looks like you don't have any treasure to sell me. Please choose a different option." << endl;
                    cout << endl;
                    break;
                }
                
                cout << "You have many beautiful treasures! Which would you like to sell to me?" << endl;
                cout << " 1. Silver ring - worth 10 gold pieces each" << endl;
                cout << " 2. Ruby necklace - worth 20 gold pieces each" << endl;
                cout << " 3. Emerald bracelet - worth 30 gold pieces each" << endl;
                cout << " 4. Diamond circlet - worth 40 gold pieces each" << endl;
                cout << " 5. Gem-encrusted goblet - worth 50 gold pieces each" << endl;
                cout << " 6. Cancel" << endl;
                cout << endl;

                cin >> input1;

                if (input1 == 6)
                {
                    cout << "Okay. The sale has been canceled." << endl;
                    cout << endl;
                    break;
                }

                switch(input1)
                {
                    case 1:
                        if (inv_.getRings() == 0)
                        {
                            cout << "It looks like you don't have any rings. The sale has been canceled." << endl;
                            cout << endl;
                            break;
                        }
                        else
                        {
                            cout << "You'd like to sell me one silver ring for 10 Gold? (y/n)" << endl;
                            cout << endl;

                            cin >> input2;
                            if (input2 == "y")
                            {
                                inv_.addRings(-1); // subtracting one ring from inventory
                                inv_.addGold(10);
                                cout << "Thank you for your business! I've paid 10 Gold." << endl;
                                cout << endl;
                                break;
                            }
                            else
                            {
                                cout << "Okay. The sale has been canceled." << endl;
                                cout << endl;
                                break;
                            }
                        }
                        break;
                    case 2:
                        if (inv_.getNecklaces() == 0)
                        {
                            cout << "It looks like you don't have any necklaces. The sale has been canceled." << endl;
                            cout << endl;
                            break;
                        }
                        else
                        {
                            cout << "You'd like to sell me one ruby necklace for 20 Gold? (y/n)" << endl;
                            cout << endl;

                            cin >> input2;
                            if (input2 == "y")
                            {
                                inv_.addNecklaces(-1); // subtracting one ring from inventory
                                inv_.addGold(20);
                                cout << "Thank you for your business! I've paid 20 Gold." << endl;
                                cout << endl;
                                break;
                            }
                            else
                            {
                                cout << "Okay. The sale has been canceled." << endl;
                                cout << endl;
                                break;
                            }
                        }
                        break;
                    case 3:
                        if (inv_.getBracelets() == 0)
                        {
                            cout << "It looks like you don't have any bracelets. The sale has been canceled." << endl;
                            cout << endl;
                            break;
                        }
                        else
                        {
                            cout << "You'd like to sell me one emerald bracelet for 30 Gold? (y/n)" << endl;
                            cout << endl;

                            cin >> input2;
                            if (input2 == "y")
                            {
                                inv_.addBracelets(-1); // subtracting one ring from inventory
                                inv_.addGold(30);
                                cout << "Thank you for your business! I've paid 30 Gold." << endl;
                                cout << endl;
                                break;
                            }
                            else
                            {
                                cout << "Okay. The sale has been canceled." << endl;
                                cout << endl;
                                break;
                            }
                        }
                        break;
                    case 4:
                        if (inv_.getCirclets() == 0)
                        {
                            cout << "It looks like you don't have any circlets. The sale has been canceled." << endl;
                            cout << endl;
                            break;
                        }
                        else
                        {
                            cout << "You'd like to sell me one diamond circlet for 40 Gold? (y/n)" << endl;
                            cout << endl;

                            cin >> input2;
                            if (input2 == "y")
                            {
                                inv_.addCirclets(-1); // subtracting one ring from inventory
                                inv_.addGold(40);
                                cout << "Thank you for your business! I've paid 40 Gold." << endl;
                                cout << endl;
                                break;
                            }
                            else
                            {
                                cout << "Okay. The sale has been canceled." << endl;
                                cout << endl;
                                break;
                            }
                        }
                        break;
                    case 5:
                        if (inv_.getGoblets() == 0)
                        {
                            cout << "It looks like you don't have any goblets. The sale has been canceled." << endl;
                            cout << endl;
                            break;
                        }
                        else
                        {
                            cout << "You'd like to sell me one gem-encrusted goblet for 50 Gold? (y/n)" << endl;
                            cout << endl;

                            cin >> input2;
                            if (input2 == "y")
                            {
                                inv_.addGoblets(-1); // subtracting one ring from inventory
                                inv_.addGold(50);
                                cout << "Thank you for your business! I've paid 50 Gold." << endl;
                                cout << endl;
                                break;
                            }
                            else
                            {
                                cout << "Okay. The sale has been canceled." << endl;
                                cout << endl;
                                break;
                            }
                        }
                        break;
                    default:
                        break;
                }
                break;
            // exiting the merchant menu
            case 6:
                cout << "Are you sure you're finished? You won't be able to buy anything else from me! (y/n)" << endl;
                cin >> input2;

                if (input2 == "y")
                {
                    cout << "Stay safe out there! Goodbye!" << endl;
                }
                else
                {
                    option = 0;
                }
                break;
            default:
                break;
        }
    }
}

/*
    Algorithm: function called when player wants to cook food on normal space
    1. Check to see if player has ingredients and cookware
    If they don't
        2. Print that the player is unable to cook
    If they do
        2. Ask player what they'd like to cook with
        3. Cancel cook if they don't have the item in inventory
        4. Ask how many kg of ingredients to be used for cook
        5. Check to see if player has enough ingredients
        6. Apply chance of cookware breaking
        7. Take ingredients away from inventory
        If cookware broke
            8. Print that cook was unsuccessful
            9. Remove cookware from inventory
        If cookware didn't break
            8. Increase fullness for each party member by ingredients used divided by 5
            9. Print out the fullness of each member
            10. Print out new value of ingredients in inventory
*/
void DungeonEscape::cook()
{
    // checking to see if the player has ingredients and cookware
    if (inv_.getTotalCookware() == 0)
    {
        cout << "Looks like you don't have any cookware. Sorry, you are unable to cook." << endl;
        cout << endl;
        return;
    }
    else if (inv_.getFood() == 0)
    {
        cout << "Looks like you don't have any ingredients to cook with. Sorry, you are unable to cook." << endl;
        cout << endl;
        return;
    }

    int ingredients_used = 0;
    int cookware = 0;
    int chance_of_breaking = 0;
    string cookware_name = "";

    cout << "What would you like to cook with?" << endl;
    cout << "Keep in mind, you have: " << inv_.getPots() << " Ceramic Pot(s), " << inv_.getPans() << " Frying Pan(s), and " << inv_.getCauldrons() << " Cauldrons." << endl;
    cout << endl;
    cout << " 1. (25%) Ceramic Pot" << endl;
    cout << " 2. (10%) Frying Pan" << endl;
    cout << " 3. ( 2%) Cauldron" << endl;
    cout << endl;
    cin >> cookware;

    // checking for invalid input
    while (cookware < 1 || cookware > 3)
    {
        cout << "Invalid input. Please choose a valid cookware." << endl;
        cout << " 1. (25%) Ceramic Pot" << endl;
        cout << " 2. (10%) Frying Pan" << endl;
        cout << " 3. ( 2%) Cauldron" << endl;
        cout << endl;
        cin >> cookware;
    }

    // checking to see if they have that cookware in inventory
    switch(cookware)
    {
        case 1:
            if (inv_.getPots() <= 0)
            {
                cout << "You do not have a pot in inventory. The cook has been canceled." << endl;
                return;
            }
            break;
        case 2:
            if (inv_.getPans() <= 0)
            {
                cout << "You do not have a pot in inventory. The cook has been canceled." << endl;
                return;
            }
            break;
        case 3:
            if (inv_.getCauldrons() <= 0)
            {
                cout << "You do not have a pot in inventory. The cook has been canceled." << endl;
                return;
            }
            break;
        default:
            break;
    }

    cout << "You have " << inv_.getFood() << " kg of ingredients. " << endl;
    cout << "How many kg of ingredients would you like to use? (Enter a positive multiple of 5)" << endl;
    cout << endl;
    cin >> ingredients_used;

    // checking for invalid input
    while (ingredients_used < 0 || ingredients_used % 5 != 0)
    {
        cout << "Invalid input. Please choose enter a positive multiple of 5." << endl;
        cout << endl;
        cin >> ingredients_used;
    }

    // checking to see if player has enough ingredients
    while (ingredients_used > inv_.getFood())
    {
        cout << "You have " << inv_.getFood() << " kg of ingredients, which is not enough to make " << ingredients_used << " kg worth of food." << endl;
        cout << "Please enter a valid amount of ingredients." << endl;
        cin >> ingredients_used;
    }

    switch(cookware)
    {
        case 1:
            chance_of_breaking = 25;
            cookware_name = "ceramic pot";
            break;
        case 2:
            chance_of_breaking = 10;
            cookware_name = "frying pan";
            break;
        case 3:
            chance_of_breaking = 2;
            cookware_name = "cauldron";
            break;
        default:
            break;
    }

    inv_.subFood(ingredients_used); // removing ingredients from inventory

    int result = rollDice();
    if (result <= chance_of_breaking)
    {
        cout << "Oh no! Your " << cookware_name << " has broken and " << ingredients_used << " kg of ingredients have been lost." << endl;
        cout << endl;

        // switch for removing the cookware from inventory
        switch(cookware)
        {
            case 1:
                inv_.subPots(1);
                break;
            case 2:
                inv_.subPans(1);
                break;
            case 3:
                inv_.subCauldrons(1);
                break;
            default:
                break;
        }
    }
    else
    {
        cout << "Wonderful! Your cook was successful!" << endl;
        cout << endl;

        // adding fullness to each character
        int fullness_increase = ingredients_used / 5;
        for (int i = 0; i < size_; i++)
        {
            party_[i].addFullness(fullness_increase);
        }
    }

    // print out the fullness regardless of the outcome of the cook
    cout << "Fullness levels for each party member:" << endl;
    for (int i = 0; i < size_; i++)
    {
        cout << party_[i].getName() << ": " << party_[i].getFullness() << " fullness" << endl;
    }
    cout << endl;
    cout << "Remaining amount of food: " << inv_.getFood() << " kg" << endl;
    return;
}

/*
    Algorithm: calculates chances of a misfortune occuring for the party
                Takes an input of whether the party is attempting to open the door to a room (bool)
    1. call rollDice() function
    If function returns number between 1 and 30 (30% chance)
        Party robbed by bandits
        2. call rollDice() function
        If function returns number between 1 and 33 (33% chance)
            3. Take 10 kg of ingredients away from inventory
            4. Print out message for loss and updated ingredient count
        If function returns number between 34 and 66 (33% chance)
            3. Take one cookware item away from inventory
            4. Print out message for loss and updated cookware count
        If function returns number between 67 and 100 (34% chance)
            3. Take one suit of armor away from inventory
            4. Set party member's armor to false
            5. Print out message for loss and updated armor
    If function returns number between 31 and 40 (30% chance)
        Party breaks a set of armor or weapon
        2. call rollDice() function
        If function returns number between 1 and 50 (50% chance)
            3. Take one weapon item away from inventory
            4. Print out message for loss and updated weapon count
        If function returns number between 51 and 100
            3. Take one suit of armor away from inventory
            4. Set party member's armor to false
            5. Print out message for loss and updated armor
    If function returns number between 41 and 70 (30% chance)
        One party member gets food poisoning
        2. call rollDice() function to choose random party member to get food poisoning (excluding main player)
        3. Subtract 10 fullness from chosen party member
        If the party member still has fullness left
            4. Print out message that party member has lost 10 fullness points
        If the party member's fullness hit 0
            4. Print out message that party member was immediately killed from the food poisoning
            5. removeMember() function to remove party member from game
    If the party is attempting to open a door
        30% chance that a party member trapped in the last room
        2. call rollDice() function to choose random party member to get left behind (excluding main player)
        3. Print out message that party member left behind
        4. call removeMember() function to remove party member from game
*/
void DungeonEscape::misfortune(bool openingDoor)
{
    int roll = rollDice();
    
    // 30% chance that the team is robbed
    if (roll >=1 && roll <=30)
    {
        cout << "OH NO! Your team was robbed by dungeon bandits!" << endl;
        cout << endl;
        int roll2 = rollDice();

        // 33% chance of losing 10 kg of ingredients
        if (roll2 >= 1 && roll2 <= 33)
        {
            if (inv_.getFood() <= 0)
            {
                cout << "Looks like you don't have any ingredients for the bandits to steal." << endl;
                cout << "The bandits did no harm! You're lucky!" << endl;
                cout << endl;
                return;
            }
            cout << "You've lost 10 kg of ingredients!" << endl;
            inv_.subFood(10);
            cout << "Updated ingredient count: " << inv_.getFood() << " kg" << endl;
            cout << endl;
            return;
        }

        // 33% chance of losing 1 cookware item
        else if (roll2 >= 34 && roll2 <= 66)
        {
            if (inv_.getTotalCookware() <= 0)
            {
                cout << "Looks like you don't have any cookware for the bandits to steal." << endl;
                cout << "The bandits did no harm! You're lucky!" << endl;
                cout << endl;
                return;
            }

            if (inv_.getPots() >= 1)
            {
                inv_.subPots(1);
                cout << "You've lost 1 Pot." << endl;
                cout << endl;
                return;
            }
            else if (inv_.getPans() >= 1)
            {
                inv_.subPans(1);
                cout << "You've lost 1 Pan." << endl;
                cout << endl;
                return;
            }
            else if (inv_.getCauldrons() >= 1)
            {
                inv_.subCauldrons(1);
                cout << "You've lost 1 Cauldron." << endl;
                cout << endl;
                return;
            }
        }

        // 33% chance of losing 1 set of armor
        else
        {
            if (inv_.getArmor() <= 0)
            {
                cout << "Looks like you don't have any armor for the bandits to steal." << endl;
                cout << "The bandits did no harm! You're lucky!" << endl;
                cout << endl;
                return;
            }

            string name = "";
            for (int i = 0; i < size_; i++)
            {
                if (party_[i].getArmor() == true)
                {
                    party_[i].setArmor(false); // setting armor for this character to false
                    inv_.addArmor(-1); // taking armor away from inventory
                    name = party_[i].getName();
                    break;
                }
            }

            cout << "You've lost 1 suit of armor. " << name << " is now without armor." << endl;
            cout << endl;
            return;
        }
    }
    
    // 10% chance that one of the weapons/armor breaks
    else if (roll >=31 && roll <= 40)
    {
        cout << "OH NO! One of your party members was not being careful and one of your weapons/armor may break!" << endl;
        cout << endl;
        int roll3 = rollDice();

        // 50% chance for a weapon to break
        if (roll3 >= 1 && roll3 <= 50)
        {
            if (inv_.getTotalWeapons() <= 0)
            {
                cout << "Looks like you don't have any weapons." << endl;
                cout << "Your party members' carelessness was not an issue. You're lucky!" << endl;
                cout << endl;
                return;
            }
            
            string name = "";
            string weapon_name = "";
            for (int i = 0; i < size_; i++)
            {
                if (party_[i].getWeapon() > 0)
                {
                    int weapon_type = party_[i].getWeapon();
                    party_[i].setWeapon(-1); // setting weapon for this character to be -1 (none)
                    
                    switch(weapon_type)
                    {
                        case 1:
                            inv_.addClubs(-1); // taking a club away from inventory
                            weapon_name = "club";
                            break;
                        case 2:
                            inv_.addSpears(-1); // taking a spear away from inventory
                            weapon_name = "spear";
                            break;
                        case 3:
                            inv_.addRapiers(-1); // taking a rapier away from inventory
                            weapon_name = "+1 rapier";
                            break;
                        case 4:
                            inv_.addAxes(-1); // taking an axe away from inventory
                            weapon_name = "+2 axe";
                            break;
                        case 5:
                            inv_.addLongswords(-1); // taking a longsword away from inventory
                            weapon_name = "+3 longsword";
                            break;
                        default:
                            break;
                    }

                    name = party_[i].getName(); // getting the name of the party member
                    break;
                }
            }

            cout << "Unfortunately, " << name << " has broken a " << weapon_name << "!" << endl;
            cout << "The " << weapon_name << " is no longer in inventory." << endl;
            return;
        }

        // 50% chance for a set of armor to break
        else
        {
            if (inv_.getArmor() <= 0)
            {
                cout << "Looks like you don't have any armor." << endl;
                cout << "Your party members' carelessness was not an issue. You're lucky!" << endl;
                cout << endl;
                return;
            }

            string name = "";
            for (int i = 0; i < size_; i++)
            {
                if (party_[i].getArmor() == true)
                {
                    party_[i].setArmor(false); // setting weapon for this character to be -1 (none)
                    inv_.addArmor(-1); // removing a suit of armor from inventory
                    name = party_[i].getName(); // getting the name of the party member
                    break;
                }
            }

            cout << "Unfortunately, " << name << " has broken their suit of armor!" << endl;
            cout << "The suit is no longer in inventory." << endl;
            return;
        }
    }

    // 30% chance of food poisoning
    else if (roll >= 41 && roll <= 70)
    {
        int rand_member = rand() % size_; // choosing a random party member
        party_[rand_member].subFullness(10);

        cout << "OH NO! " << party_[rand_member].getName() << " has gotten food poisoning!" << endl;

        if (party_[rand_member].getFullness() <= 0)
        {
            cout << "This has caused them to reach 0 fullness. " << party_[rand_member].getName() << " has died." << endl;
            cout << endl;
            removeMember(party_[rand_member].getName());
            return;
        }
        else
        {
            cout << party_[rand_member].getName() << " has lost 10 fullness points." << endl;
            cout << endl;
            return;
        }
    }

    // 30% chance of team member getting locked in previous room
    else
    {
        // this only occurs if the party is opening a door with a key, so if not opening door, then nothing happens
        if (openingDoor == false)
        {
            return;
        }
        else
        {
            int bounds = size_-1; // ensures that the player is not being chosen to be left behind
            int r = rand() % bounds + 1; // choosing random party member, not including the player

            cout << "OH NO! Your teammate " << party_[r].getName() << " is trapped in the previous room and is unable to get through. You must continue without them." << endl;

            removeMember(party_[r].getName()); // removing party member from game

            cout << "Your party size has reduced to " << size_ << " members. " << endl;
            cout << endl;
            return;
        }
    }
    return;
}

// returns sorcerer anger level (anger_)
int DungeonEscape::getSorcererAnger()
{
    return anger_;
}

// adds sorcerer anger
void DungeonEscape::addSorcererAnger(int anger)
{
    anger_ = anger_ + anger;
    return;
}

/*
    Algorithm: Returns true if the party can afford an item based on an inputed price, false if they cannot
    1. If the gold in inventory is less than the price, return true
    2. Otherwise, return false
*/
bool DungeonEscape::checkPrice(int price)
{
    if (inv_.getGold() < price)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*
    Algorithm: Gives an update on the members that are hungry or that have died of hunger, removes any members that died of hunger
    Cycle through each party member
        If the party member's fullness is at 0
            1. Add member's name to a "dead list"
            2. Remove member from the game by calling removeMember() function
        If the party member's fullness is less than or equal to 2
            1. Add member's name to a "hungry list"
    If the "dead vector" has size greater than 0
        3. Print out the names of those who have died of starvation
    If the "hungry vector" has size greater than 0
        3. Print out names of those who are hungry
        4. Suggest that party cooks and eats food
*/
void DungeonEscape::checkFullness()
{
    vector<string> dead_names;
    vector<string> hungry_names;
    for (int i = 0; i < size_; i++)
    {
        if (party_[i].getFullness() <= 0)
        {
            dead_names.push_back(party_[i].getName()); // add name to dead list
            removeMember(party_[i].getName()); // remove member from the game
        }
        else if (party_[i].getFullness() <= 2)
        {
            hungry_names.push_back(party_[i].getName()); // add name to hungry list
        }
    }
    if (dead_names.size() > 0)
    {
        cout << "Oh no! Unfortunately, these members have died of starvation this turn: " << endl;
        for (int i = 0; i < dead_names.size(); i++)
        {
            cout << dead_names[i] << endl;
        }
        cout << endl;
    }
    if (hungry_names.size() > 0)
    {
        cout << "Warning - these members are on the brink of starvation:" << endl;
        for (int i = 0; i < hungry_names.size(); i++)
        {
            cout << hungry_names[i] << endl;
        }
        cout << endl;
        cout << "You should cook and eat food!" << endl;
        cout << endl;
    }
    return;
}

/*
    Algorithm: returns -1 if the game is still going on, 1 if the party lost because party members died, 2 if the 
    party lost because the sorcerer reached 100 anger
*/
int DungeonEscape::gameOver()
{
    // if the player lost all other party members, return 2
    if (size_ <= 1)
    {
        return 1;
    }
    // if the sorcerer anger reached 100, return 3
    else if (anger_ >= 100)
    {
        return 2;
    }
    // otherwise, return -1
    else
    {
        return -1;
    }
}

/*
    Algorithm: Removes party member from game and updates inventory accordingly
    Input: name of party member to be removed
    1. Loop through the party_ vector to find the player with the given name
    2. Take away their corresponding weapon from inventory
    3. Erase the Character from the vector
    4. Decrease size_ by 1
*/
void DungeonEscape::removeMember(string name)
{
    Character c;
    int index;
    for (int i = 0; i < size_; i++)
    {
        if (party_[i].getName() == name)
        {
            c = party_[i];
            index = i;
            break;
        }
    }
    
    int w = c.getWeapon();
    if (w == 1)
    {
        inv_.addClubs(-1); // removing a club from inventory
    }
    else if (w == 2)
    {
        inv_.addSpears(-1); // removing a spear from inventory
    }
    else if (w == 3)
    {
        inv_.addRapiers(-1); // removing a rapier from inventory
    }
    else if (w == 4)
    {
        inv_.addAxes(-1); // removing an axe from inventory
    }
    else if (w == 5)
    {
        inv_.addLongswords(-1); // removing a longsword from inventory
    }

    if (c.getArmor() == true)
    {
        inv_.addArmor(-1); // removing armor from inventory
    }

    party_.erase(party_.begin() + index); // removing the character from the party vector
    size_--; // decreasing size by 1
}

/*
    Algorithm: reads monsters and challenge levels from a text file, creates Monster variables, stores Monsters in vectors
    organized by challenge level
    1. Open the file "monsters.txt"
    While the file is open:
        2. Get the current line on the file
        3. Call split() function to split riddles into monster names and challenge levels
        4. Create new monster with given name and challenge level
        5. Add monster to corresponding monster vector
    6. Close the text file
    7. Add monster vectors to array of size 5
*/
void DungeonEscape::readMonsters(string file_name)
{
    ifstream file_input;
    string line = ""; // holding the current line being read
    string arr [2];
    int split_result;

    // open the file
    file_input.open(file_name);

    if (file_input.is_open()) 
    {
        // while the number of posts in the array is less than the array size
        while (!file_input.eof())
        {
            // gets line of text from file_input, stores it in line
            getline(file_input, line);

            // split line into array of size 2
            split_result = split(line, ',', arr, 2);

            // if the split function successfully splits the line into two parts
            if (split_result == 2)
            {
                int lvl = stoi(arr[1]);
                Monster mon = Monster(arr[0], lvl, true);
                
                switch(lvl)
                {
                    case 1:
                        monster_1.push_back(mon);
                        break;
                    case 2:
                        monster_2.push_back(mon);
                        break;
                    case 3:
                        monster_3.push_back(mon);
                        break;
                    case 4:
                        monster_4.push_back(mon);
                        break;
                    case 5:
                        monster_5.push_back(mon);
                        break;
                    case 6:
                        sorcerer_ = mon;
                        break;
                    default:
                        break;
                }
            }
        }
        // close the file
        file_input.close();

        monster_vects[0] = monster_1;
        monster_vects[1] = monster_2;
        monster_vects[2] = monster_3;
        monster_vects[3] = monster_4;
        monster_vects[4] = monster_5;

        return;
    }
    return;
}

/*
    Algorithm: Returns a random integer in the range of 0 to corresponding monster vector's size - 1 
    1. Set int variable vect_size equal to corresponding monster depending on rooms cleared
    2. Return random number between 0 and monster level vecotr size - 1
*/
int DungeonEscape::randomMonster(int rooms_cleared)
{
    int vect_size = 0;
    switch (rooms_cleared)
    {
        case 0:
            vect_size = monster_1.size();
            break;
        case 1:
            vect_size = monster_2.size();
            break;
        case 2:
            vect_size = monster_3.size();
            break;
        case 3:
            vect_size = monster_4.size();
            break;
        case 4:
            vect_size = monster_5.size();
            break;
        case 5:
            return 1;
            break;
        default:
            break;
    }

    return rand() % vect_size;
}

/*
    Algorithm: Removes a monster from its monster level vector and adds monster to defeated monster vector
    Inputs: (level of monster, name of monster)
    Loop through corresponding monster vector
        If the current monster's name matches the input name
            1. Set the monster to dead
            2. Remove monster from its level vector
            3. Add monster to defeated_monsters vector
*/
void DungeonEscape::defeatMonster(int level, string name)
{
    switch(level)
    {
        case 1:
            for (int i = 0; i < monster_1.size(); i++)
            {
                if (monster_1[i].getName() == name)
                {
                    Monster mon = monster_1[i];
                    mon.setStatus(false); // set to dead
                    monster_1.erase(monster_1.begin() + i); // remove monster from list
                    defeated_monsters.push_back(mon); // add to defeated list
                    return;
                }
            }
            break;
        case 2:
            for (int i = 0; i < monster_2.size(); i++)
            {
                if (monster_2[i].getName() == name)
                {
                    Monster mon = monster_2[i];
                    mon.setStatus(false); // set to dead
                    monster_2.erase(monster_2.begin() + i); // remove monster from list
                    defeated_monsters.push_back(mon); // add to defeated list
                    return;
                }
            }
            break;
        case 3:
            for (int i = 0; i < monster_3.size(); i++)
            {
                if (monster_3[i].getName() == name)
                {
                    Monster mon = monster_3[i];
                    mon.setStatus(false); // set to dead
                    monster_3.erase(monster_3.begin() + i); // remove monster from list
                    defeated_monsters.push_back(mon); // add to defeated list
                    return;
                }
            }
            break;
        case 4:
            for (int i = 0; i < monster_4.size(); i++)
            {
                if (monster_4[i].getName() == name)
                {
                    Monster mon = monster_4[i];
                    mon.setStatus(false); // set to dead
                    monster_4.erase(monster_4.begin() + i); // remove monster from list
                    defeated_monsters.push_back(mon); // add to defeated list
                    return;
                }
            }
            break;
        case 5:
            for (int i = 0; i < monster_5.size(); i++)
            {
                if (monster_4[i].getName() == name)
                {
                    Monster mon = monster_5[i];
                    mon.setStatus(false); // set to dead
                    monster_5.erase(monster_5.begin() + i); // remove monster from list
                    defeated_monsters.push_back(mon); // add to defeated list
                    return;
                }
            }
            break;
        default:
            return;
            break;
    }
    return;
}

/*
    Algorithm: Prints out the statistics at the end of the game
    1. Create ofstream object
    2. Open "stats.txt"
    3. Write to file: remaining party members
    4. Write to file: number of rooms cleared
    5. Write to file: number of gold pieces remaining
    6. Write to file: number of treasure items
    7. Write to file: number of monsters defeated
*/
void DungeonEscape::printStats()
{
    ofstream fout;

    fout.open("stats.txt");

    // printing out leader name and remaining party members
    fout << "Remaining party members:" << endl;
    for (int i = 0; i < size_; i++)
    {
        fout << party_[i].getName() << endl;
    }
    fout << endl;

    fout << "Number of rooms cleared: " << roomsCleared_ << endl;
    fout << "Number of gold pieces remaining: " << inv_.getGold() << endl;
    fout << "Number of treasure items: " << inv_.getTotalTreasure() << endl;
    fout << "Number of monsters defeated: " << defeated_monsters.size() << endl;
    // number of turns elapsed and number of explored spaces will be printed out in dungeonEscapeDriver.cpp
    return;
}

// prints out the members in the party and their fullness levels
void DungeonEscape::printPartyMembers()
{
    cout << "| PARTY       |" << endl;
    cout << "+-------------+" << endl;

    for (int i = 0; i < size_; i++)
    {
        cout << "| " << party_[i].getName() << " | Fullness: " << party_[i].getFullness() << endl;
    }
}

// prints out the items in inventory
void DungeonEscape::printInventory()
{
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << inv_.getGold() << endl; 
    cout << "| Ingredients | " << inv_.getFood() << " kg" << endl;
    cout << "| Cookware    | P: " << inv_.getPots() << " | F: " << inv_.getPans() << " | C: " << inv_.getCauldrons() << endl;
    cout << "| Weapons     | C: " << inv_.getClubs() << " | S: " << inv_.getSpears() << " | R: " << inv_.getRapiers() << " | B: " << inv_.getAxes() << " | L: " << inv_.getLongswords() << endl;
    cout << "| Armor       | " << inv_.getArmor() << endl;
    cout << "| Treasures   | R: " << inv_.getRings() << " | N: " << inv_.getNecklaces() << " | B: " << inv_.getBracelets() << " | C: " << inv_.getCirclets() << " | G: " << inv_.getGoblets() << endl;
    return;
}

// prints the options that the merchant offers in the merchant() function
void DungeonEscape::printMerchantOptions()
{
    cout << "Choose one of the following: " << endl;
    cout << " 1. Ingredients: To make food, you have to cook raw ingredients." << endl;
    cout << " 2. Cookware: You will need something to cook those ingredients." << endl;
    cout << " 3. Weapons: It's dangerous to go alone, take this!" << endl;
    cout << " 4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
    cout << " 5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
    cout << " 6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
    cout << endl;
    return;
}

// prints the weapons in inventory
void DungeonEscape::printWeapons()
{
    for (int i = 0; i < size_; i++)
    {
        cout << party_[i].getName() << ": " << party_[i].getWeapon() << endl;
    }
    return;
}

// increments roomsCleared_ by 1
void DungeonEscape::addRoomsCleared()
{
    roomsCleared_ = roomsCleared_ + 1;
}

// returns roomsCleared_
int DungeonEscape::getRoomsCleared()
{
    return roomsCleared_;
}

/*
    Algorithm: helper function that generates a random number between 1 and 100 (inclusive)
*/
int rollDice()
{
    int result = rand() % 100 + 1;
    
    return result;
}

/*
    Algorithm: Takes an input string and input delimiter and adds each section of string between delimiters to an array
    1. Accepts string, the delimiter character, array of type string, and the size of that array
    2. If the length of the input string is 0, return 0
    3. Go through each character of the string
    4. If the current character is not the delimiter, then add it to curString (string since the last delimiter)
    5. If the current character is the delimiter and the number of strings in the array is larger than the size of the array, return -1
    6. Otherwise, set the next available index in the array equal to curString and reset curString
    7. Increment the size
    8. After looping through, add the last curString to the array and return the number of elements in the array
*/
int split (string input_string, char separator, string arr [], int arr_size)
{
    string curString = "";
    int size = 0;
    int stringLength = input_string.length();

    // if the input string is empty, return 0
    if (stringLength == 0)
    {
        return 0;
    }

    // loop through each character of the string
    for (int i = 0; i < stringLength; i++)
    {
        // if the current character is not the separator
        if (input_string[i] != separator)
        {
            // add that character to curString
            curString += input_string[i];
        }
        else 
        {
            // if the size is greater than the array size, return -1
            if (size > arr_size)
            {
                return -1;
            }
            else
            {
                // set the next available spot in the array to curString
                arr[size] = curString;
                // reset curString
                curString = "";
            }
            // increment size
            size++;
        }
    }
    // add the last curString to the array
    arr[size] = curString;
    // if the number of elements is larger than the array, return -1
    if (size >= arr_size)
    {
        return -1;
    }
    // return the number of elements in the array
    return size+1;
}