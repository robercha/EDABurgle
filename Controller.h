#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "EventGenerator.h"
#include "View.h"
#include "FSM.h"

class Controller {
public:
    Controller(char* ip);
    void manageEvent(void);
    //  bool connect(void);
    void updateGraphics(void);
    bool initGame(void);
    //  bool buildPacket(packet_t packet); //enum
    void translateUserData(void);
    //  void translatePackage(void);
    void copyButtons();
    unsigned getLastEvent();
    ~Controller();
private:
    void* getDisplay();
    userData_t* userData;
    gameData_t* gameData;
    //graphics_t* graphics;
    FSM* fsm;
    userInterface* user;
    //Networking* networking;
    View *view;
};


#endif /* CONTROLLER_H */

