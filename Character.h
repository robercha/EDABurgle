#ifndef CHARACTER_H
#define CHARACTER_H

#include <list>
#include "Tile.h"

class Character {
public:
    Character();
    Character(const Character& orig);
    virtual ~Character();
    void move();
    void peek();
    void pass();
    void rollDice();
    void addDiceToSafe();

    //enum class action_t {
    //    MOVE, PEEK, PASS, ADD_DICE_TO_SAFE, ROLL_DICE_FOR_SAFE, SPEND_ACTIONS_TO_ENTER, HACK_COMPUTER, USE_HACK_TOKEN,
    //    OFFER_LOOT, REQUEST_LOOT, PICK_UP_LOOT, CREATE_ALARM, SPY_PATROL_DECK, PATROL_IS_TOP, PATROL_IS_BOTTOM,
    //    PLACE_CROW_TOKEN, ACCEPT, DECLINE, PLAY_AGAIN_YES, PLAY_AGAIN_NO, ACTION_COUNT
    //};

    void addToken(token_t);
    void useToken(Tile*); //no hace falta pasarle el token porq solo se usan los hack tokens, los demas son automaticos

    bool virtual specialMove() = 0;
protected:
    Tile* currentTile;
    unsigned actions;
    unsigned stealthTokens;
    //std::list<Loot> loots;

    //loot
};

class Juicer : public Character {
public:
private:

};

class Hacker : public Character {
public:
private:

};

class Acrobat : public Character {
public:
private:

};

class Spotter : public Character {
public:
private:

};

class Hawk : public Character {
public:
private:

};

class Raven : public Character {
public:
private:
    void placeCrowToken(Tile*);

};

class Peterman : public Character {
public:
private:

};


#endif /* CHARACTER_H */

