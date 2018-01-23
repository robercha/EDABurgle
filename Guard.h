#ifndef GUARD_H
#define GUARD_H

#include "Tile.h"

class Guard {
public:
    Guard();
    Guard(const Guard& orig);
    virtual ~Guard();
    //walk() avanza de a uno, o al destino final, hay q verlo!!!
    void walk(); //usa calculateRoute() tantas veces como steps tenga que dar y camina
private:
    Tile* currentTile;
    unsigned steps;
    Tile* calculateRoute(/*destino y la lista de tiles del floor*/);
    unsigned checkAlarms(); //Devuelve numero de alarmas activadas, (chequea el camino a cada una y devuelve el minimo)???
};

#endif /* GUARD_H */

