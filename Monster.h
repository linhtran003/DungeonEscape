// CSCI 1300 Fall 2022
// Author: Linh Tran
// Recitation: 206 - Baljot Kaur
// Project 3 - Code Skeleton - Monster Class

#include <iostream>
using namespace std;

class Monster
{
    public:
    Monster(); // default constructor
    Monster(string name, int rating, bool status); // parameterized constructor

    // getters and setters
    int getRating();
    void setRating(int rating);
    bool getStatus();
    void setStatus(bool status);
    string getName();
    void setName(string name);

    private:
    int rating_; // the challenge level of the monster
    bool status_; // whether the monster is alive or dead
    string name_; // name of the monster
};