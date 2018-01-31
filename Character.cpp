#include "Character.h"

Character::Character()
{
}

bool Character::canIUseThisTile(location_t selectedTile)
{
    bool isTileValid = false;
    isTileValid = currentTile->isTileValid(selectedTile);

    return isTileValid;
}

character_t Character::getName()
{
    return name;
}

unsigned Character::getStealthTokensQty()
{
    return stealthTokens;
}

location_t Character::getLocation()
{
    return currentTile->getCurrentLocation();
}

unsigned Character::getActionsLeft()
{
    return actions;
}

Character::Character(const Character& orig)
{
}

Character::~Character()
{
}

void Character::move()
{

}

void Character::pass()
{

}

bool Hawk::canIUseThisTile(location_t selectedTile)
{
    bool isTileValid = false;
    if (currentTile->isTileValid(selectedTile))
        isTileValid = true;
    else if (currentTile->checkDurlock(selectedTile))
        isTileValid = true;

    return isTileValid;
}

bool Raven::canIUseThisTile(location_t selectedTile)
{
    bool isTileValid = false;
    if (currentTile->isTileValid(selectedTile))
        isTileValid = true;
    else if (currentTile->isTileTwoTilesAway(selectedTile))
        isTileValid = true;

    return isTileValid;
}