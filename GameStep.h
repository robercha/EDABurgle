#ifndef ACTION_H
#define ACTION_H

typedef enum {
    IDLE, WAITING_1_ACTION, WAITING_2_ACTION, WAITING_RESPONSE, PLAY_AGAIN, END, STATE_COUNT
} modelState_t;

typedef enum {
    VALID_TILE, INVALID_TILE, VALID_ACTION_0_STEP, INVALID_ACTION_0_STEP, VALID_ACTION_1_STEP, INVALID_ACTION_1_STEP, VALID_ACTION_2_STEP, INVALID_ACTION_2_STEP, WIN, LOSE, ACCEPT, DECLINE, EVENT_COUNT
} modelEvent_t;

class Action {
public:
    Action();
    virtual ~Action();
    virtual void eventHandler(gameData_t gameData, modelEvent_t event) = 0;
protected:




};

#endif /* ACTION_H */

