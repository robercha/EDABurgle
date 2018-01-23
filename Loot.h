#ifndef LOOT_H
#define LOOT_H

#include "Character.h"
#include "Guard.h"

typedef enum {
    TIARA, PERSIAN_KITTY, PAINTING, MIRROR, KEYCARD, ISOTOPE, GEMSTONE, CURSED_GOBLET, CHIHUAHUA, GOLD_BAR, LOOT_COUNT
} loot_t;

class Loot {
public:
    Loot();
    Loot(const Loot& orig);
    virtual ~Loot();
    void shareLoot(Character* destiny);
    //void giveLoot(Character* destiny);
    //void takeLoot(Character* source);
    void pickUpLoot();
    void virtual specialMove() = 0;
protected:
    Character* currentCharacter;
};

class Goblet : public Loot {
public:
    void specialMove();
private:
    bool virgin;
};

class Kitty : public Loot { //chequear al principio del turno
public:
    void specialMove();
private:
    bool rollDice(); //si es 1 o 2
    bool isThereAnAlarmTile();
    Tile* calculateRoute(); //devuelve la tile a la q deberia moverse el kitty
    Tile* currentTile;
};

class Tiara : public Loot { //chequear al final del turno
public:
    void specialMove(Guard*);
private:
    bool isGuardNearby();
};

class Painting : public Loot {
public:
    bool specialMove(); //si devuelve true, no puede pasar
private:
    bool onServiceDuctTile();
    bool isSecretDoorNearby();
};

class Mirror : public Loot { //principio del turno y cuando se mueve el personaje
public:
    bool specialMove(); //si devuelve false, no cambia el estado de la alarma
private:
    bool deactivateLaser(); //evita que se active el flag de triggered alarm
    void decreaseActions(); //si tiene >3 actions, le resta una
};

class KeyCard : public Loot {
public:
    void specialMove(); //poner en todos los safe tile el flag de poder crakear en false y si el jugador esta en esa safe tile cambiarlo a true
private:
};

class Isotope : public Loot {
public:
    void specialMove(); //dispara alarma de thermo
private:
    bool onThermoTile(); //tal vez no es necesario
};

class Gemstone : public Loot {
public:
    void specialMove(); //dispara alarma de thermo
private:
    bool onSameTileAsPartner();
};



#endif /* LOOT_H */

