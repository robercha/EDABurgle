#include "Guard.h"

Guard::Guard()
{

}

unsigned Guard::getSpeed()
{
    return steps;
}

location_t Guard::getLocation()
{
    return this->currentTile->getCurrentLocation();
}

location_t Guard::getDestination()
{
    return currentPatrolCard;
}


Guard::~Guard()
{

}

void Guard::walk(Tile* nextStep)
{
    currentTile = nextStep;
}