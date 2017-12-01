#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "EventGenerator.h"
#include "View.h"

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
    userData_t* userData;
    //gameData_t* gameData;
    //graphics_t* graphics;
    //FSM* FSM;
    userInterface* user;
    //Networking* networking;
    View *view;
};


#endif /* CONTROLLER_H */

