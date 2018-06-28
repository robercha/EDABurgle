#ifndef GAMESTEP_H
#define GAMESTEP_H

#include <string>
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
    A_PATROL_IS_BOTTOM, A_PLACE_CROW_TOKEN, WIN, LOSE, ACCEPT, DECLINE, A_LOOT, A_PATROL_CARD, EVENT_COUNT

} modelEvent_t;

struct gamePointers_t {
    std::vector<Floor*> floors;
    std::vector<Guard*> guards; //esto lo tiene floor
    std::vector<Character*> characters; //Los dos characters en juego
    Character* currentCharacter;
} ;

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
} actions_t;

typedef struct gameData {
    unsigned currentCharacter;
    unsigned actionsLeft;
    button_t preEvent;
    modelEvent_t event;
    tileInfo_t selectedTile;
    actions_t actions;
    unsigned loot; //el loot que se toco
    unsigned patrolDeck;
    unsigned diceResult[5];
    std::string message;
} gameData_t;

class GameStep {
public:
    GameStep();
    virtual ~GameStep();
    virtual void eventHandler(gameData_t* , gamePointers_t* ) = 0;

    modelState_t getState() {
        return this->state;
    };

    std::string& getMessage() {
        return this->message;
    }
    void drawLoot(gamePointers_t*);

    virtual void enableActions(gameData_t*, gamePointers_t*) = 0;
protected:
    modelState_t state;
    bool hasCharLostLife();
    bool isGameWon();
    bool isGameLost();
    virtual void showInvalidTileMessage(gameData_t*) = 0; //no tiene acceso a view, deberia hacerlo controller
    void showUsedPatrolCards();
    void faceConsequences();
    std::string message;
} ;

class Idle : public GameStep {
public:

    Idle() {
        state = IDLE;
    };
    void eventHandler(gameData_t *gameData, gamePointers_t* gamePointers);
    void enableActions(gameData_t*, gamePointers_t*);
    void showInvalidTileMessage(gameData_t*);
private:
    ;
} ;

class WaitingFirstAction : public GameStep {
public:

    WaitingFirstAction() {
        state = WAITING_1_ACTION;
    };
    void eventHandler(gameData_t *gameData, gamePointers_t* gamePointers);
    void enableActions(gameData_t*, gamePointers_t*);
    void showInvalidTileMessage(gameData_t*);
private:
} ;

class WaitingSecondAction : public GameStep {
public:

    WaitingSecondAction() {
        state = WAITING_2_ACTION;
    };
    void eventHandler(gameData_t *gameData, gamePointers_t* gamePointers);
    void enableActions(gameData_t*, gamePointers_t*);
    void showInvalidTileMessage(gameData_t*);
private:
} ;

class WaitingResponse : public GameStep {
public:

    WaitingResponse() {
        state = WAITING_RESPONSE;
    };
    void eventHandler(gameData_t *gameData, gamePointers_t* gamePointers);
    void enableActions(gameData_t*, gamePointers_t*);
    void showInvalidTileMessage(gameData_t*);
private:
} ;

class PlayAgain : public GameStep {
public:

    PlayAgain() {
        state = PLAY_AGAIN;
    };
    void eventHandler(gameData_t *gameData, gamePointers_t* gamePointers);
    void enableActions(gameData_t*, gamePointers_t*);
    void showInvalidTileMessage(gameData_t*);
private:
} ;

class End : public GameStep {
public:

    End() {
        state = END;
    };
    void eventHandler(gameData_t *gameData, gamePointers_t* gamePointers);
    void enableActions(gameData_t*, gamePointers_t*);
    void showInvalidTileMessage(gameData_t*);
private:
} ;


#endif /* GAMESTEP_H */

