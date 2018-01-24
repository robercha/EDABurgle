

#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <list>
#include "Tile.h"
#include "Guard.h"

class Floor {
public:
    Floor(std::list<Tile*> &tileDeck);
    ~Floor();
    void randomizeFloor();
    void setTile(Tile* tile);
private:
    std::vector< std::vector<Tile*> > tiles;

};

#endif /* FLOOR_H */

