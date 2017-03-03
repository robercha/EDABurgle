#include "EventGenerator.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
public:
    Controller();
    void manageEvent(void);
    bool connect(void);
    void updateGraphics(void);
    bool initGame(void);
    bool buildPacket(packet_t packet); //enum
    translateUserData(void);
    translatePackage(void);
    ~Controller();
private:
    userData_t* userData;
    gameData_t* gameData;
    graphics_t* graphics;
    FSM* FSM;
    EventGenerator* user;
    EventGenerator* networking;
}


#endif /* CONTROLLER_H */

