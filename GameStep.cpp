#include "GameStep.h"

GameStep::GameStep()
{
}

GameStep::~GameStep()
{
}

void GameStep::showUsedPatrolCards()
{

}

void WaitingFirstAction::showInvalidTileMessage(gameData_t* gameData)
{

}

void Idle::showInvalidTileMessage(gameData_t* gameData)
{
    gameData->message = "Oops, looks like we can't go there, Chief. We gotta find another way.";
}

void GameStep::faceConsequences()
{

}

void GameStep::drawLoot(gamePointers_t* gamePointers)
{
    std::vector <Loot*>::iterator  lootIt;
    lootIt = gamePointers->loots.begin();
    gamePointers->currentCharacter->addLoot(*(gamePointers->loots[0]));
    gamePointers->loots.erase(lootIt);
    //if(loot==gold Bar)
    //hacer algo
}

void Idle::eventHandler(gameData_t *gameData, gamePointers_t* gamePointers)
{
    switch (gameData->event)
    {
        case VALID_TILE:
            enableActions(gameData);
            break; //pone en negrito las opciones posibles;
        case INVALID_TILE:
            showInvalidTileMessage(gameData);
            break;
        case A_PASS:
            gamePointers->currentCharacter->pass();
            //Cambio el pointer del currentCharacter
            (gamePointers->currentCharacter == gamePointers->characters[0]) ?  gamePointers->currentCharacter = gamePointers->characters[1] : gamePointers->currentCharacter = gamePointers->characters[0];
            gamePointers->floors[gamePointers->currentCharacter->getLocation() / 16]->moveGuard();
            break;
        case A_ADD_DICE_TO_SAFE:
            if (gameData->actions.addDice == true)
                gamePointers->currentCharacter->addDiceToSafe();
            break;
        case A_ROLL_DICE_FOR_SAFE:
            if (gameData->actions.rollDice == true)
            {
                gamePointers->floors[(unsigned) gamePointers->currentCharacter->getLocation() / 16]->crack(gamePointers->currentCharacter->getDieQty(), (location_t) (gamePointers->currentCharacter->getLocation() % 16));
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
            //            showHappyPepe();
            //            reset();
            break;
        case LOSE:
            //            showSadPepe();
            break;

        default: break;
    }

}

void Idle::enableActions(gameData_t* gameData)
{
    if (gameData->selectedTile.adyacent)
    {
        gameData->actions.move = true;
        gameData->actions.peek = true;
        gameData->actions.pass = true;
    }

    if (gameData->selectedTile.hawkWall)
    {
        gameData->actions.peek = true;
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
        case VALID_TILE:    //nunca va a entrar aca?
            enableActions(gameData);
            break;
        case A_FREE_MOVE:
            if (gameData->actions.move == true)
            {
                gamePointers->currentCharacter->move(gameData->selectedTile.tile);
                faceConsequences();     //consecuencias cuando se mueve a una tile
            }
            enableActions(gameData);
            break;
        case A_PASS:
            gamePointers->currentCharacter->pass();
            for (unsigned i = 0; i < (gamePointers->guards[gamePointers->currentCharacter->getLocation() / 16]->getSpeed()); i++)
                gamePointers->floors[gamePointers->currentCharacter->getLocation() / 16]->moveGuard();
            enableActions(gameData);
            break;
        case A_PEEK:
            if (gameData->actions.peek == true)
                gamePointers->currentCharacter->peek(gameData->selectedTile.tile);
            enableActions(gameData);
            break;
        case A_ADD_DICE_TO_SAFE:
            if (gameData->actions.addDice == true)
                gamePointers->currentCharacter->addDiceToSafe();
            enableActions(gameData);
            break;
        case A_ROLL_DICE_FOR_SAFE:
            if (gameData->actions.rollDice == true)
            {
                gamePointers->floors[(unsigned) gamePointers->currentCharacter->getLocation() / 16]->crack(gamePointers->currentCharacter->getDieQty(), gamePointers->currentCharacter->getLocation());
                if (gamePointers->currentCharacter->wasCracked())
                    drawLoot(gamePointers);
            }
            enableActions(gameData);
            break;
        case A_HACK_COMPUTER:
            if (gameData->actions.hackCR == true)
            {
                gamePointers->currentCharacter->setHackToken();
                enableActions(gameData);
            }
            break;
        case A_USE_HACK_TOKEN:
            if (gameData->actions.useHackToken == true)
            {
                gamePointers->currentCharacter->useHackToken(gamePointers->currentCharacter->whereAmI());
                //untrigger alarm
            }
            enableActions(gameData);
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

void WaitingFirstAction::enableActions(gameData_t* gameData)
{
    if (gameData->event == VALID_TILE || gameData->event == INVALID_TILE || gameData->event == A_FREE_MOVE
            || gameData->event == A_PEEK || gameData->event == A_PASS || gameData->event == A_PATROL_IS_BOTTOM
            || gameData->event == A_PATROL_IS_TOP || gameData->event == A_PICKUP_LOOT)
    {
        gameData->actions.pass = true;

        gameData->actions.move = false;
        gameData->actions.peek = false;
        gameData->actions.acceptDecline = false;
        gameData->actions.addDice = false;
        gameData->actions.createAlarm = false;
        gameData->actions.hackCR = false;
        gameData->actions.patrolIsTopBottom = false;
        gameData->actions.pickupLoot = false;
        gameData->actions.placeCrowToken = false;
        gameData->actions.rollDice = false;
        gameData->actions.offerLoot = false;
        gameData->actions.requestLoot = false;
        gameData->actions.spyPatrolDeck = false;
        gameData->actions.useHackToken = false;
    }
    else if (gameData->event == INVALID_TILE)
    {
        gameData->actions.pass = true;

        gameData->actions.move = false;
        gameData->actions.peek = false;
        gameData->actions.acceptDecline = false;
        gameData->actions.addDice = false;
        gameData->actions.createAlarm = false;
        gameData->actions.hackCR = false;
        gameData->actions.patrolIsTopBottom = false;
        gameData->actions.pickupLoot = false;
        gameData->actions.placeCrowToken = false;
        gameData->actions.rollDice = false;
        gameData->actions.offerLoot = false;
        gameData->actions.requestLoot = false;
        gameData->actions.spyPatrolDeck = false;
        gameData->actions.useHackToken = false;
    }
    // else if (gameData->event == );


    //Pone en false las acciones que ya no se pueden hacer???
}

void WaitingSecondAction::enableActions(gameData_t* gameData)
{

}

void WaitingSecondAction::showInvalidTileMessage(gameData_t*)
{

}

void WaitingResponse::enableActions(gameData_t* gameData)
{

}

void WaitingResponse::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void End::enableActions(gameData_t* gameData)
{

}

void End::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void WaitingSecondAction::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void PlayAgain::showInvalidTileMessage(gameData_t* gameData)
{

}

void PlayAgain::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void PlayAgain::enableActions(gameData_t*)
{

}

void End::showInvalidTileMessage(gameData_t* gameData)
{

}

void WaitingResponse::showInvalidTileMessage(gameData_t* gameData)
{

}

