#include "Character.h"

Character::Character()
{
}

bool Character::canIUseThisTile(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;
    if(currentTile->isTileValid(selectedTile, tileInfo))
        isTileValid = true;
    else if(selectedTile==currentTile->getCurrentLocation())
    {    
        isTileValid=true;
        tileInfo->ownTile=true;
    }

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

bool Hawk::canIUseThisTile(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;
    if (currentTile->isTileValid(selectedTile))
        isTileValid = true;
    else if (currentTile->checkDurlock(selectedTile))
    {
        isTileValid = true;
        tileInfo->hawkWall=true;
    }
    else if(selectedTile==currentTile->getCurrentLocation())
    {    
        isTileValid=true;
        tileInfo->ownTile=true;
    }

    return isTileValid;
}

bool Raven::canIUseThisTile(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;
    if (currentTile->isTileValid(selectedTile))
    {
        isTileValid = true;
    }
    else if (currentTile->isTileTwoTilesAway(selectedTile))
    {
        isTileValid = true;
        tileInfo->twoTilesAwayTile=true;
    }
    else if(selectedTile==currentTile->getCurrentLocation())
    {    
        isTileValid=true;
        tileInfo->ownTile=true;
    }
    
    return isTileValid;
}