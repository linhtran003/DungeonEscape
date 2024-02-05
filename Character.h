// CSCI 1300 Fall 2022
// Author: Linh Tran
// Recitation: 206 - Baljot Kaur
// Project 3 - Code Skeleton - Character Class

#include <iostream>
using namespace std;

class Character
{
    public:
    Character(); // default constructor

    // getters and setters
    int getFullness();
    void setFullness(int full);
    void addFullness(int full);
    void subFullness(int full);
    bool getArmor();
    void setArmor(bool armor);
    bool isPlayer();
    void setPlayer(bool player);
    string getName();
    void setName(string name);
    void setWeapon(int weapon);
    int getWeapon();

    private:
    int fullness_; // fullness level of the character
    bool armor_; // whether or not this character has armor on
    int weapon_; // integer that represents which weapon type the character has (if one)
    bool player_; // whether or not this character is a player
    string name_; // name of the character
};