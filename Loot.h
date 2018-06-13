#ifndef LOOT_H
#define LOOT_H

#include "Floor.h" //por ahora se lo agrego porque lo necesitaria KeyCard

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
} ;


class Goblet : public Loot {
public:

    Goblet() {
        lootName = CURSED_GOBLET;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse();
	
private:
   // bool virgin; 
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
    bool isThereAnAlarmTile(Floor* currFloor);
    Tile* calculateRoute(); //devuelve la tile a la q deberia moverse el kitty
    Tile* currentTile; //o location_t location;
	std::vector<location_t> alarmTiles; //las locations de las alarm tiles que haya descubiertas

};

class Tiara : public Loot { //chequear al final del turno
public:

    Tiara() {
        lootName = TIARA;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(Tile*, tileInfo_t*);
    void setGuard(Guard*);
private:
    bool isGuardNearby(Tile*, tileInfo_t*);  // le agrego Tile* y tileInfo_t* para saber si esta cerca del guard
    Guard* guard;

};

class Painting : public Loot {
public:

    Painting() {
        lootName = PAINTING;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(Tile*); //si devuelve true, no puede pasar
private:
    bool onServiceDuctTile(Tile*);
    bool isSecretDoorNearby(Tile*);
};

class Mirror : public Loot { //principio del turno y cuando se mueve el personaje
public:

    Mirror() {
        lootName = MIRROR;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(Tile*); //si devuelve false, no cambia el estado de la alarma
private:
    bool deactivateLaser(Tile*); //evita que se active el flag de triggered alarm
    void decreaseActions(); //si tiene >3 actions, le resta una // Aca necesitaria tener acceso al character o que esto se haga en gameStep
};

class KeyCard : public Loot {
public:

    KeyCard() {
        lootName = KEYCARD;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(Floor*, Tile*); //poner en todos los safe tile el flag de poder crakear en false y si el jugador esta en esa safe tile cambiarlo a true
private:
	bool isOwnerOnSafeTile(Tile*);
	void disableCrackFlags(Floor*); //tendria que tener acceso a todo el floor
	void enableCrackFlag(Tile*); 


};

class Isotope : public Loot {
public:

    Isotope() {
        lootName = ISOTOPE;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(Tile*); //dispara alarma de thermo
private:
    bool onThermoTile(Tile*); //tal vez no es necesario
};

class Gemstone : public Loot {
public:

    Gemstone() {
        lootName = GEMSTONE;
        isVisible = false;
        owner = NO_PLAYER;
    };
    bool awakenCurse(Tile*,Tile*); //chequeamos que prevTile y currTile sean diferentes, y que onSameTile devuelva true
    void setPartner(/*Character**/); //solo una vez
    void setPrevTile(Tile*); //solo se setea cuando agarra el loot
private:
    bool onSameTileAsPartner(Tile*, Tile*);
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
    bool awakenCurse(Tile*); //triggerea alarma de cualquier currentTile
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
