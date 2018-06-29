#include "Guard.h"

Guard::Guard(unsigned steps, Tile* startTile, location_t patrolCard)
{
    this->steps = steps;
    this->currentTile = startTile;
    this->currentPatrolCard = patrolCard;
    this->destination = patrolCard;
    this->isActive = false;
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
    return destination;
}

location_t Guard::getPatrolCard()
{
    return currentPatrolCard;
}

void Guard::setDestination(location_t destination)
{
    this->destination = destination;
}

void Guard::setPatrolCard(location_t newPatrolCard)
{
    currentPatrolCard = newPatrolCard;
}


Guard::~Guard()
{

}

void Guard::walk(Tile* nextStep)
{
    currentTile = nextStep;
}