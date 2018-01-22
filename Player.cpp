#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void
Player::eventHandler(event_t event, gameData_t* gameData)
{
    switch (event) //Los eventos que me pasan son solo ACTION y TURN
    {
        case ACTION: model->analyzeAction(gameData); //Aca empieza la lógica del juego
            break; //Pasamos por parámetro el indice al arreglo de characters
        case TURN: switchPlayer();
            break;
    }
}

state_t
Player::getCurrentPlayer()
{
    return currentPlayer;
}

void
Player::switchPlayer()
{
}//dummy function


