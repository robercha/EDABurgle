
#ifndef GUARD_H
#define GUARD_H

class Guard {
public:
    Guard();
    Guard(const Guard& orig);
    virtual ~Guard();
    walk( ?); //usa calculateRoute() tantas veces como steps tenga que dar y camina
private:
    //tile y floor
    unsigned steps;
    Tile* calculateRoute(/*destino y la lista de tiles del floor*/);
    unsigned checkAlarms(); //Devuelve numero de alarmas activadas, (chequea el camino a cada una y devuelve el minimo)???
};

#endif /* GUARD_H */

