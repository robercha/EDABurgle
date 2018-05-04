#ifndef CHARACTER_H
#define CHARACTER_H

#include <list>
#include "Tile.h"
#include "Floor.h"
#include "Loot.h"

#define INIT_STEALTH 3
#define INIT_ACTIONS 4

typedef enum {
    JUICER, HACKER, ACROBAT, SPOTTER, HAWK, RAVEN, PETERMAN, CHARACTER_COUNT
} character_t;

class Character {
public:
    Character();
    Character(const Character& orig);
    virtual ~Character();
    void move(Tile*);
    void pass();
    void peek(Tile*);
    //virtual bool hiddenTalent() = 0;

    void addLoot(Loot& loot) {
        loots.push_back(loot);
    }
    //
    //    void addToken(tokenInfo_t token, Tile* tile) {
    //        currentTile->setToken(token, tile);
    //    }

    void setHackToken() {
        dynamic_cast<CRFingerprint*> (currentTile)->hack();
    }

    void useHackToken(tileType_t computerRoom) {
        if (computerRoom == CR_FINGERPRINT)
            dynamic_cast<CRFingerprint*> (currentTile)->useHackToken();
        else if (computerRoom == CR_MOTION)
            dynamic_cast<CRMotion*> (currentTile)->useHackToken();
        else if (computerRoom == CR_LASER)
            dynamic_cast<CRLaser*> (currentTile)->useHackToken();
    }

    void addDiceToSafe() {
        dynamic_cast<Safe*> (currentTile)->addDice();
    }

    void addDiceToSafe() {
        dynamic_cast<Safe*> (currentTile)->addDice();
    }

    bool wasCracked() {
        return dynamic_cast<Safe*> (currentTile)->isCracked();
    }

    unsigned getDieQty() {
        return dynamic_cast<Safe*> (currentTile)->getDieQty();
    }

    tileType_t whereAmI() {
        return currentTile->getTileType();
    }
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
} ;

class Juicer : public Character {
public:
    Juicer();
    void placeExtraAlarm(Tile*); //se le pasa una tile adyacente
    //    void setTile(Tile*);
private:
    //    Tile* adyacentTile;
    //    bool isTileAdyacent();

} ;

class Hacker : public Character {
public:
    Hacker();
    //bool hiddenTalent(); //no triggerea alarma

private:
    bool isPartnerOnSameTile();
    bool isFML(); //chequea si la tile es fingerprint, motion, laser


} ;

class Acrobat : public Character {
public:
    Acrobat();
    //bool hiddenTalent(); //se fija si la cant de actions es 0 y si el guardia sigue en la misma tile le quita un stealth
private:
    bool isGuardOnCurrTile();
    bool actionCount(); //se fija si la cant de actions es 0
} ;

class Spotter : public Character {
public:
    Spotter();
    //bool hiddenTalent(); //esta usa spend action
    void sendToTop(); //para los botoncitos
    void sendToBottom(std::vector<location_t>* patrolDeck);
private:
    void spendExtraAction();
} ;

class Hawk : public Character {
public:
    Hawk();
    bool canIUseThisTile(location_t, tileInfo_t*);

    //bool hiddenTalent(); //chequea si hay una pared y si la hay el peek no cuesta action
    void setTile(Tile*);
private:
    void addAction();
    bool isThereAWall(location_t);
    Tile* destiny;

} ;

class Raven : public Character {
public:
    Raven();
    void placeCrowToken(Tile*);

    //    bool canPlaceCrowToken(); //hasta dos tiles adyacentes
    //    void setTile(Tile*);
private:
    bool canIUseThisTile(location_t, tileInfo_t*);
    //Tile* tile;
} ;

class Peterman : public Character {
public:
    Peterman();
    //bool hiddenTalent(); //throw aditional dice for safe or keypad
private:
    unsigned throwAditionalDice();

} ;


#endif /* CHARACTER_H */

