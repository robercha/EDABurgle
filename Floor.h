#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <list>
#include "Tile.h"
#include "Guard.h"
//#include "View.h"

typedef enum {
    A1, A2, A3, A4, B1, B2, B3, B4, C1, C2, C3, C4, D1, D2, D3, D4, NO_PATROL
} patrol_t;

class Floor {
public:
    Floor(std::list<Tile*> &tileDeck);
    ~Floor();
    void randomizeFloor();
    void setTile(Tile* tile);
private:
    std::vector<patrol_t> patrolDeck;
    std::vector< std::vector<Tile*> > tiles;

};

#endif /* FLOOR_H */

