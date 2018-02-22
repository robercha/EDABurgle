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

bool
Player::eventHandler(gameData_t* gameData)
{
    switch (gameData->event) //Los eventos que me pasan son solo ACTION y TURN
    {
        case ACTION: 
            if(model->analyzeAction(gameData, (unsigned)currentPlayer)) //AnalyzeAction devuelve true si se acabaron las actions
            {
                gameData->event = PASS;
                eventHandler(gameData);
            }
            
            break; //Pasamos por parámetro el indice al arreglo de characters
        case PASS: model->analyzeAction(gameData, (unsigned)currentPlayer); 
            break;
        default: break;
    }
    
 
}

state_t
Player::getCurrentPlayer()
{
    return currentPlayer;
}




