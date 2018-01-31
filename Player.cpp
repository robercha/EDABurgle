#include "Player.h"
#include <iostream>

Player::Player(Model* model, state_t player)
{
    this->model=model;
    this->currentPlayer = player;
}

Player::~Player()
{
}

void
Player::eventHandler(event_t event, gameData_t* gameData)
{
    switch (event) //Los eventos que me pasan son solo ACTION y TURN
    {
        case ACTION: printf("model actúa");//model->analyzeAction(gameData, event); //Aca empieza la lógica del juego
            break; //Pasamos por parámetro el indice al arreglo de characters
        case SWITCH_PLAYER: printf("Cambio de player"); switchPlayer();
            break;
        default: break;
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


