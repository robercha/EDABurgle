#include "FSM.h"

FSM::FSM(Player* player1, Player* player2)
{
    Player * FSMTempMatrix[STATECOUNT][EVENTCOUNT] = //Creamos matriz temporal para luego copiar a la final
    {
        //ACTION   TURN
        {player1, player2}, //Player 1
        {player2, player1}, //Player 2
    };

    FSMMatrix = new Player**[STATECOUNT];
    for (int i = 0; i < STATECOUNT; i++)
    {
        FSMMatrix[i] = new Player*[EVENTCOUNT]; //Alocamos las columnas

        for (int j = 0; j < EVENTCOUNT; j++)
        {
            FSMMatrix[i][j] = FSMTempMatrix[i][j]; //copiamos celda a celda la matriz temporal
        }
    }
}

void
FSM::FSMCycle(event_t event, gameData_t *gameData)
{
    currentPlayer->eventHandler(event, gameData);
    currentPlayer = FSMMatrix[currentPlayer->getCurrentPlayer()][event];
}

FSM::~FSM()
{
    for (int i = 0; i < STATECOUNT; i++)
        delete[] this->FSMMatrix[i]; //Desalocamos columnas
    delete[] this->FSMMatrix;

}

