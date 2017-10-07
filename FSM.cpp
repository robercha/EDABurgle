#include "FSM.h"

FSM::FSM(Player* Player1, Player* Player2)
{
    Player * FSMTempMatrix[STATECOUNT][EVENTCOUNT] = //Creamos matriz temporal para luego copiar a la final
    {
        //ACTION   TURN
        {&Player1, &Player2}, //Player 1
        {&Player2, &Player1}, //Player 2
    };

    this->FSMMatrix = new Player**[STATECOUNT]; //Alocamos las filas de la matriz
    for (int i = 0; i < STATECOUNT; i++)
    {
        this->FSMMatrix[i] = new Player*[EVENTCOUNT]; //Alocamos las columnas

        for (int j = 0; j < EVENTCOUNT; j++)
        {
            this->FSMMatrix[i][j] = FSMTempMatrix[i][j]; //copiamos celda a celda la matriz temporal
        }
    }
}

FSM::FSMCycle(event_t event, gameData_t gameData)
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

