#ifndef GAMESTEP_H
#define GAMESTEP_H

typedef enum {
    IDLE, WAITING_1_ACTION, WAITING_2_ACTION, WAITING_RESPONSE, PLAY_AGAIN, END, STATE_COUNT
} modelState_t;

typedef enum {
    VALID_TILE, INVALID_TILE, VALID_ACTION_0_STEP, INVALID_ACTION_0_STEP, VALID_ACTION_1_STEP, INVALID_ACTION_1_STEP, VALID_ACTION_2_STEP, INVALID_ACTION_2_STEP, WIN, LOSE, ACCEPT, DECLINE, EVENT_COUNT
} modelEvent_t;


class GameStep {
public:
    GameStep();
    virtual ~GameStep();
    virtual void eventHandler(gameData_t *gameData, modelEvent_t event) = 0;
    modelState_t getState();
protected:
    modelState_t state;
};

class Idle : public GameStep {
public:

    idle() {
        state = IDLE;
    };
    void eventHandler(gameData_t *gameData, modelEvent_t event);
private:
};

class WaitingFirstAction : public GameStep {
public:

    WaitingFirstAction() {
        state = WAITING_1_ACTION;
    };
    void eventHandler(gameData_t *gameData, modelEvent_t event);
private:
};

class WaitingSecondAction : public GameStep {
public:

    WaitingSecondAction() {
        state = WAITING_2_ACTION;
    };
    void eventHandler(gameData_t *gameData, modelEvent_t event);
private:
};

class WaitingResponse : public GameStep {
public:

    WaitingResponse() {
        state = WAITING_RESPONSE;
    };
    void eventHandler(gameData_t *gameData, modelEvent_t event);
private:
};

class PlayAgain : public GameStep {
public:

    PlayAgain() {
        state = PLAY_AGAIN;
    };
    void eventHandler(gameData_t *gameData, modelEvent_t event);
private:
};

class End : public GameStep {
public:

    End() {
        state = END;
    };
    void eventHandler(gameData_t *gameData, modelEvent_t event);
private:
};


#endif /* GAMESTEP_H */

