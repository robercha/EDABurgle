#include "Guard.h"

Guard::Guard(unsigned steps, Tile* startTile, location_t patrolCard)
{
    this->steps = steps;
    this->currentTile = startTile;
    this->currentPatrolCard = patrolCard;
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

void Guard::setDestination(location_t destination)
{
    currentPatrolCard = destination;
}


Guard::~Guard()
{

}

void Guard::walk(Tile* nextStep)
{
    currentTile = nextStep;
}