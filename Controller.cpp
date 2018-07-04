#include "Controller.h"
#include <new>

Controller::Controller(char* ip)
{
    this->view = new View;
    this->gameData = new gameData_t;
    this->model = new Model(gameData);
    this->userData = new userData_t;

    this->view->graphicsData = new graphicsData_t;
    this->userData->buttonClicked = (unsigned) button_t::NO_BUTTON;

    this->user = new userInterface(getDisplay());
    this->copyButtons();
    this->networkingMode = false;

    model->initGraphicsData(view, gameData);

    view->updateGraphics();


}

Controller::~Controller()
{
    //delete networking;
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


    if ((userData->buttonClicked != (unsigned) (button_t::NO_BUTTON)) &&
            (userData->buttonClicked != (unsigned) button_t::HOME_EXIT))
    {
        if (networkingMode && gameData->currentCharacter == PLAYER1) //Si juega online sólo entra al juego si es el turno del de esta compu
            model->analyzeAction(gameData); //Empieza la logica del juego
        else if (!networkingMode) //Si no esta jugando online los turnos son irrelevantes.
            model->analyzeAction(gameData);
    }

    //    networking->getEvent(userData);
    //    translatePackage();
    //    FSMCycle(userData->event, gameData);
    if (gameData->preEvent != button_t::NO_BUTTON)
    {
        model->fillGraphicsData(view, gameData);
        view->updateGraphics();
    }
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
    gameData->preEvent = (button_t) userData->buttonClicked;
}

void*
Controller::getDisplay()
{
    return view->getDisplay();
}