// CSCI 1300 Fall 2022
// Author: Linh Tran
// Recitation: 206 - Baljot Kaur
// Project 3 - Code Skeleton - Character Class

#include "Character.h"
#include <iostream>
using namespace std;

// default constructor
Character::Character()
{
    fullness_ = 50;
    armor_ = false;
    player_ = false;
    name_ = "";
    weapon_ = -1;
}

bool Character::getArmor()
{
    return armor_;
}

void Character::setArmor(bool armor)
{
    armor_ = armor;
}

int Character::getFullness()
{
    return fullness_;
}

void Character::setFullness(int full)
{
    fullness_ = full;
}

void Character::addFullness(int full)
{
    fullness_ = fullness_ + full;
}

void Character::subFullness(int full)
{
    fullness_ = fullness_ - full;
    if (fullness_ < 0)
    {
        fullness_ = 0;
    }
}

// returns if the character is the player in the game
bool Character::isPlayer()
{
    return player_;
}

// sets whether the character is a player in the game
void Character::setPlayer(bool player)
{
    player_ = player;
}

string Character::getName()
{
    return name_;
}

void Character::setName(string name)
{
    name_ = name;
}

void Character::setWeapon(int weapon)
{
    weapon_ = weapon;
}

int Character::getWeapon()
{
    return weapon_;
}