#ifndef CHARACTER_H
#define CHARACTER_H

#include <list>
#include "Tile.h"
#include "Floor.h"
#include "Loot.h"

typedef enum {
    JUICER, HACKER, ACROBAT, SPOTTER, HAWK, RAVEN, PETERMAN
} character_t;

class Character {
public:
    Character();
    Character(const Character& orig);
    virtual ~Character();
    void move();
    //void peek();          esto esta en tile
    void pass();
    virtual bool hiddenTalent() = 0;
    virtual bool canIUseThisTile(location_t, tileInfo_t*); //de cada character y le pregunta a la tile sus adyacentes
    character_t getName();
    unsigned getStealthTokensQty();
    location_t getLocation();
    unsigned getActionsLeft();
    loot_t getLootName();
protected:
    character_t name;
    Tile* currentTile;
    unsigned actions;
    unsigned stealthTokens;
    std::vector<Loot*> loots;
};

class Juicer : public Character {
public:

    Juicer() {
        name = JUICER;
    };
    bool hiddenTalent(); //coloca alarma triggereada si isTileAdyacent()==true
    void setTile(Tile*);
private:
    Tile* adyacentTile;
    bool isTileAdyacent();

};

class Hacker : public Character {
public:

    Hacker() {
        name = HACKER;
    };
    bool hiddenTalent(); //no triggerea alarma

private:
    bool isPartnerOnSameTile();
    bool isFML(); //chequea si la tile es fingerprint, motion, laser


};

class Acrobat : public Character {
public:

    Acrobat() {
        name = ACROBAT;
    };
    bool hiddenTalent(); //se fija si la cant de actions es 0 y si el guardia sigue en la misma tile le quita un stealth
private:
    bool isGuardOnCurrTile();
    bool actionCount(); //se fija si la cant de actions es 0
};

class Spotter : public Character {
public:

    Spotter() {
        name = SPOTTER;
    };
    bool hiddenTalent(); //esta usa spend action
    void sendToTop(); //para los botoncitos
    void sendToBottom(std::vector<patrol_t>* patrolDeck);
private:
    void spendExtraAction();
};

class Hawk : public Character {
public:

    Hawk() {
        name = HAWK;
    };
    bool canIUseThisTile(location_t, tileInfo_t*);

    bool hiddenTalent(); //chequea si hay una pared y si la hay el peek no cuesta action
    void setTile(Tile*);
private:
    void addAction();
    bool isThereAWall(location_t);
    Tile* destiny;

};

class Raven : public Character {
public:

    Raven() {
        name = RAVEN;
    };
    bool canIUseThisTile(location_t, tileInfo_t*);
    bool canPlaceCrowToken(); //hasta dos tiles adyacentes
    bool hiddenTalent(); //place crow token
    void setTile(Tile*);
private:
    void placeCrowToken();
    Tile* tile;
};

class Peterman : public Character {
public:

    Peterman() {
        name = PETERMAN;
    };
    bool hiddenTalent(); //throw aditional dice for safe or keypad
private:
    unsigned throwAditionalDice();

};


#endif /* CHARACTER_H */

