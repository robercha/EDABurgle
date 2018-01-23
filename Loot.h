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
    bool virtual specialMove() = 0;
protected:
    Character* currentCharacter;
};

class Goblet : public Loot {
public:
    bool specialMove();
private:
    bool virgin;
};

class Kitty : public Loot { //chequear al principio del turno
public:
    bool specialMove();
private:
    bool rollDice(); //si es 1 o 2
    bool isThereAnAlarmTile();
    Tile* calculateRoute(); //devuelve la tile a la q deberia moverse el kitty
    Tile* currentTile;
};

class Tiara : public Loot { //chequear al final del turno
public:
    bool specialMove();
    void setGuard(Guard*);
private:
    bool isGuardNearby();
    Guard* guard;

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
    bool specialMove(); //poner en todos los safe tile el flag de poder crakear en false y si el jugador esta en esa safe tile cambiarlo a true
private:
};

class Isotope : public Loot {
public:
    bool specialMove(); //dispara alarma de thermo
private:
    bool onThermoTile(); //tal vez no es necesario
};

class Gemstone : public Loot {
public:
    bool specialMove(); //chequeamos que prevTile y currTile sean diferentes, y que onSameTile devuelva true
    void setPartner(Character*); //solo una vez
    void setPrevTile(Tile*); //solo se setea cuando agarra el loot
private:
    bool onSameTileAsPartner();
    Character* partner;
    Tile* previousTile;
};

class Chihuahua : public Loot { //chequear al principio del turno
public:
    bool specialMove(); //triggerea alarma de cualquier currentTile
private:
    bool rollDice(); //si es 6
};

class GoldBar : public Loot { //quien lleve un goldbar debe ser diferente a quien lleve el otro
public:
    bool specialMove(); //clonarse y crear GoldBar2
    //   Loot getGoldBar();
private:
    //  Loot goldBar2;

};

#endif /* LOOT_H */

