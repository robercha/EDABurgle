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
    checkAlarms(gameData, gamePointers);
}

void GameStep::checkAlarms(gameData_t* gameData, gamePointers_t* gamePointers)
{
    unsigned floorNumber = getFloor(gamePointers->currentCharacter->getLocation());
    if (gamePointers->floors[floorNumber]->isAlarmTile(gamePointers->currentCharacter->getLocation()))
    {
        //camera
        if ((gamePointers->floors[floorNumber]->getGuardRoom() == CAMERA)&&(gamePointers->currentCharacter->whereAmI() == CAMERA))
            triggerAlarm(gameData, gamePointers);
        //deadbolt
        if ((gamePointers->currentCharacter->getLootQty() != 0)&&(gamePointers->currentCharacter->whereAmI() == DEADBOLT))
            triggerAlarm(gameData, gamePointers);
        if (gamePointers->currentCharacter->whereAmI() == FINGERPRINT)
            triggerAlarm(gameData, gamePointers);
        //2 actions to enter or trigger alarm, laser
        //stop here or trigger alarm, motion
        //if actions end here, trigger alarm, thermo
        //falta hacer esto en el move del guardia, con sus respectivas alarmas
    }
}

void GameStep::triggerAlarm(gameData_t* gameData, gamePointers_t* gamePointers)
{
    unsigned floorNumber = getFloor(gamePointers->currentCharacter->getLocation());
    gamePointers->floors[floorNumber]->setAlarmToken(gamePointers->currentCharacter->getLocation(), true);
    gamePointers->floors[floorNumber]->increaseGuardSpeed();
}

void GameStep::drawLoot(gamePointers_t* gamePointers)
{
    unsigned floor = getFloor(gamePointers->currentCharacter->getLocation());
    gamePointers->currentCharacter->addLoot((*gamePointers->floors[floor]->getLoot()));

    //if(loot==gold Bar)
}

void GameStep::checkFloorChange(gameData_t* gameData, gamePointers_t* gamePointers)
{
    unsigned currentFloor = getFloor(gamePointers->currentCharacter->getLocation());

    if (gamePointers->currentCharacter->whereAmI() == STAIRS)
    {
        if (gameData->selectedTile.differentFloor)
        {
            unsigned newFloor = getFloor(gameData->selectedTile.tile->getCurrentLocation());
            if (gamePointers->floors[newFloor]->isGuardActive());
            else
                gamePointers->floors[newFloor]->toggleGuard();
        }
    }
}

void Idle::eventHandler(gameData_t *gameData, gamePointers_t* gamePointers)
{
    switch (gameData->event)
    {
        case VALID_TILE:
        {
            enableActions(gameData, gamePointers);
            if (!gameData->selectedTile.tile->isTileVisible())
                gameData->message = "Be careful bosss, Do you want to take a peek first?";
            break;
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
            {
                gamePointers->floors[floor]->moveGuard();
                for (unsigned j = 0; j < 2 ; j++)
                    if (gamePointers->characters[j]->getLocation() == gamePointers->floors[floor]->getGuardLocation())
                        gamePointers->characters[j]->decreaseStealth();
            }
            enableActions(gameData, gamePointers);
            gameData->message = "Alright, let me know what you need, bosss";
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
                gamePointers->currentCharacter->setHackToken(gamePointers->currentCharacter->whereAmI());
            }
            enableActions(gameData, gamePointers);
            break;
        }
        case A_USE_HACK_TOKEN:
        {
            if (gameData->actions.useHackToken == true)
            {
                unsigned floorNumbah = getFloor(gameData->selectedTile.tile->getCurrentLocation());
                gamePointers->currentCharacter->useHackToken(gamePointers->currentCharacter->whereAmI());
                gamePointers->floors[floorNumbah]->setAlarmToken(gameData->selectedTile.tile->getCurrentLocation(), false);
            }
            enableActions(gameData, gamePointers);
            break;
        }
        case A_SPY_PATROL_DECK:
        {
            if (gameData->actions.spyPatrolDeck == true)
            {
                ;
            }
            break;
        }
        case A_LOOT:
        {
            //muestra loot, creo que no hace falta hacer nada
            break;
        }

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
    if (gameData->event == VALID_TILE)
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
        if (gameData->selectedTile.tile->getTileType() == LASER)
        {
            for (unsigned f = 0; f < FLOORS_QTY; f++)
            {
                if (gameData->selectedTile.tile->isTileVisible())
                    if (gameData->selectedTile.tile->isAlarmOn())
                        if (gamePointers->floors[f]->canIUseMotionHackToken())       //si hay laser room, avisa si hay hack tokens disponibles
                            gameData->actions.useHackToken = true;
            }
        }
        if (gameData->selectedTile.tile->getTileType() == MOTION)
        {
            for (unsigned f = 0; f < FLOORS_QTY; f++)
            {
                if (gameData->selectedTile.tile->isTileVisible())
                    if (gameData->selectedTile.tile->isAlarmOn())
                        if (gamePointers->floors[f]->canIUseMotionHackToken())       //si hay laser room, avisa si hay hack tokens disponibles
                            gameData->actions.useHackToken = true;
            }
        }
        if (gameData->selectedTile.tile->getTileType() == FINGERPRINT)
        {
            for (unsigned f = 0; f < FLOORS_QTY; f++)
            {
                if (gameData->selectedTile.tile->isTileVisible())
                    if (gameData->selectedTile.tile->isAlarmOn())
                        if (gamePointers->floors[f]->canIUseMotionHackToken())       //si hay laser room, avisa si hay hack tokens disponibles
                            gameData->actions.useHackToken = true;
            }
        }
        if ((gameData->selectedTile.tile->getTileType() == CR_FINGERPRINT) && gameData->selectedTile.ownTile)
        {
            if (gameData->selectedTile.tile->isTileVisible())
                if (!(dynamic_cast<CRFingerprint*> (gameData->selectedTile.tile)->areHackTokensMax()))  //si puedo agregar hackTokens
                    gameData->actions.hackCR = true;
        }
        if ((gameData->selectedTile.tile->getTileType() == CR_LASER) && gameData->selectedTile.ownTile)
        {
            if (gameData->selectedTile.tile->isTileVisible())
                if (!(dynamic_cast<CRLaser*> (gameData->selectedTile.tile)->areHackTokensMax()))  //si puedo agregar hackTokens
                    gameData->actions.hackCR = true;
        }
        if ((gameData->selectedTile.tile->getTileType() == CR_MOTION) && gameData->selectedTile.ownTile)
        {
            if (gameData->selectedTile.tile->isTileVisible())
                if (!(dynamic_cast<CRMotion*> (gameData->selectedTile.tile)->areHackTokensMax()))  //si puedo agregar hackTokens
                    gameData->actions.hackCR = true;
        }
    }
    else if (gameData->event == INVALID_TILE)
    {
        gameData->actions.move = false;
        gameData->actions.peek = false;
        gameData->actions.pass = false;
        gameData->actions.acceptDecline = false;
        gameData->actions.addDice = false;
        gameData->actions.createAlarm = false;
        gameData->actions.hackCR = false;
        gameData->actions.offerLoot = false;
        gameData->actions.patrolIsTopBottom = false;
        gameData->actions.pickupLoot = false;
        gameData->actions.placeCrowToken = false;
        gameData->actions.requestLoot = false;
        gameData->actions.spyPatrolDeck = false;
        gameData->actions.rollDice = false;
        gameData->actions.useHackToken = false;
    }


}

void WaitingFirstAction::eventHandler(gameData_t* gameData, gamePointers_t* gamePointers)
{
    switch (gameData->event)
    {
        case VALID_TILE:
        {
            enableActions(gameData, gamePointers);      //pone en negrito las opciones posibles;
            break;
        }
        case INVALID_TILE:
        {
            enableActions(gameData, gamePointers);
            break;
        }
        case A_FREE_MOVE:
        {
            checkFloorChange(gameData, gamePointers);
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
            {
                gamePointers->floors[floor]->moveGuard();

                for (unsigned j = 0; j < 2 ; j++)
                    if (gamePointers->characters[j]->getLocation() == gamePointers->floors[floor]->getGuardLocation())
                        gamePointers->characters[j]->decreaseStealth();
            }
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
                gamePointers->currentCharacter->setHackToken(gamePointers->currentCharacter->whereAmI());
            }
            enableActions(gameData, gamePointers);
            break;
        }
        case A_USE_HACK_TOKEN:
        {
            if (gameData->actions.useHackToken == true)
            {
                unsigned floorNumbah = getFloor(gameData->selectedTile.tile->getCurrentLocation());
                gamePointers->currentCharacter->useHackToken(gamePointers->currentCharacter->whereAmI());
                gamePointers->floors[floorNumbah]->setAlarmToken(gameData->selectedTile.tile->getCurrentLocation(), false);
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
    if (gameData->event == A_FREE_MOVE || gameData->event == A_PEEK || gameData->event == A_PASS || gameData->event == VALID_TILE || gameData->event == INVALID_TILE ) //No se si falta aguna mas habria que agregar eventos para hacerle reset
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
            checkFloorChange(gameData, gamePointers);
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

