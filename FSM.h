#ifndef FSM_H
#define FSM_H

#include "Player.h"

class FSM {
public:
    void FSM(Player*, Player*);
    void FSMCycle(event_t, gameData_t*);
    virtual ~FSM();
private:
    Player* currentPlayer;
    Player** FSMMatrix;
    //Player* FSMMatrix[STATECOUNT][EVENTCOUNT];
};

#endif /* FSM_H */

