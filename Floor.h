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
    void crack(unsigned, location_t, gameData_t*); //se fija si las tiles son crackeadas
    unsigned getGuardSpeed();
    location_t getGuardLocation();
    void moveGuard();
    location_t getGuardDieLocation(); //no se bien que hace pero la necesitamos para graphicsData //donde esta el dado (a donde va si no suenan alarmas)/puede ser patrol_t tmb?
    std::vector< std::vector<Tile*> >& getDeck();
    //patrol_t getPatrolCard(); //para view
private:
    unsigned floorNumber;
    void createPatrolDeck();
    bool takePatrolCard();
    void setAdjacentTiles(unsigned row, unsigned col);
    void createWalls(unsigned);
    Tile* setDistance2Guard();
    Tile* nextStep(Tile* destination);
    Tile* minDistance();
    void unvisitTiles();
    Guard* guard;
    bool compare(Tile*, Tile*);
    std::vector<location_t> patrolDeck;
    std::vector<location_t> trashedPatrolDeck;
    std::vector< std::vector<Tile*> > tiles;

};

#endif /* FLOOR_H */

