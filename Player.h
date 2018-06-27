#ifndef PLAYER_H
#define PLAYER_H

#include "Model.h"


typedef enum {
    ACTION, PASS, NO_EVENT, EVENTCOUNT
} event_t;

typedef enum {
    P1, P2, STATECOUNT
} state_t;

class Player {
public:
    Player();
    Player(Model* model, state_t player);
    bool eventHandler(event_t, gameData_t*);
    state_t getCurrentPlayer();
    ~Player();
private:
    void sendAction(event_t, gameData_t);
    void switchPlayer();
    state_t currentPlayer;
    Model* model; //ambos, player1 y player2, tienen el mismo puntero a model
};


#endif /* PLAYER_H */
