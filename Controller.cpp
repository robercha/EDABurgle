#include "Controller.h"
//#include "FSM.h"
#include <new>

Controller::Controller(char* ip)
{
    this->userData = new userData_t;
    //this->networking = new Networking(ip);
    this->view = new View;    
    this->user = new userInterface(getDisplay());
    this->copyButtons();
    //this->view->menuDisplay();
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

void Controller::manageEvent(void)
{
    user->getEvent(userData);
    translateUserData();
    //FSM->FSMCycle(userData->event, gameData); //Funcion de FSM

    //    networking->getEvent(userData);
    //    translatePackage();
    //    FSMCycle(userData->event, gameData);

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

void Controller::copyButtons()
{
    for(unsigned i=0; i<BUTTON_COUNT; i++)
    {
        user->setButton(i,view->getButtonW(i),view->getButtonH(i),view->getButtonX(i),view->getButtonY(i));    
    }
}

unsigned Controller::getLastEvent()
{
    return this->userData->buttonClicked;
}

void Controller::translateUserData()
{
    
}

void* Controller::getDisplay()
{
    return view.getDisplay();
}