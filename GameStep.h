#ifndef ACTION_H
#define ACTION_H

typedef enum {
<<<<<<< HEAD

}modelEvent_t;
=======
    IDLE, WAITING_1_ACTION, WAITING_2_ACTION, WAITING_RESPONSE, PLAY_AGAIN, END, STATE_COUNT
} modelState_t;

typedef enum {
    VALID_TILE, INVALID_TILE, VALID_ACTION_0_STEP, INVALID_ACTION_0_STEP, VALID_ACTION_1_STEP, INVALID_ACTION_1_STEP, VALID_ACTION_2_STEP, INVALID_ACTION_2_STEP, WIN, LOSE, ACCEPT, DECLINE, EVENT_COUNT
} modelEvent_t;
>>>>>>> 258a82c6cb528d6814d78759d8e1914f56e2525e

class Action {
public:
    Action();
    virtual ~Action();
<<<<<<< HEAD
    virtual void doAction(gameData_t* gameData , modelEvent_t event)=0;
protected:
};

class Move:public Action
{
public:
    void doAction(gameData_t* gameData, modelEvent_t event);
private:
};    
    
class Peek:public Action
{
public:
    void doAction(gameData_t* gameData, modelEvent_t event);
private:
};  

class :public Action
{
public:
    void doAction(gameData_t* gameData, modelEvent_t event);
private:
};  


=======
    virtual void eventHandler(gameData_t gameData, modelEvent_t event) = 0;
protected:




};
>>>>>>> 258a82c6cb528d6814d78759d8e1914f56e2525e

#endif /* ACTION_H */

