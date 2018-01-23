#ifndef PLAYER_H
#define PLAYER_H

//#include "Model.h"


/*SOLO PARA PROBAR FSM SIN MODEL*/

typedef struct gameData
{
    unsigned action;
}gameData_t;
/*------------------------------*/



typedef enum {
    ACTION, SWITCH_PLAYER, NO_EVENT, EVENTCOUNT
} event_t;

typedef enum {
    P1, P2, STATECOUNT
} state_t;

class Player {
public:
    Player();
    Player(/*Model* model*/);
    void eventHandler(event_t, gameData_t*);
    state_t getCurrentPlayer();
    ~Player();
private:
    void sendAction(event_t, gameData_t);
    void switchPlayer();
    state_t currentPlayer;
    //Model* model; //ambos, player1 y player2, tienen el mismo puntero a model
};


#endif /* PLAYER_H */