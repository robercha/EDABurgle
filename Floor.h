

#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "Tile.h"
#include "Guard.h"

class Floor {
public:
    Floor();
    ~Floor();
<<<<<<< HEAD
    //void randomizeFloor();
=======
    void randomizeFloor();
>>>>>>> a87a25276e785be9552dddfaf320b8d808bd69b4
private:
    std::vector< std::vector<Tile> > tiles;

};

#endif /* FLOOR_H */

