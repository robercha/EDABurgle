#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "Tile.h"
#include "Guard.h"
//#include "View.h"

typedef enum {
    A1, A2, A3, A4, B1, B2, B3, B4, C1, C2, C3, C4, D1, D2, D3, D4, NO_PATROL
} patrol_t;

class Floor {
public:
    Floor();
    ~Floor();
    //void randomizeFloor();
    void randomizeFloor();
private:
    std::vector< std::vector<Tile> > tiles;
    std::vector<patrol_t> patrolDeck;

};

#endif /* FLOOR_H */

