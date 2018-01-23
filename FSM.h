#ifndef FSM_H
#define FSM_H

#include "Player.h"

class FSM {
public:
    FSM(Player*, Player*);
    void FSMCycle(event_t, gameData_t*);
    event_t getEvent();
    void setEvent(event_t event);
    ~FSM();
private:
    event_t event;
    Player* currentPlayer;
    Player*** FSMMatrix;
    //Player* FSMMatrix[STATECOUNT][EVENTCOUNT];
};

#endif /* FSM_H */

