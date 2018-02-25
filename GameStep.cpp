#include "GameStep.h"

GameStep::GameStep()
{
}

GameStep::~GameStep()
{
}

void Idle::eventHandler(gameData_t *gameData, gamePointers_t* gamePointers)
{
    switch (gameData->event)
    {
        case VALID_TILE:
            enableActions();
            break; //pone en negrito las opciones posibles;
        case INVALID_TILE:
            showInvalidTileMessage();
            break;
        case A_PASS:
            gamePointers->currentCharacter->pass();
            moveGuards();
            break;
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

void Idle::enableActions()
{

}

void WaitingFirstAction::eventHandler(gameData_t *gameData, gamePointers_t* gamePointers)
{

}

void WaitingResponse::eventHandler(gameData_t *gameData, gamePointers_t* gamePointers)
{

}

void End::eventHandler(gameData_t *gameData, gamePointers_t* gamePointers)
{

}

void PlayAgain::eventHandler(gameData_t *gameData, gamePointers_t* gamePointers)
{

}

void WaitingSecondAction::eventHandler(gameData_t *gameData, gamePointers_t* gamePointers)
{

}


