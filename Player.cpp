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
Player::eventHandler(event_t event, gameData_t* gameData)
{
	bool ret = true; //en que caso devolvería false?

    switch (event) //Los eventos que me pasan son solo ACTION y TURN
    {
        case ACTION: 
            if(model->analyzeAction(gameData)) //AnalyzeAction devuelve true si se acabaron las actions
            {
                event = PASS;
                eventHandler(event, gameData);
            }
            
            break; //Pasamos por parámetro el indice al arreglo de characters
        case PASS: model->analyzeAction(gameData); 
            break;
        default: break;
    }
    
 return ret;

}

state_t
Player::getCurrentPlayer()
{
    return currentPlayer;
}




