#ifndef GUARD_H
#define GUARD_H

#include "Tile.h"
#include "View.h"

#define DISCARDED_PATROL_COUNT 6

typedef enum {
    A1, B1, C1, D1,
    A2, B2, C2, D2,
    A3, B3, C3, D3,
    A4, B4, C4, D4,
    PATROL_COUNT,
    NO_PATROL
} patrol_t;

class Guard {
public:
    Guard(unsigned, Tile*, location_t);
    virtual ~Guard();
    void walk(Tile*); //usa calculateRoute() tantas veces como steps tenga que dar y camina
    unsigned getSpeed();
    location_t getLocation();
    location_t getDestination();
    location_t getPatrolCard();

    void setDestination(location_t);
    void setPatrolCard(location_t newPatrolCard);

    void toggleGuard() {
        isActive = ~isActive;
    }

    bool getGuardState() {
        return isActive;
    }

    void increaseSpeed() 
    {
        if (steps < 6)
            steps++;
    }

    void decreaseSpeed(unsigned minimunSpeed) {
        if (steps > minimunSpeed)
            steps--;
    }

    tileType_t getRoomType() {
        return this->currentTile->getTileType();
    }


private:
    Tile* currentTile;
    location_t currentPatrolCard;
    location_t destination;
    unsigned steps;
    bool isActive;
} ;

#endif /* GUARD_H */

