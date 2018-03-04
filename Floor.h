#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <list>
#include "Tile.h"
#include "Guard.h"

class Floor {
public:
    Floor(std::vector<Tile*> &tileDeck, unsigned floorNumber);
    ~Floor();
    void randomizeFloor();
    void setTile(Tile* tile);
    bool crack(unsigned); //se fija si las tiles son crackeadas
    unsigned getGuardSpeed();
    location_t getGuardLocation();
    location_t getGuardDieLocation(); //no se bien que hace pero la necesitamos para graphicsData //donde esta el dado (a donde va si no suenan alarmas)/puede ser patrol_t tmb?
    std::vector< std::vector<Tile*> >& getDeck();
    //patrol_t getPatrolCard(); //para view
private:
    unsigned floorNumber;
    void createPatrolDeck();
    void setAdjacentTiles(unsigned row, unsigned col);
    void createWalls(unsigned);
    Tile* calculateRoute(Tile* destination);
    Tile* minDistance();
    void unvisitTiles();
    Guard* guard;
    std::vector<patrol_t> patrolDeck;
    std::vector<patrol_t> trashedPatrolDeck;
    std::vector< std::vector<Tile*> > tiles;

};

#endif /* FLOOR_H */

