#ifndef PLAYER_HANDLE_H
#define PLAYER_HANDLE_H

#include "Player.h"

class PlayerHandle {
public:
    PlayerHandle(Player*, Player*);
    void PlayerCycle(event_t, gameData_t*);
    event_t getEvent();
    void setEvent(event_t event);
    ~PlayerHandle();
private:
    event_t event;
    Player* currentPlayer;
    Player*** PlayerHandleMatrix;
};

#endif /* PLAYER_HANDLE_H */

