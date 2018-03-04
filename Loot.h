#ifndef LOOT_H
#define LOOT_H

#include "Guard.h"

typedef enum {
    TIARA, PERSIAN_KITTY, PAINTING, MIRROR, KEYCARD, ISOTOPE, GEMSTONE, CURSED_GOBLET, CHIHUAHUA, GOLD_BAR, LOOT_COUNT
} loot_t;

typedef enum {
    YOU, PARTNER, NO_PLAYER
} player_t;

class Loot {
public:
    Loot();
    Loot(const Loot& orig);
    virtual ~Loot();
    void shareLoot(/*Character* destiny*/); //esto lo haria ahora character
    //void giveLoot(Character* destiny);
    //void takeLoot(Character* source);
    void pickUpLoot();
    bool virtual awakenCurse() = 0;
    loot_t getLootName();

    player_t getOwner() {
        return owner;
    }

    bool isLootVisible() {
        return isVisible;
    }
protected:
    bool isVisible;
    loot_t lootName;
    player_t owner;
};

class Goblet : public Loot {
public:

    Goblet() {
        lootName = CURSED_GOBLET;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse();
private:
    bool virgin;
};

class Kitty : public Loot { //chequear al principio del turno
public:

    Kitty() {
        lootName = PERSIAN_KITTY;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse();
    void setTile();
private:
    bool rollDice(); //si es 1 o 2
    bool isThereAnAlarmTile();
    Tile* calculateRoute(); //devuelve la tile a la q deberia moverse el kitty
    Tile* currentTile; //o location_t location;
};

class Tiara : public Loot { //chequear al final del turno
public:

    Tiara() {
        lootName = TIARA;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse();
    void setGuard(Guard*);
private:
    bool isGuardNearby();
    Guard* guard;

};

class Painting : public Loot {
public:

    Painting() {
        lootName = PAINTING;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(); //si devuelve true, no puede pasar
private:
    bool onServiceDuctTile();
    bool isSecretDoorNearby();
};

class Mirror : public Loot { //principio del turno y cuando se mueve el personaje
public:

    Mirror() {
        lootName = MIRROR;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(); //si devuelve false, no cambia el estado de la alarma
private:
    bool deactivateLaser(); //evita que se active el flag de triggered alarm
    void decreaseActions(); //si tiene >3 actions, le resta una
};

class KeyCard : public Loot {
public:

    KeyCard() {
        lootName = KEYCARD;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(); //poner en todos los safe tile el flag de poder crakear en false y si el jugador esta en esa safe tile cambiarlo a true
private:
};

class Isotope : public Loot {
public:

    Isotope() {
        lootName = ISOTOPE;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(); //dispara alarma de thermo
private:
    bool onThermoTile(); //tal vez no es necesario
};

class Gemstone : public Loot {
public:

    Gemstone() {
        lootName = GEMSTONE;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(); //chequeamos que prevTile y currTile sean diferentes, y que onSameTile devuelva true
    void setPartner(/*Character**/); //solo una vez
    void setPrevTile(Tile*); //solo se setea cuando agarra el loot
private:
    bool onSameTileAsPartner();
    //Character* partner;
    Tile* previousTile;
};

class Chihuahua : public Loot { //chequear al principio del turno
public:

    Chihuahua() {
        lootName = CHIHUAHUA;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(); //triggerea alarma de cualquier currentTile
private:
    bool rollDice(); //si es 6
};

class GoldBar : public Loot { //quien lleve un goldbar debe ser diferente a quien lleve el otro
public:

    GoldBar() {
        lootName = GOLD_BAR;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(); //clonarse y crear GoldBar2
    //   Loot getGoldBar();
private:
    //  Loot goldBar2;

};

#endif /* LOOT_H */

