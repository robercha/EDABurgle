#ifndef ACTION_H
#define ACTION_H

typedef enum {

}modelEvent_t;

class Action {
public:
    Action();
    virtual ~Action();
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



#endif /* ACTION_H */

