#include "GameStep.h"



GameStep::GameStep()
{
}

GameStep::~GameStep()
{
}

void Idle::eventHandler(gameData_t* gameData)
{
    switch(gameData->event)
    {
        case VALID_TILE: break; //pone en negrito las opciones posibles;
        case INVALID_TILE: break;
        case A_PASS: break;
        case A_ADD_DICE_TO_SAFE: break;
        case A_ROLL_DICE_FOR_SAFE: break;
        case A_HACK_COMPUTER: break;
        case A_PICKUP_LOOT: break;
        case A_USE_HACK_TOKEN: break;
        case WIN: break;
        case LOSE: break;
        
        default: break;
    }
    
}

void WaitingFirstAction::eventHandler(gameData_t* gameData) 
{

}

void WaitingResponse::eventHandler(gameData_t* gameData)
{

}

void End::eventHandler(gameData_t* gameData) 
{

}

void PlayAgain::eventHandler(gameData_t* gameData) 
{

}

void WaitingSecondAction::eventHandler(gameData_t* gameData) 
{

}


