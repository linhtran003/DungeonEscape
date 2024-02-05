#include <iostream>
#include "Inventory.h"
using namespace std;

Inventory::Inventory()
{
    keys_ = 0;
    gold_ = 100;

    // ingredients and cookware
    food_ = 0;
    pots_ = 0;
    pans_ = 0;
    cauldrons_ = 0;

    // treasure
    rings_ = 0;
    necklaces_ = 0;
    bracelets_ = 0;
    circlets_ = 0;
    goblets_ = 0;

    // weapons and armor
    clubs_ = 0;
    spears_ = 0;
    rapiers_ = 0;
    axes_ = 0;
    longswords_ = 0;
    armor_ = 0;
}

int Inventory::getKeys()
{
    return keys_;
}

void Inventory::addKeys(int keys)
{
    keys_ = keys_ + keys;
}

int Inventory::getFood()
{
    return food_;
}

void Inventory::subFood(int food)
{
    food_ = food_ - food;
    if (food_ < 0)
    {
        food_ = 0;
    }
    return;
}

void Inventory::addFood(int food)
{
    food_ = food_ + food;
}

int Inventory::getRings()
{
    return rings_;
}

void Inventory::addRings(int rings)
{
    rings_ = rings_ + rings;
}

int Inventory::getNecklaces()
{
    return necklaces_;
}

void Inventory::addNecklaces(int neck)
{
    necklaces_ = necklaces_ + neck;
}

int Inventory::getBracelets()
{
    return bracelets_;
}

void Inventory::addBracelets(int bracelets)
{
    bracelets_ = bracelets_ + bracelets;
}

int Inventory::getCirclets()
{
    return circlets_;
}

void Inventory::addCirclets(int circlets)
{
    circlets_ = circlets_ + circlets;
}

int Inventory::getGoblets()
{
    return goblets_;
}

void Inventory::addGoblets(int gob)
{
    goblets_ = goblets_ + gob;
}

int Inventory::getGold()
{
    return gold_;
}

void Inventory::addGold(int gold)
{
    gold_ = gold_ + gold;
}

void Inventory::subGold(int gold)
{
    gold_ = gold_ - gold;

    if (gold_ < 0)
    {
        gold_ = 0;
    }
}

int Inventory::getTotalTreasure()
{
    return rings_ + necklaces_ + bracelets_ + circlets_ + goblets_;
}

int Inventory::getClubs()
{
    return clubs_;
}

void Inventory::addClubs(int clubs)
{
    clubs_ = clubs_ + clubs;
}

int Inventory::getSpears()
{
    return spears_;
}

void Inventory::addSpears(int spears)
{
    spears_ = spears_ + spears;
}

int Inventory::getRapiers()
{
    return rapiers_;
}

void Inventory::addRapiers(int rapiers)
{
    rapiers_ = rapiers_ + rapiers;
}

int Inventory::getAxes()
{
    return axes_;
}

void Inventory::addAxes(int axes)
{
    axes_ = axes_ + axes;
}

int Inventory::getLongswords()
{
    return longswords_;
}

void Inventory::addLongswords(int swords)
{
    longswords_ = longswords_ + swords;
}

int Inventory::getTotalWeapons()
{
    return clubs_ + spears_ + rapiers_ + axes_ + longswords_;
}

int Inventory::getArmor()
{
    return armor_;
}

void Inventory::addArmor(int armor)
{
    armor_ = armor_ + armor;
}

int Inventory::getPots()
{
    return pots_;
}

void Inventory::addPots(int pots)
{
    pots_ = pots_ + pots;
}

void Inventory::subPots(int pots)
{
    pots_ = pots_ - pots;
}

int Inventory::getPans()
{
    return pans_;
}
void Inventory::addPans(int pans)
{
    pans_ = pans_ + pans;
}

void Inventory::subPans(int pans)
{
    pans_ = pans_ - pans;
}

int Inventory::getCauldrons()
{
    return cauldrons_;
}

void Inventory::addCauldrons(int caul)
{
    cauldrons_ = cauldrons_ + caul;
}

void Inventory::subCauldrons(int caul)
{
    cauldrons_ = cauldrons_ - caul;
}

int Inventory::getTotalCookware()
{
    return pots_ + pans_ + cauldrons_;
}