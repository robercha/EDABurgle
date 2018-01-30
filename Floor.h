#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <list>
#include "Tile.h"
#include "Guard.h"

typedef enum {
    A1, A2, A3, A4, B1, B2, B3, B4, C1, C2, C3, C4, D1, D2, D3, D4, NO_PATROL
} patrol_t;

class Floor {
public:
    Floor(std::vector<Tile*> &tileDeck, unsigned floorNumber);
    ~Floor();
    void randomizeFloor();
    void setTile(Tile* tile);
    unsigned getGuardSpeed();
    location_t getGuardLocation();
    location_t getGuardDieLocation(); //no se bien que hace pero la necesitamos para graphicsData //donde esta el dado (a donde va si no suenan alarmas)/puede ser patrol_t tmb?
    //patrol_t getPatrolCard(); //para view
private:
    void setAdjacentTiles(unsigned row, unsigned col);
    void createWalls(unsigned);
    Guard* guard;
    std::vector<patrol_t> patrolDeck;
    std::vector< std::vector<Tile*> > tiles;

};

#endif /* FLOOR_H */

