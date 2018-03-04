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
            //Cambio el pointer del currentCharacter
            (gamePointers->currentCharacter == gamePointers->characters[0]) ?  gamePointers->currentCharacter = gamePointers->characters[1] : gamePointers->currentCharacter = gamePointers->characters[0];
            moveGuards();
            break;
        case A_ADD_DICE_TO_SAFE:
            if (gameData->actions.addDice == true)
                gamePointers->currentCharacter->addDiceToSafe();
            break;
        case A_ROLL_DICE_FOR_SAFE:
            if (gameData->actions.rollDice == true)
            {
                gamePointers->floors[(unsigned) gamePointers->currentCharacter->getLocation() / 16]->crack(gamePointers->currentCharacter->getDieQty(), (location_t) gamePointers->currentCharacter->getLocation() % 16, gameData);
                if (gamePointers->currentCharacter->wasCracked())
                    drawLoot(gamePointers);
            }
            break;
        case A_HACK_COMPUTER:
            if (gameData->actions.hackCR == true)
            {
                gamePointers->currentCharacter->setHackToken();
            }
            break;
        case A_USE_HACK_TOKEN:
            if (gameData->actions.useHackToken == true)
            {
                gamePointers->currentCharacter->useHackToken(gamePointers->currentCharacter->whereAmI());
                //untrigger alarm
            }
            break;
        case A_SPY_PATROL_DECK:
            break;
        case A_LOOT: break;
        case A_PATROL_CARD:
            showUsedPatrolCards();
            break;
        case WIN:
            showPepe();
            reset();
            break;
        case LOSE:
            showSadPepe();
            break;

        default: break;
    }

}

void Idle::enableActions(gameData_t gameData)
{
    if (gameData->selectedTile.adyacent)
    {
        gameData->actions.move = true;
        gameData->actions.peek = true;
        gameData->actions.pass = true;
    }
    if (gameData->selectedTile.hawkWall)
    {
        gameData->actions.createAlarm = true;
    }
    if (gameData->selectedTile.serviceDuct)
    {
        gameData->actions.move = true;
    }
    if (gameData->selectedTile.twoTilesAwayTile)
    {
        gameData->actions.placeCrowToken = true;
    }



}

void WaitingFirstAction::eventHandler(gameData_t* gameData, gamePointers_t* gamePointers)
{
    switch (gameData->event)
    {
        case VALID_TILE:
            //enableActions();
            break;
        case A_FREE_MOVE:
            if (gameData->actions.move == true)
            {
                gamePointers->currentCharacter->move(gameData->selectedTile.tile);
                faceConsequences();     //consecuencias cuando se mueve a una tile
            }
            break;
        case A_PASS:
            gamePointers->currentCharacter->pass();
            moveGuards();
            break;
        case A_PEEK:
            if (gameData->actions.peek == true)
                gamePointers->currentCharacter->peek(gameData->selectedTile.tile);
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
                gamePointers->currentCharacter->setHackToken();
            }
            break;
        case A_USE_HACK_TOKEN:
            if (gameData->actions.useHackToken == true)
            {
                gamePointers->currentCharacter->useHackToken(gamePointers->currentCharacter->whereAmI());
                //untrigger alarm
            }
            break;
        case A_OFFER_LOOT:
            break;
        case A_REQUEST_LOOT:
            break;
        case A_PICKUP_LOOT:
            break;
        case A_CREATE_ALARM:
            break;
        case A_PATROL_IS_TOP:
            break;
        case A_PATROL_IS_BOTTOM:
            break;
        case A_PLACE_CROW_TOKEN:
            break;
        case A_LOOT: break;
        case A_PATROL_CARD:
            showUsedPatrolCards();
            break;
        default: break;
    }
}

void WaitingFirstAction::enableActions()
{

}

void WaitingResponse::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void End::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void PlayAgain::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void WaitingSecondAction::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}


