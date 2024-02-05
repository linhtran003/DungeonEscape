// CSCI 1300 Fall 2022
// Author: Linh Tran
// Recitation: 206 - Baljot Kaur
// Project 3 - Code Skeleton - Monster Class

#include "Monster.h"
#include <iostream>
using namespace std;

// default constructor
Monster::Monster()
{
    rating_ = 1;
    status_ = true; // monster is alive to start
    name_ = "";
}

// parameterized constructor
Monster::Monster(string name, int rating, bool status)
{
    rating_ = rating;
    status_ = status;
    name_ = name;
}

int Monster::getRating()
{
    return rating_;
}

void Monster::setRating(int rating)
{
    rating_ = rating;
}

bool Monster::getStatus()
{
    return status_;
}

void Monster::setStatus(bool status)
{
    status_ = status;
}

string Monster::getName()
{
    return name_;
}

void Monster::setName(string name)
{
    name_ = name;
    return;
}