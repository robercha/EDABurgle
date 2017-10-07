#ifndef FSM_H
#define FSM_H

#include "Player.h"

typedef enum {ACTION, TURN, EVENTCOUNT} event_t;
typedef enum {P1, P2, STATECOUNT} state_t;
class FSM {
public:
    FSM(Player*, Player*);
    FSMCycle(event_t, gameData_t);
    virtual ~FSM();
private:
    Player* currentPlayer;
    Player** FSMMatrix;
    Player* FSMMatrix[][EVENTCOUNT];
};

#endif /* FSM_H */

