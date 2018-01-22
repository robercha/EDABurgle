#include "Controller.h"
//#include "FSM.h"
#include <new>

void fillGraphicsData(View&view);

Controller::Controller(char* ip)
{
    this->userData = new userData_t;
    this->userData->buttonClicked = (unsigned)button_t::NO_BUTTON;
    //this->networking = new Networking(ip);
    this->view = new View;    
    this->user = new userInterface(getDisplay());
    this->copyButtons();
    fillGraphicsData(*view);
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
    for(unsigned i=0; i<(unsigned)button_t::BUTTON_COUNT; i++)
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
    return view->getDisplay();
}


void
fillGraphicsData(View &view)
{
    view.graphicsData->gameLost = true;
    view.graphicsData->gameWon = true;
    view.graphicsData->players[0].character = character_t::RAVEN;
    view.graphicsData->players[0].stealthTokens = 3;
    view.graphicsData->players[0].location = location_t::D4F3;
    view.graphicsData->players[0].actionsLeft = 4;
    view.graphicsData->players[1].character = character_t::JUICER;
    view.graphicsData->players[1].stealthTokens = 2;
    view.graphicsData->players[1].location = location_t::B3F2;
    view.graphicsData->players[1].actionsLeft = 3;

    view.graphicsData->guards[0].location = location_t::B2F1;
    view.graphicsData->guards[1].location = location_t::A2F2;
    view.graphicsData->guards[2].location = location_t::D4F3;
    view.graphicsData->guards[0].patrolDeck = patrol_t::C1;
    view.graphicsData->guards[1].patrolDeck = patrol_t::B3;
    view.graphicsData->guards[2].patrolDeck = patrol_t::A1;
    view.graphicsData->guards[0].movements = 2;
    view.graphicsData->guards[1].movements = 4;
    view.graphicsData->guards[2].movements = 6;
    view.graphicsData->guards[0].guardDie = location_t::B2F1;
    view.graphicsData->guards[1].guardDie = location_t::C2F2;
    view.graphicsData->guards[2].guardDie = location_t::A4F3;


    for (unsigned i = 0; i < 48; i++)
    {
        view.graphicsData->tiles[i].iAm = room_t::ROOMBACK;
        view.graphicsData->tiles[i].goldBarOnTheLoose = false;
    }
    view.graphicsData->tiles[46].goldBarOnTheLoose = true;

    view.graphicsData->tiles[0].iAm = room_t::LAVATORY;
    view.graphicsData->tiles[0].combinationNumber = 1;
    view.graphicsData->tiles[0].howManyStealthTokens = 1;
    view.graphicsData->tiles[1].iAm = room_t::CR_FINGERPRINT;
    view.graphicsData->tiles[1].combinationNumber = 2;
    view.graphicsData->tiles[1].howManyHackTokens = 6;
    view.graphicsData->tiles[4].iAm = room_t::CR_LASER;
    view.graphicsData->tiles[4].combinationNumber = 3;
    view.graphicsData->tiles[5].iAm = room_t::CR_MOTION;
    view.graphicsData->tiles[5].combinationNumber = 4;
    view.graphicsData->tiles[6].iAm = room_t::DEADBOLT;
    view.graphicsData->tiles[6].combinationNumber = 5;
    view.graphicsData->tiles[7].iAm = room_t::ATRIUM;
    view.graphicsData->tiles[7].combinationNumber = 6;
    view.graphicsData->tiles[20].iAm = room_t::DETECTOR;
    view.graphicsData->tiles[20].combinationNumber = 1;
    view.graphicsData->tiles[22].iAm = room_t::FINGERPRINT;
    view.graphicsData->tiles[22].combinationNumber = 2;
    view.graphicsData->tiles[23].iAm = room_t::FOYER;
    view.graphicsData->tiles[23].combinationNumber = 3;
    view.graphicsData->tiles[26].iAm = room_t::KEYPAD;
    view.graphicsData->tiles[26].combinationNumber = 4;
    view.graphicsData->tiles[27].iAm = room_t::LABORATORY;
    view.graphicsData->tiles[27].combinationNumber = 5;
    view.graphicsData->tiles[29].iAm = room_t::LASER;
    view.graphicsData->tiles[29].combinationNumber = 6;
    view.graphicsData->tiles[30].iAm = room_t::LAVATORY;
    view.graphicsData->tiles[30].combinationNumber = 1;
    view.graphicsData->tiles[32].iAm = room_t::MOTION;
    view.graphicsData->tiles[32].combinationNumber = 2;
    view.graphicsData->tiles[34].iAm = room_t::ROOMBACK;
    view.graphicsData->tiles[34].combinationNumber = 3;
    view.graphicsData->tiles[35].iAm = room_t::SAFE;
    view.graphicsData->tiles[35].combinationNumber = 4;
    view.graphicsData->tiles[37].iAm = room_t::SECRETDOOR;
    view.graphicsData->tiles[37].combinationNumber = 5;
    view.graphicsData->tiles[39].iAm = room_t::SERVICEDUCT;
    view.graphicsData->tiles[39].combinationNumber = 6;
    view.graphicsData->tiles[32].iAm = room_t::MOTION;
    view.graphicsData->tiles[32].combinationNumber = 2;
    view.graphicsData->tiles[34].iAm = room_t::ROOMBACK;
    view.graphicsData->tiles[34].combinationNumber = 3;
    view.graphicsData->tiles[35].iAm = room_t::SAFE;
    view.graphicsData->tiles[35].combinationNumber = 4;
    view.graphicsData->tiles[37].iAm = room_t::SECRETDOOR;
    view.graphicsData->tiles[37].combinationNumber = 5;
    view.graphicsData->tiles[39].iAm = room_t::SERVICEDUCT;
    view.graphicsData->tiles[39].combinationNumber = 6;
    view.graphicsData->tiles[41].iAm = room_t::STAIRS;
    view.graphicsData->tiles[41].combinationNumber = 2;
    view.graphicsData->tiles[43].iAm = room_t::THERMO;
    view.graphicsData->tiles[43].combinationNumber = 3;
    view.graphicsData->tiles[44].iAm = room_t::WALKWAY;
    view.graphicsData->tiles[44].combinationNumber = 4;
    view.graphicsData->tiles[46].iAm = room_t::FOYER;
    view.graphicsData->tiles[46].combinationNumber = 5;
    view.graphicsData->tiles[47].iAm = room_t::SAFE;
    view.graphicsData->tiles[47].combinationNumber = 6;

    for (unsigned i = 0; i < 3; i++)
    {
        view.graphicsData->loots[i] = loot_t::TIARA;
    }
    view.graphicsData->currentCardSelected = button_t::A1F1;
    for (unsigned i = 0; i < 8; i++)
        view.graphicsData->tiles[(int) button_t::A2F1].tokens[i] = true;
    view.graphicsData->tiles[(int) button_t::A2F1].tokens[1] = false;

    for (unsigned i = 0; i < 8; i++)
        view.graphicsData->tiles[(int) button_t::A1F1].tokens[i] = true;

    //view.graphicsData->currentCardSelected = button_t::NOBUTTON;
}