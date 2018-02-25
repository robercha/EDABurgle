#include "Character.h"

void Character::move(Tile* tile)
{
    //reveal y todo eso
    tile->reveal();
    this->currentTile = tile;
    actions--;
}

void Character::peek(Tile* tile)
{
    tile->reveal();
    actions--;
}

bool Character::canIUseThisTile(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;
    if (currentTile->isTileValid(selectedTile, tileInfo))
        isTileValid = true;
    else if (selectedTile == currentTile->getCurrentLocation())
    {
        isTileValid = true;
        tileInfo->ownTile = true;
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

Character::~Character()
{
}

void Character::pass()
{
    actions = INIT_ACTIONS;
}

Juicer::Juicer()
{
    name = JUICER;
    stealthTokens = INIT_STEALTH;
    actions = INIT_ACTIONS;
}

Hacker::Hacker()
{
    name = HACKER;
    stealthTokens = INIT_STEALTH;
    actions = INIT_ACTIONS;
}

Acrobat::Acrobat()
{
    name = ACROBAT;
    stealthTokens = INIT_STEALTH;
    actions = INIT_ACTIONS;
}

Spotter::Spotter()
{
    name = SPOTTER;
    stealthTokens = INIT_STEALTH;
    actions = INIT_ACTIONS;
}

Hawk::Hawk()
{
    name = HAWK;
    stealthTokens = INIT_STEALTH;
    actions = INIT_ACTIONS;
}

Raven::Raven()
{
    name = RAVEN;
    stealthTokens = INIT_STEALTH;
    actions = INIT_ACTIONS;
}

Peterman::Peterman()
{
    name = PETERMAN;
    stealthTokens = INIT_STEALTH;
    actions = INIT_ACTIONS;
}

bool Hawk::canIUseThisTile(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;
    if (currentTile->isTileValid(selectedTile, tileInfo))
        isTileValid = true;
    else if (currentTile->checkDurlock(selectedTile))
    {
        isTileValid = true;
        tileInfo->hawkWall = true;
    }
    else if (selectedTile == currentTile->getCurrentLocation())
    {
        isTileValid = true;
        tileInfo->ownTile = true;
    }

    return isTileValid;
}

bool Raven::canIUseThisTile(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;
    if (currentTile->isTileValid(selectedTile, tileInfo))
    {
        isTileValid = true;
    }
    else if (currentTile->isTileTwoTilesAway(selectedTile))
    {
        isTileValid = true;
        tileInfo->twoTilesAwayTile = true;
    }
    else if (selectedTile == currentTile->getCurrentLocation())
    {
        isTileValid = true;
        tileInfo->ownTile = true;
    }

    return isTileValid;
}

void Raven::placeCrowToken(Tile* tile)
{
    tile->setToken(CROWTOKEN, NULL);
}

void Juicer::placeExtraAlarm(Tile* tile)
{
    tile->setJuicerAlarm();
}
