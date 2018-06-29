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

void GameStep::enterRoom(gameData_t* gameData, gamePointers_t*  gamePointers)
{
    unsigned floorNumber = getFloor(gamePointers->currentCharacter->getLocation());
    if (gamePointers->currentCharacter->getLocation() == gamePointers->floors[floorNumber]->getGuardLocation())
    {
        gamePointers->currentCharacter->decreaseStealth();
        if (gamePointers->currentCharacter->isDead())
            gameData->event = LOSE;
    }

    if (gamePointers->floors[floorNumber]->isAlarmTile(gamePointers->currentCharacter->getLocation()))
        gamePointers->floors[floorNumber]->setAlarmToken(gamePointers->currentCharacter->getLocation(), true);
}

void GameStep::drawLoot(gamePointers_t* gamePointers)
{
    unsigned floor = getFloor(gamePointers->currentCharacter->getLocation());
    gamePointers->currentCharacter->addLoot((*gamePointers->floors[floor]->getLoot()));

    //if(loot==gold Bar)
    //hacer algo
}

void Idle::eventHandler(gameData_t *gameData, gamePointers_t* gamePointers)
{
    switch (gameData->event)
    {
        case VALID_TILE:
        {
            enableActions(gameData, gamePointers);
            break; //pone en negrito las opciones posibles;
        }
        case INVALID_TILE:
        {
            showInvalidTileMessage(gameData);
            break;
        }
        case A_PASS:
        {
            unsigned floor = getFloor(gamePointers->currentCharacter->getLocation());
            gamePointers->currentCharacter->pass();
            //Cambio el pointer del currentCharacter
            (gamePointers->currentCharacter == gamePointers->characters[0]) ?  gamePointers->currentCharacter = gamePointers->characters[1] : gamePointers->currentCharacter = gamePointers->characters[0];

            for (unsigned i = 0; i < (gamePointers->floors[floor]->getGuardSpeed()); i++)
                gamePointers->floors[floor]->moveGuard();
            enableActions(gameData, gamePointers);
            break;
        }
        case A_ADD_DICE_TO_SAFE:
        {
            if (gameData->actions.addDice == true)
            {
                unsigned floor = (unsigned) gamePointers->currentCharacter->getLocation() / 16;
                gamePointers->floors[floor]->addDiceToSafe((location_t) (gamePointers->currentCharacter->getLocation() % 16));
                gamePointers->currentCharacter->decreaseActions();
            }
            break;
        }
        case A_ROLL_DICE_FOR_SAFE:
        {
            if (gameData->actions.rollDice == true)
            {
                unsigned floor = (unsigned) gamePointers->currentCharacter->getLocation() / 16;
                gamePointers->floors[floor]->crack(gamePointers->currentCharacter->getDieQty(), (location_t) (gamePointers->currentCharacter->getLocation() % 16));
                if (gamePointers->floors[floor]->isSafeCracked((location_t) (gamePointers->currentCharacter->getLocation() % 16)))
                    drawLoot(gamePointers);
            }
            break;
        }
        case A_HACK_COMPUTER:
        {
            if (gameData->actions.hackCR == true)
            {
                gamePointers->currentCharacter->setHackToken();
            }
            break;
        }
        case A_USE_HACK_TOKEN:
        {
            if (gameData->actions.useHackToken == true)
            {
                gamePointers->currentCharacter->useHackToken(gamePointers->currentCharacter->whereAmI());
                //untrigger alarm
            }
            break;
        }
        case A_SPY_PATROL_DECK:
        {
            break;
        }
        case A_LOOT:
        {
        }
        break;
        case A_PATROL_CARD:
        {
            showUsedPatrolCards();
            break;
        }
        case WIN:
        {
            //            showHappyPepe();
            //            reset();
            break;
        }
        case LOSE:
        {
            //            showSadPepe();
            break;
        }
        default:
        {
            break;
        }
    }

}

void Idle::enableActions(gameData_t* gameData, gamePointers_t* gamePointers)
{
    if(gameData->event == VALID_TILE)
    {
        if (gameData->selectedTile.adyacent)
        {
            gameData->actions.move = true;
            gameData->actions.peek = true;
            gameData->actions.pass = true;
        }
        else
         {
            gameData->actions.move = false;
            gameData->actions.peek = false;
            gameData->actions.pass = false;
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


}

void WaitingFirstAction::eventHandler(gameData_t* gameData, gamePointers_t* gamePointers)
{
    switch (gameData->event)
    {
        case A_FREE_MOVE:
        {
            if (gameData->actions.move == true)
            {
                gamePointers->currentCharacter->move(gameData->selectedTile.tile);
                enterRoom(gameData, gamePointers);     //consecuencias cuando se mueve a una tile
            }
            enableActions(gameData, gamePointers);
            break;
        }
        case A_PAID_MOVE:
        {
            enableActions(gameData, gamePointers);
            gameData->message = "Oh, we have a tough decision to make. Should we do it?";
            break;
        }
        case A_PASS:
        {
            gamePointers->currentCharacter->pass();
            unsigned floor = getFloor(gamePointers->currentCharacter->getLocation());

            (gamePointers->currentCharacter == gamePointers->characters[0]) ?  gamePointers->currentCharacter = gamePointers->characters[1] : gamePointers->currentCharacter = gamePointers->characters[0];

            for (unsigned i = 0; i < (gamePointers->floors[floor]->getGuardSpeed()); i++)
                gamePointers->floors[floor]->moveGuard();

            enableActions(gameData, gamePointers);
            break;
        }
        case A_PEEK:
        {
            if (gameData->actions.peek == true)
                gamePointers->currentCharacter->peek(gameData->selectedTile.tile);
            enableActions(gameData, gamePointers);
            break;
        }
        case A_ADD_DICE_TO_SAFE:
        {
            if (gameData->actions.addDice == true)
            {
                unsigned floor = (unsigned) gamePointers->currentCharacter->getLocation() / 16;
                gamePointers->floors[floor]->addDiceToSafe((location_t) (gamePointers->currentCharacter->getLocation() % 16));
                gamePointers->currentCharacter->decreaseActions();
            }
            enableActions(gameData, gamePointers);
            break;
        }
        case A_ROLL_DICE_FOR_SAFE:
        {
            if (gameData->actions.rollDice == true)

                if (gameData->actions.rollDice == true)
                {
                    unsigned floor = (unsigned) gamePointers->currentCharacter->getLocation() / 16;
                    gamePointers->floors[floor]->crack(gamePointers->currentCharacter->getDieQty(), (location_t) (gamePointers->currentCharacter->getLocation() % 16));
                    if (gamePointers->floors[floor]->isSafeCracked((location_t) (gamePointers->currentCharacter->getLocation() % 16)))
                        drawLoot(gamePointers);
                }
            enableActions(gameData, gamePointers);
            break;
        }
        case A_HACK_COMPUTER:
        {
            if (gameData->actions.hackCR == true)
            {
                gamePointers->currentCharacter->setHackToken();
                enableActions(gameData, gamePointers);
            }
            break;
        }
        case A_USE_HACK_TOKEN:
        {
            if (gameData->actions.useHackToken == true)
            {
                gamePointers->currentCharacter->useHackToken(gamePointers->currentCharacter->whereAmI());
                //untrigger alarm
            }
            enableActions(gameData, gamePointers);
            break;
        }
        case A_OFFER_LOOT:
        {
            break;
        }
        case A_REQUEST_LOOT:
        {
            break;
        }
        case A_PICKUP_LOOT:
        {
            break;
        }
        case A_CREATE_ALARM:
        {
            break;
        }
        case A_PATROL_IS_TOP:
        {
            break;
        }
        case A_PATROL_IS_BOTTOM:
        {
            break;
        }
        case A_PLACE_CROW_TOKEN:
        {
            break;
        }
        case A_LOOT:
        {
            break;
        }
        case A_PATROL_CARD:
        {
            showUsedPatrolCards();
            break;
        }
        default:
        {
            break;
        }
    }
}

void WaitingFirstAction::enableActions(gameData_t* gameData, gamePointers_t* gamePointers)
{
    if (gameData->event == A_PAID_MOVE)
    {
        gameData->actions.pass = false;
        gameData->actions.move = false;
        gameData->actions.peek = false;
        gameData->actions.acceptDecline = true;
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
    if (gameData->event == A_FREE_MOVE)
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

}

void WaitingSecondAction::eventHandler(gameData_t* gameData, gamePointers_t* gamePointers)
{
    switch (gameData->event)
    {
        case ACCEPT:
            gamePointers->currentCharacter->move(gameData->selectedTile.tile);
            enableActions(gameData, gamePointers);
            break;
        case DECLINE:
            enableActions(gameData, gamePointers);
            break;

        default: break;
    }
}

void WaitingSecondAction::enableActions(gameData_t* gameData, gamePointers_t* gamePointers)
{
    if (gameData->event == ACCEPT || gameData->event == DECLINE)
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
}

void WaitingSecondAction::showInvalidTileMessage(gameData_t* gameData)
{
    gameData->message = "We have to make a decision. Quick! Go with your guts on this one.";
}

void WaitingResponse::enableActions(gameData_t* gameData, gamePointers_t* gamePointers)
{

}

void WaitingResponse::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void End::enableActions(gameData_t* gameData, gamePointers_t* gamePointers)
{

}

void End::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void PlayAgain::showInvalidTileMessage(gameData_t* gameData)
{

}

void PlayAgain::eventHandler(gameData_t *gameData, gamePointers_t * gamePointers)
{

}

void PlayAgain::enableActions(gameData_t*, gamePointers_t* gamePointers)
{

}

void End::showInvalidTileMessage(gameData_t* gameData)
{

}

void WaitingResponse::showInvalidTileMessage(gameData_t* gameData)
{

}

