#ifndef PLAYER_H
#define PLAYER_H

#include "Model.h"

typedef enum {
    ACTION, TURN, EVENTCOUNT
} event_t;

typedef enum {
    P1, P2, STATECOUNT
} state_t;

class Player {
public:
    Player();
    void eventHandler(event_t, gameData_t*);
    state_t getCurrentPlayer();
    ~Player();
private:
    void sendAction(event_t, gameData_t);
    void switchPlayer();
    state_t currentPlayer;
    Model* model; //ambos, player1 y player2, tienen el mismo puntero a model
};


#endif /* PLAYER_H */