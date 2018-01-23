

#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "Tile.h"
#include "Guard.h"

class Floor {
public:
    Floor();
    ~Floor();
    void randomizeFloor();
private:
    std::vector< std::vector<Tile> > tiles;

};

#endif /* FLOOR_H */

