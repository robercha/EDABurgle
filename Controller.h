#include "EventGenerator.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

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
    ~Controller();
private:
    userData_t* userData;
    gameData_t* gameData;
    graphics_t* graphics;
    FSM* FSM;
    userInterface* user;
    //Networking* networking;
    View *view;
};


#endif /* CONTROLLER_H */

