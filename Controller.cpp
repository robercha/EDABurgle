#include "Controller.h"
//#include "PlayerHandle.h"
#include <new>

Controller::Controller(char* ip)
{
    this->view = new View;
    Model* model = new Model(view);
    this->userData = new userData_t;
    this->gameData = new gameData_t;
    this->userData->buttonClicked = (unsigned) button_t::NO_BUTTON;

//    Player* player1 = new Player(model, P1);
//    Player* player2 = new Player(model, P2);
//    this->playerHandle = new PlayerHandle(player1, player2);
    //this->networking = new Networking(ip);
    this->user = new userInterface(getDisplay());
    this->copyButtons();
    view->updateGraphics();

}

Controller::~Controller()
{
    //delete networking;
//    delete playerHandle;
    delete user;
    delete userData;
}

//bool Controller::connect()
//{
//    unsigned randomNumber = rand() % (MAXTIME - MINTIME + 1);
//    networking->startTimerCount();
//    randomNumber += MINTIME;
//    bool success;
//    do
//    {
//        user->getEvent(userData);
//        success = networking->tryConnecting();
//    }
//    while ((userData->event.trueEvent != ESC) && !success && (networking->getTimerCount() <= randomNumber));
//
//    if (success)
//    {
//        printf("success connecting as client");
//    }
//    else //!success
//    {
//        printf("connection failed as client");
//        //networking->writeLog("connection failed as client");
//        do
//        {
//            user->getEvent(userData);
//            success = networking->listen();
//        }
//        while ((userData->event.trueEvent != ESC) && (userData->event.trueEvent != TIMEOUT) && !success);
//
//        if (success)
//        {
//            printf("success connecting as server");
//            //networking.writeLog("connection succeed");
//        }
//        else if (userData->event.trueEvent == ESC)
//        {
//            //networking->writeLog("Game Exited");
//        }
//        else if (userData->event.trueEvent == TIMEOUT)
//        {
//            //networking->writeLog("Timeout");
//        }
//    }
//
//    return success;
//}

void
Controller::manageEvent(void)
{
    user->getEvent(userData);
    translateUserData(); //convierte button_t a modelEvent_t que son los de model FSM
    //if (playerHandle->getEvent() != NO_EVENT)
    if ((userData->buttonClicked != (unsigned) button_t::NO_BUTTON) ||
            (userData->buttonClicked != (unsigned) button_t::HOME_EXIT))
    {
        if (networkingMode && gameData->currentCharacter == 0) //Si juega online sólo entra al juego si es el turno del de esta compu
            model->analyzeAction(gameData); //Empieza la logica del juego
        else if (!networkingMode) //Sino esta jugando online los turnos son irrelevantes.
            model->analyzeAction(gameData);
    }

    //    networking->getEvent(userData);
    //    translatePackage();
    //    FSMCycle(userData->event, gameData);
    updateGraphics();

}

void Controller::updateGraphics()
{
    model->fillGraphicsData(view);
    view->updateGraphics();
}

//Controller::initGame()
//{
//    //    if (networking.getLastPacketSent == NULL) //null o noEvent, lo q sea
//    //        buildPacket(NAME);
//    switch (userData.event.trueEvent)
//    {
//        case TIMEOUT:
//            //buildPacket(networking.getLastPacketSent);
//            break;
//        case ERROR:
//            break;
//        case QUIT:
//            break;
//        case NAME:
//    }
//}

void
Controller::copyButtons()
{
    for (unsigned i = 0; i < (unsigned) button_t::BUTTON_COUNT; i++)
    {
        user->setButton(i, view->getButtonW(i), view->getButtonH(i), view->getButtonX(i), view->getButtonY(i));
    }
}

unsigned
Controller::getLastEvent()
{
    return this->userData->buttonClicked;
}

void
Controller::translateUserData()
{
    gameData->preEvent = userData->buttonClicked;
    ////    if (userData->buttonClicked == (unsigned) button_t::PASS)
    ////        playerHandle->setEvent(PASS);
    //    if ((userData->buttonClicked == (unsigned) button_t::NO_BUTTON) ||
    //            (userData->buttonClicked == (unsigned) button_t::HOME_EXIT))
    //        playerHandle->setEvent(NO_EVENT);
    ////  else
    ////        playerHandle->setEvent(ACTION);
    //    userData->buttonClicked == (unsigned) button_t::NO_BUTTON;
}

void*
Controller::getDisplay()
{
    return view->getDisplay();
}