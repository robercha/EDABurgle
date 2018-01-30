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

Guard::Guard(const Guard& orig)
{

}

Guard::~Guard()
{

}

void
Guard::walk()
{

}