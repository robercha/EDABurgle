#include "PlayerHandle.h"

PlayerHandle::PlayerHandle(Player* player1, Player* player2)
{
    Player * PlayerHandleTempMatrix[STATECOUNT][EVENTCOUNT] = //Creamos matriz temporal para luego copiar a la final
    {
        //ACTION  SWITCH_PLAYER
        {player1, player2}, //Player 1
        {player2, player1}, //Player 2
    };

    PlayerHandleMatrix = new Player**[STATECOUNT];
    for (int i = 0; i < STATECOUNT; i++)
    {
        PlayerHandleMatrix[i] = new Player*[EVENTCOUNT]; //Alocamos las columnas

        for (int j = 0; j < EVENTCOUNT; j++)
        {
            PlayerHandleMatrix[i][j] = PlayerHandleTempMatrix[i][j]; //copiamos celda a celda la matriz temporal
        }
    }

    currentPlayer = player1; //SOLO DE PRUEBA;
    event = NO_EVENT;
}

void
PlayerHandle::PlayerCycle(event_t event, gameData_t *gameData)
{
    currentPlayer->eventHandler(event, gameData);
    currentPlayer = PlayerHandleMatrix[currentPlayer->getCurrentPlayer()][event];
}

PlayerHandle::~PlayerHandle()
{
    delete PlayerHandleMatrix[0][0]; //Desalocamos cada player.
    delete PlayerHandleMatrix[0][1];
    for (int i = 0; i < STATECOUNT; i++)
        delete[] this->PlayerHandleMatrix[i]; //Desalocamos columnas
}

event_t
PlayerHandle::getEvent()
{
    return event;
}

void
PlayerHandle::setEvent(event_t newEvent)
{
    event = newEvent;
}