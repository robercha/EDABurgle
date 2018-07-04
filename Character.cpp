#include "Character.h"

Character::Character()
{
    this->stealthTokens = INIT_STEALTH;
    this->actions = INIT_ACTIONS;
    this->dead = false;
}

void Character::setInitialTile(Tile* tile)
{
    currentTile = tile;
}

void Character::move(Tile* tile)
{
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
        tileInfo->tile = currentTile;
    }
    else
        tileInfo->tile = NULL;

    tileInfo->twoTilesAwayTile = false;
    tileInfo->hawkWall = false;

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
}

Hacker::Hacker()
{
    name = HACKER;
}

Acrobat::Acrobat()
{
    name = ACROBAT;
}

Spotter::Spotter()
{
    name = SPOTTER;
}

Hawk::Hawk()
{
    name = HAWK;
}

Raven::Raven()
{
    name = RAVEN;
}

Peterman::Peterman()
{
    name = PETERMAN;
}

bool Hacker::isFML()
{
    bool isItFML = false;
    tileType_t tileType = currentTile->getTileType();
    if ((tileType == FINGERPRINT) || (tileType == MOTION) || (tileType == LASER))
        isItFML = true;

    return isItFML;
}

bool Hacker::hiddenTalent()
{
    bool hTalent = false;
    if (isFML())
    {
        currentTile->setAlarmToken(false);
        hTalent = true;
    }

    return hTalent;
}

void Hacker::setPartnerTile(Tile* pTile)
{
    partnerTile = pTile;
}

bool Hacker::isPartnerOnSameTile()
{
    bool same = false;
    if (partnerTile->getCurrentLocation() == this->getLocation())
        same = true;

    return same;
}

bool Acrobat::noActionsLeft()
{
    bool isItZero = false;
    if (actions == 0)
        isItZero = true;

    return isItZero;
}

bool Acrobat::hiddenTalent(Floor* currFloor)
{
    bool hTalent = true; //da true si no lo agarra el guardia; false en caso contrario
    if ((noActionsLeft())&&(this->isGuardOnCurrTile(currFloor)))
    {
        hTalent = false;
        stealthTokens--;
    }


    return hTalent;
}

bool Acrobat::isGuardOnCurrTile(Floor* currFloor)
{
    bool isGuardHere = false;
    location_t guardLocation = currFloor->getGuardLocation();
    if (guardLocation == this->getLocation())
        isGuardHere = true;

    return isGuardHere;
}

void Spotter::sendToBottom(std::vector<location_t>* patrolDeck)
{
    patrolDeck->push_back(patrolDeck->front());
    patrolDeck->erase(patrolDeck->begin());
}

//void Spotter::spendExtraAction()
//{
//    actions--;
//}

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

bool Hawk::hiddenTalent(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool canIUseHiddenTalent = false;
    if (canIUseThisTile(selectedTile, tileInfo)&&(tileInfo->hawkWall))
    {
        peek(tileInfo->tile);
        addAction();
        canIUseHiddenTalent = true;
    }

    return canIUseHiddenTalent;


}

void Hawk::addAction()
{
    actions++;
}

bool Raven::canIUseThisTile(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;
    if (currentTile->isTileValid(selectedTile, tileInfo))
    {
        isTileValid = true;
        tileInfo->twoTilesAwayTile = true;
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

bool Raven::hiddenTalent(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool canIUseHiddenTalent = false;

    if (canIUseThisTile(selectedTile, tileInfo))
        placeCrowToken(tileInfo->tile);

    return canIUseHiddenTalent;

}

void Raven::placeCrowToken(Tile* tile)
{
    tile->setCrowToken(true);
}

void Juicer::placeExtraAlarm(Tile* tile)
{
    tile->setJuicerAlarm();
}

bool Peterman::hiddenTalent()
{
    bool hTalent = false;
    if (whereAmI() == SAFE || whereAmI() == KEYPAD)
    {
        throwAdditionalDice();
        hTalent = true;
    }

    return hTalent;

}

unsigned Peterman::throwAdditionalDice()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    unsigned result = rand() % 6 + 1;


    return result;
}
