// CSCI 1300 Fall 2022
// Author: Linh Tran
// Recitation: 206 - Baljot Kaur
// Project 3 - Code Skeleton - Inventory Class

#include <iostream>
using namespace std;

class Inventory
{
    public:
    // constructors
    Inventory();

    // keys
    int getKeys();
    void addKeys(int keys);

    // food and cookware
    int getFood();
    void addFood(int food);
    void subFood(int food);
    int getPots();
    void addPots(int pots);
    void subPots(int pots);
    int getPans();
    void addPans(int pans);
    void subPans(int pans);
    int getCauldrons();
    void addCauldrons(int caul);
    void subCauldrons(int caul);
    int getTotalCookware();

    // treasure
    int getRings();
    void addRings(int rings);
    int getNecklaces();
    void addNecklaces(int neck);
    int getBracelets();
    void addBracelets(int bracelets);
    int getCirclets();
    void addCirclets(int circlets);
    int getGoblets();
    void addGoblets(int gob);
    int getTotalTreasure();

    // gold
    int getGold();
    void addGold(int gold); // will add gold to inventory
    void subGold(int gold); // will subtract gold from inventory
    
    // weapons
    int getClubs();
    void addClubs(int clubs);
    int getSpears();
    void addSpears(int spears);
    int getRapiers();
    void addRapiers(int rapiers);
    int getAxes();
    void addAxes(int axes);
    int getLongswords();
    void addLongswords(int swords);
    int getTotalWeapons();
    int getArmor();
    void addArmor(int armor);

    private:
    int keys_;
    int gold_;

    // ingredients and cookware
    int food_;
    int pots_;
    int pans_;
    int cauldrons_;

    // treasure
    int rings_;
    int necklaces_;
    int bracelets_;
    int circlets_;
    int goblets_;
    
    // weapons and armor
    int clubs_;
    int spears_;
    int rapiers_;
    int axes_;
    int longswords_;
    int armor_;
};