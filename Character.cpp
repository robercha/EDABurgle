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

Character::Character(const Character& orig)
{
}

Character::~Character()
{
}

void
Character::move()
{

}

void
Character::pass()
{

}
