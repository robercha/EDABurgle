#ifndef GAMESTEP_H
#define GAMESTEP_H

#include "Floor.h"
#include "Tile.h"
#include "Guard.h"
#include "Character.h"
#include "Loot.h"

typedef enum {
    IDLE, WAITING_1_ACTION, WAITING_2_ACTION, WAITING_RESPONSE, PLAY_AGAIN, END, STATE_COUNT
} modelState_t;

typedef enum {
    VALID_TILE, INVALID_TILE, A_PASS, A_FREE_MOVE, A_PAID_MOVE, A_PEEK, A_ADD_DICE_TO_SAFE,
    A_ROLL_DICE_FOR_SAFE, A_HACK_COMPUTER, A_USE_HACK_TOKEN, A_OFFER_LOOT,
    A_REQUEST_LOOT, A_PICKUP_LOOT, A_CREATE_ALARM, A_SPY_PATROL_DECK, A_PATROL_IS_TOP,
    A_PATROL_IS_BOTTOM, A_PLACE_CROW_TOKEN, WIN, LOSE, ACCEPT, DECLINE, LOOT, PATROL_CARD, EVENT_COUNT

} modelEvent_t;

typedef struct {
    bool pass;
        bool move;
        bool peek;
        bool addDice;
        bool rollDice;
        bool hackCR;
        bool useHackToken;
        bool offerLoot;
        bool requestLoot;
        bool pickupLoot;
        bool createAlarm;
        bool spyPatrolDeck;
        bool patrolIsTopBottom;
        bool placeCrowToken;
        bool acceptDecline;
}actions_t;


typedef struct gameData {
    button_t preEvent;
    modelEvent_t event;
    tileInfo_t selectedTile;
    actions_t actions;
    
} gameData_t;

class GameStep {
public:
    GameStep();
    virtual ~GameStep();
    virtual void eventHandler(gameData_t *gameData) = 0;
    modelState_t getState();
protected:
    modelState_t state;
};

class Idle : public GameStep {
public:

    Idle() {
        state = IDLE;
    };
    void eventHandler(gameData_t* gameData);
private:
};

class WaitingFirstAction : public GameStep {
public:

    WaitingFirstAction() {
        state = WAITING_1_ACTION;
    };
    void eventHandler(gameData_t *gameData);
private:
};

class WaitingSecondAction : public GameStep {
public:

    WaitingSecondAction() {
        state = WAITING_2_ACTION;
    };
    void eventHandler(gameData_t *gameData);
private:
};

class WaitingResponse : public GameStep {
public:

    WaitingResponse() {
        state = WAITING_RESPONSE;
    };
    void eventHandler(gameData_t *gameData);
private:
};

class PlayAgain : public GameStep {
public:

    PlayAgain() {
        state = PLAY_AGAIN;
    };
    void eventHandler(gameData_t *gameData);
private:
};

class End : public GameStep {
public:

    End() {
        state = END;
    };
    void eventHandler(gameData_t *gameData);
private:
};


#endif /* GAMESTEP_H */

