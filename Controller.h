#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "EventGenerator.h"
#include "View.h"
#include "PlayerHandle.h"

class Controller {
public:
    Controller(char* ip);
    void manageEvent(void); //Recibe input de usuario (y networking) y llama a fsm
    //  bool connect(void);
    void updateGraphics(void);
    bool initGame(void);
    //  bool buildPacket(packet_t packet); //enum
    void translateUserData(void); //traduce input de usuario a eventos de FSM
    //  void translatePackage(void);
    void copyButtons(); //Le da a EventGenerator el arreglo de botones generado en graphics.
    unsigned getLastEvent();
    ~Controller();
private:
    void* getDisplay();
    userData_t* userData;
    gameData_t* gameData;
    //graphics_t* graphics;
    PlayerHandle* playerHandle;
    userInterface* user;
    //Networking* networking;
    View *view;
};


#endif /* CONTROLLER_H */

