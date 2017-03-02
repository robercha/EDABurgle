#include "Controller.h"
#include "EventGenerator.h"

Controller::Controller()
{
}

Controller::Controller(const Controller& orig)
{
}

Controller::~Controller()
{
}

Controller::connect()
{
    unsigned randomNumber = rand() % (MAXTIME - MINTIME + 1);
    randomNumber += MINTIME;
    bool success;

    do
    {
        networking.getEvent(userData);
        success = networking.tryConnecting();
    }
    while (event != ESC && !success && networking.getTimerCount() <= randomNumber);

    if (success)
    {
        printf("success connecting");
    }
    else //!success
    {
        //writelog ("probamos como client") especificar ip
        do
        {
            user.getEvent(userData);
            success = networking.listen();
        }
        while (event != ESC && event != TIMEOUT && !success);

        if (success)
        {
            //show success message
            networking.writeLog("connection succeed");
        }
        else
        {
            //show error; fijarse si fue esc o error para el log
        }
    }
}

Controller::manageEvent(void)
{
    user->getEvent(userData);
    translateUserData();
    FSMCycle(userData->event, gameData);

    networking->getEvent(userData);
    translatePackage();
    FSMCycle(userData->event, gameData);

}

Controller::initGame()
{
    if (networking.getLastPacketSent == NULL) //null o noEvent, lo q sea
        buildPacket(NAME);
    switch (userData.event.trueEvent)
    {
        case TIMEOUT:
            buildPacket(networking.getLastPacketSent);
            break;
        case ERROR: ? ? ?
            break;
        case QUIT: ? ? ?
            break;
        case NAME:
    }
}

