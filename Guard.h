#ifndef GUARD_H
#define GUARD_H

#include "Tile.h"
#include "View.h"
#include "Floor.h"

class Guard {
public:
    Guard();
    Guard(const Guard& orig);
    virtual ~Guard();
    //walk() avanza de a uno, o al destino final, hay q verlo!!!
    void walk(); //usa calculateRoute() tantas veces como steps tenga que dar y camina
    unsigned getSpeed();
    location_t getLocation();
    location_t getDieLocation(); //no se bien que hace pero la necesitamos para graphicsData //donde esta el dado (a donde va si no suenan alarmas)/puede ser patrol_t tmb?
    //patrol_t getPatrolCard(); //para view
private:
    Tile* currentTile;
    unsigned steps;
    Tile* calculateRoute(/*destino y la lista de tiles del floor*/);
    unsigned checkAlarms(); //Devuelve numero de alarmas activadas, (chequea el camino a cada una y devuelve el minimo)???
};

#endif /* GUARD_H */

