#include "GameStep.h"

GameStep::GameStep()
{
}

GameStep::~GameStep()
{
}

void GameStep::drawLoot(gamePointers_t* gamePointers)
{
    gamePointers->currentCharacter->addLoot(gamePointers->loots[0]);
    gamePointers->loots.erase(0);
    //if(loot==gold Bar)
    //hacer algo
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
        case A_ADD_DICE_TO_SAFE:
            if (gameData->actions.addDice == true)
                gamePointers->currentCharacter->addDiceToSafe();
            break;
        case A_ROLL_DICE_FOR_SAFE:
            if (gameData->actions.rollDice == true)
            {
                gamePointers->floors[(unsigned) gamePointers->currentCharacter->getLocation() / 16]->crack(gamePointers->currentCharacter->getDieQty());
                if (gamePointers->currentCharacter->wasCracked())
                    drawLoot(gamePointers);
            }
            break;
        case A_HACK_COMPUTER:
            if (gameData->actions.hackCR == true)
            {
                gamePointers->currentCharacter->addToken(HACKTOKEN, NULL);
            }
            break;
        case A_USE_HACK_TOKEN:
            if (gameData->actions.useHackToken == true)
            {
                //completar
            }
            break;
        case A_LOOT: break;
        case A_PATROL_CARD:
            showUsedPatrolCards();
            break;
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


