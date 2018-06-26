#include "Model.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <time.h>


Model::Model()
{
    std::vector<Tile*> deck;

    createTiles(deck);
    shuffleTiles(deck);
    createFloors(deck);
    createModelFSM();
    createLoots();
    createCharacters();
}

Model::~Model()
{
    unsigned i;
    for (i = 0; i < FLOORS_QTY; i++)
        delete floors[i];
}

void Model::createLoots()
{
    loots.push_back(new Tiara);
    loots.push_back(new Kitty);
    loots.push_back(new Painting);
    loots.push_back(new Mirror);
    loots.push_back(new KeyCard);
    loots.push_back(new Isotope);
    loots.push_back(new Gemstone);
    loots.push_back(new Goblet);
    loots.push_back(new Chihuahua);
    loots.push_back(new GoldBar);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(loots.begin(), loots.end(), std::default_random_engine(seed));

}

void Model::createTiles(std::vector<Tile*> &deck)
{
    unsigned i;

    for (i = 0; i < ATRIUM_QTY; i++)
        deck.push_back(new Atrium);
    for (i = 0; i < ATRIUM_QTY; i++)
        deck.push_back(new Atrium);
    for (i = 0; i < CAMERA_QTY; i++)
        deck.push_back(new Camera);
    for (i = 0; i < CROOM_FINGERPRINT_QTY; i++)
        deck.push_back(new CRFingerprint);
    for (i = 0; i < CROOM_LASER_QTY; i++)
        deck.push_back(new CRLaser);
    for (i = 0; i < CROOM_MOTION_QTY; i++)
        deck.push_back(new CRMotion);
    for (i = 0; i < DEADBOLT_QTY; i++)
        deck.push_back(new Deadbolt);
    for (i = 0; i < FINGERPRINT_QTY; i++)
        deck.push_back(new Fingerprint);
    for (i = 0; i < FOYER_QTY; i++)
        deck.push_back(new Foyer);
    for (i = 0; i < KEYPAD_QTY; i++)
        deck.push_back(new Keypad);
    for (i = 0; i < LABORATORY_QTY; i++)
        deck.push_back(new Laboratory);
    for (i = 0; i < LASER_QTY; i++)
        deck.push_back(new Laser);
    for (i = 0; i < LAVATORY_QTY; i++)
        deck.push_back(new Lavatory);
    for (i = 0; i < MOTION_QTY; i++)
        deck.push_back(new Motion);
    for (i = 0; i < SCANNER_DETECTOR_QTY; i++)
        deck.push_back(new Detector);
    for (i = 0; i < SECRET_DOOR_QTY; i++)
        deck.push_back(new SecretDoor);
    for (i = 0; i < SERVICE_DUCT_QTY; i++)
        deck.push_back(new ServiceDuct);

    ServiceDuct* tempDuct; //inicializamos los punteros a los respectivos Service Ducts
    unsigned n = deck.size();
    tempDuct = (ServiceDuct*) deck.at(n - 1);
    tempDuct->setSecondduct((ServiceDuct*) deck.at(n - 2));
    tempDuct = (ServiceDuct*) deck.at(n - 2);
    tempDuct->setSecondduct((ServiceDuct*) deck.at(n - 1));

    for (i = 0; i < THERMO_QTY; i++)
        deck.push_back(new Thermo);
    for (i = 0; i < WALKWAY_QTY; i++)
        deck.push_back(new Walkway);
}

void Model::createCharacters()
{
    characters.push_back(new Juicer);
    characters.push_back(new Acrobat);
    characters.push_back(new Hacker);
    characters.push_back(new Hawk);
    characters.push_back(new Spotter);
    characters.push_back(new Raven);
    characters.push_back(new Peterman);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(characters.begin(), characters.end(), std::default_random_engine(seed));

    for (std::vector<Character*>::iterator charIt = characters.end(); charIt != (characters.begin() + 2); charIt--)     //shuffleo y saco 5 (de 7) para que queden los dos jugadores
        characters.pop_back();
    
    srand(time(NULL));
    unsigned initialRow = rand()%4; 
    unsigned initialCol = rand()%4; 
    characters[0]->setInitialTile(floors[0]->getDeck()[initialRow][initialCol]);
    characters[1]->setInitialTile(floors[0]->getDeck()[initialRow][initialCol]);   
}

void Model::shuffleTiles(std::vector<Tile*> deck)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void Model::createFloors(std::vector<Tile*> deck)
{
    std::vector<Tile*> floorDeck;

    for (unsigned i = 0; i < FLOORS_QTY; i++)
    {
        for (unsigned j = 0; j < (FLOORTILE_QTY - 2); j++)
        {
            floorDeck.push_back(deck.back());            
            deck.pop_back();
        }
        floors.push_back(new Floor(floorDeck, i));
        floorDeck.clear();
    }
}

void Model::createModelFSM()
{
    Idle* idle = new Idle;
    WaitingFirstAction* waitingFirstAction = new WaitingFirstAction;
    WaitingSecondAction* waitingSecondAction = new WaitingSecondAction;
    WaitingResponse* waitingResponse = new WaitingResponse;
    PlayAgain* playAgain = new PlayAgain;
    End* end = new End;

    GameStep * FSMTempMatrix[STATE_COUNT][EVENT_COUNT] = //Creamos matriz temporal para luego copiar a la final
    {
        //VALID TILE            INVALID TILE            FREE MOVE           PAID MOVE              PEEK                    PASS                 ADD_DICE_TO_SAFE     ROLL_DICE_FOR_SAFE   HACK_COMPUTER        USE_HACK_TOKEN           OFFER_LOOT           REQUEST_LOOT         PICK_UP_LOOT         CREATE_ALARM         SPY_PATROL_DECK      PATROL_IS_TOP         PATROL_IS_BOTTOM        PLACE_CROW_TOKEN        WIN                  LOSE                 ACCEPT                  DECLINE                LOOT                    PATROL_CARD
        {waitingFirstAction,    idle,                   idle,               idle,                  idle,                   idle,                idle,                idle,                idle,                idle,                    idle,                idle,                idle,                idle,                waitingFirstAction,  idle,                 idle,                   idle,                   playAgain,           playAgain,           idle,                   idle,                  waitingFirstAction,     waitingFirstAction  },  //IDLE
        {idle,                  idle,                   idle,               waitingSecondAction,   idle,                   idle,                idle,                idle,                idle,                idle,                    waitingResponse,     waitingResponse,     idle,                idle,                waitingFirstAction,  idle,                 idle,                   idle,                   playAgain,           playAgain,           waitingFirstAction,     waitingFirstAction,    waitingFirstAction,     idle                }, //WAITING FOR FIRST ACTION
        {waitingSecondAction,   waitingSecondAction,    idle,               waitingSecondAction,   waitingSecondAction,    waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction,     waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction,  waitingSecondAction,    waitingSecondAction,    waitingSecondAction, waitingSecondAction, idle,                   idle,                  waitingSecondAction,    waitingSecondAction }, //WAITING FOR SECOND ACTION
        {waitingResponse,       waitingResponse,        waitingResponse,    waitingResponse,       waitingResponse,        waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,         waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,      waitingResponse,        waitingResponse,        waitingResponse,     waitingResponse,     idle,                   idle,                  waitingResponse,        waitingResponse     }, //WAITING FOR PLAYER RESPONSE
        {playAgain,             playAgain,              playAgain,          playAgain,             playAgain,              playAgain,           playAgain,           playAgain,           playAgain,           playAgain,               playAgain,           playAgain,           playAgain,           playAgain,           playAgain,           playAgain,            playAgain,              playAgain,              playAgain,           playAgain,           idle,                   end,                   playAgain,              playAgain           }, //PLAY AGAIN?
        {end,                   end,                    end,                end,                   end,                    end,                 end,                 end,                 end,                 end,                     end,                 end,                 end,                 end,                 end,                 end,                  end,                    end,                    end,                 end,                 end,                    end,                   end,                    end                 }, //EXIT GAME
    };
//Reglas: 1.Tiene que apretar su tile par poder poner un dice o roll dice en el safe tile
    //2. Tiene que apretar su tile para poder enable las acciones de offer loot, request loot y pick up loot
    //3. Tiene que apretar su tile para 
    gameHandlerMatrix = new GameStep**[STATE_COUNT];
    for (int i = 0; i < STATE_COUNT; i++)
    {
        gameHandlerMatrix[i] = new GameStep*[EVENT_COUNT]; //Alocamos las columnas

        for (int j = 0; j < EVENT_COUNT; j++)
        {
            gameHandlerMatrix[i][j] = FSMTempMatrix[i][j]; //copiamos celda a celda la matriz temporal
        }
    }

    this->currentAction = idle;
}

void Model::analyzeAction(gameData_t* gameData)
{
    gamePointers_t *gamePointers;           //cargamos estructura con los punteros del juego que se manda a model
    gamePointers->currentCharacter = this->currentCharacter;
    gamePointers->characters = this->characters;
    gamePointers->floors = this->floors;
    gamePointers->guards = this->guards;

    eventGenerator(gameData); //traduce de button_t a modelEvent para la fsm de model
    currentAction->eventHandler(gameData, gamePointers);
    currentAction = gameHandlerMatrix[currentAction->getState()][gameData->event];
    if (gameData->actionsLeft == 0)
    {
        gameData->event = A_PASS;
        currentAction->eventHandler(gameData, gamePointers);
        currentAction = gameHandlerMatrix[currentAction->getState()][gameData->event];
    }
    if (currentAction->getState() == IDLE)
        dynamic_cast <Idle*> (currentAction)->enableActions(gameData);
}

void Model::eventGenerator(gameData_t* gameData)
{
    if (gameWon)
        gameData->event = WIN;

    else if (gameLost)
        gameData->event = LOSE;

    else if ((int) gameData->preEvent >= (int) button_t::A1F1 && (int) gameData->preEvent <= (int) button_t::D4F3)
    {
        if (currentCharacter->canIUseThisTile((location_t) gameData->preEvent, &(gameData->selectedTile)))
            gameData->event = VALID_TILE;
        else
            gameData->event = INVALID_TILE;
    }
    else if (gameData->preEvent == button_t::PASS)
        gameData->event = A_PASS;

    else if (gameData->preEvent == button_t::MOVE)
    {
        std::vector< std::vector<Tile*> > deck = floors[getFloor(gameData->selectedTile.tile->getCurrentLocation())]->getDeck();
        std::vector< std::vector<Tile*> >::iterator row;
        std::vector<Tile*>::iterator col;

        row = deck.begin();
        col = row->begin();

        for (row = deck.begin(); row != deck.end() ; row++)
        {
            for (col = row->begin(); ((*col)->getCurrentLocation() == gameData->selectedTile.tile->getCurrentLocation()) &&
                    col != row->end(); col++);

            if ((*col)->getCurrentLocation() == gameData->selectedTile.tile->getCurrentLocation())
                break;
        }

        if ((*col)->isPaidMove())
            gameData->event = A_PAID_MOVE;
        else
            gameData->event = A_FREE_MOVE;
    }

    else if (gameData->preEvent == button_t::PEEK)
        gameData->event = A_PEEK;

    else if (gameData->preEvent == button_t::ADD_DICE_TO_SAFE)
        gameData->event = A_ADD_DICE_TO_SAFE;

    else if (gameData->preEvent == button_t::ROLL_DICE_FOR_SAFE)
        gameData->event = A_ROLL_DICE_FOR_SAFE;

    else if (gameData->preEvent == button_t::HACK_COMPUTER)
        gameData->event = A_HACK_COMPUTER;

    else if (gameData->preEvent == button_t::OFFER_LOOT)
        gameData->event = A_OFFER_LOOT;

    else if (gameData->preEvent == button_t::REQUEST_LOOT)
        gameData->event = A_REQUEST_LOOT;

    else if (gameData->preEvent == button_t::PICK_UP_LOOT)
        gameData->event = A_PICKUP_LOOT;

    else if (gameData->preEvent == button_t::CREATE_ALARM)
        gameData->event = A_CREATE_ALARM;

    else if (gameData->preEvent == button_t::SPY_PATROL_DECK)
        gameData->event = A_SPY_PATROL_DECK;

    else if (gameData->preEvent == button_t::PATROL_IS_TOP)
        gameData->event = A_PATROL_IS_TOP;

    else if (gameData->preEvent == button_t::PATROL_IS_BOTTOM)
        gameData->event = A_PATROL_IS_BOTTOM;

    else if (gameData->preEvent == button_t::PLACE_CROW_TOKEN)
        gameData->event = A_PLACE_CROW_TOKEN;

    else if (gameData->preEvent == button_t::ACCEPT)
        gameData->event = ACCEPT;

    else if (gameData->preEvent == button_t::DECLINE)
        gameData->event = DECLINE;

    else if (gameData->preEvent == button_t::LOOTF1 || gameData->preEvent == button_t::LOOTF2 || gameData->preEvent == button_t::LOOTF3)
        gameData->event = A_LOOT;

    else if (gameData->preEvent == button_t::PATROL_DECK_1 || gameData->preEvent == button_t::PATROL_DECK_2 || gameData->preEvent == button_t::PATROL_DECK_3)
        gameData->event = A_PATROL_CARD;

}

bool Model::isGameLost()
{
    
}

bool Model::isGameWon()
{
    
}

void Model::initGraphicsData(View* view, gameData_t* gameData)
{
    fillGraphicsData(view, gameData);
    
     for (unsigned floor = 1; floor < V_TOTAL_FLOORS; floor++)
    {
      
        view->graphicsData->guards[floor].movements = 0;
        view->graphicsData->guards[floor].location = locationV_t::NO_LOCATION;
        view->graphicsData->guards[floor].guardDie = locationV_t::NO_LOCATION;
        view->graphicsData->guards[floor].patrolDeck = patrolV_t::V_NO_PATROL;
    
     }
    
}

void Model::fillGraphicsData(View* view, gameData_t* gameData)
{

    view->graphicsData->gameLost = isGameLost();
    view->graphicsData->gameWon = isGameWon();
    view->graphicsData->currentCardSelected = gameData->preEvent;

    //players
    for (unsigned p = 0; p < V_TOTAL_PLAYERS; p++)
    {
        view->graphicsData->players[p].character = (characterV_t) characters[p]->getName();
        view->graphicsData->players[p].stealthTokens = characters[p]->getStealthTokensQty();
        view->graphicsData->players[p].location = (locationV_t) characters[p]->getLocation();
        view->graphicsData->players[p].actionsLeft = characters[p]->getActionsLeft();
    }
   

    for (unsigned floor = 0; floor < V_TOTAL_FLOORS; floor++)
    {
        if(floors[floor]->isGuardActive())
        {
            view->graphicsData->guards[floor].movements = floors[floor]->getGuardSpeed();
            view->graphicsData->guards[floor].location = (locationV_t) floors[floor]->getGuardLocation();
            view->graphicsData->guards[floor].guardDie = (locationV_t) floors[floor]->getGuardDestination();
            view->graphicsData->guards[floor].patrolDeck = (patrolV_t) floors[floor]->getGuardPatrolCard();
        }
        //loots
        for (unsigned j = 0; j < V_TOTAL_LOOTS; j++)
        {
            if (loots[j]->isLootVisible() == true)
            {
                view->graphicsData->loots[j].owner = (playerV_t) loots[j]->getOwner();
                view->graphicsData->loots[j].loot = (lootV_t) loots[j]->getLootName();
                view->graphicsData->loots[j].isVisible = true;
            }
            else
            {
                view->graphicsData->loots[j].owner = (playerV_t) NO_PLAYER;
                view->graphicsData->loots[j].isVisible = false;
            }
        }

        //tiles

        std::vector< std::vector<Tile*> >& deck = floors[floor]->getDeck();
        unsigned index = 0;
        for (unsigned row = 0; row < 4; row++)
        {
            for (unsigned col = 0; col < 4; col++)
            {
                index = floor * FLOORTILE_QTY + row * 4 + col;
                view->graphicsData->tiles[index].combinationNumber =  deck[row][col]->getCombinationNumber();
                view->graphicsData->tiles[index].goldBarOnTheLoose = deck[row][col]->isGoldBar()  ;        //hacer algo con esto


                if (!deck[row][col]->isTileVisible())
                    view->graphicsData->tiles[index].iAm = roomV_t::V_ROOMBACK;
                else
                    view->graphicsData->tiles[index].iAm = (roomV_t) deck[row][col]->getTileType();


                if (deck[row][col]->getTileType() == CR_FINGERPRINT)
                    view->graphicsData->tiles[index].howManyHackTokens = dynamic_cast < CRFingerprint* > (deck[row][col])->getHackTokensQty();
                else if (deck[row][col]->getTileType() == CR_LASER)
                    view->graphicsData->tiles[index].howManyHackTokens = dynamic_cast < CRLaser* > (deck[row][col])->getHackTokensQty();
                else if (deck[row][col]->getTileType() == CR_MOTION)
                    view->graphicsData->tiles[index].howManyHackTokens = dynamic_cast < CRMotion* > (deck[row][col])->getHackTokensQty();
                else
                    view->graphicsData->tiles[index].howManyHackTokens = 0;

                if (deck[row][col]->getTileType() == LAVATORY)
                    view->graphicsData->tiles[index].howManyStealthTokens = dynamic_cast < Lavatory* > (deck[row][col])->getStealthTokensQty();
                else
                    view->graphicsData->tiles[index].howManyStealthTokens = 0;

                //tokens
                for (unsigned k = 0; k < (int) tokenV_t::V_TOKEN_COUNT; k++)
                    view->graphicsData->tiles[index].tokens[k] = false;      //pongo en false todo el arreglo de tokens

                std::vector<token_t*>::iterator tokensIt;               //ver bien
                for (tokensIt = deck[row][col]->getTokens().begin(); tokensIt != deck[row][col]->getTokens().end(); tokensIt++)
                {
                    view->graphicsData->tiles[index].tokens[(unsigned) (*tokensIt)->token] = true;
                }
            }
        }
    }

    view->graphicsData->actions.acceptDecline = gameData->actions.acceptDecline;
    view->graphicsData->actions.addDice = gameData->actions.addDice;
    view->graphicsData->actions.createAlarm = gameData->actions.createAlarm;
    view->graphicsData->actions.hackCR = gameData->actions.hackCR;
    view->graphicsData->actions.move = gameData->actions.move;
    view->graphicsData->actions.offerLoot = gameData->actions.offerLoot;
    view->graphicsData->actions.pass = gameData->actions.pass;
    view->graphicsData->actions.patrolIsTopBottom = gameData->actions.patrolIsTopBottom;
    view->graphicsData->actions.peek = gameData->actions.peek;
    view->graphicsData->actions.pickupLoot = gameData->actions.pickupLoot;
    view->graphicsData->actions.placeCrowToken = gameData->actions.placeCrowToken;
    view->graphicsData->actions.requestLoot = gameData->actions.requestLoot;
    view->graphicsData->actions.rollDice = gameData->actions.rollDice;
    view->graphicsData->actions.spyPatrolDeck = gameData->actions.spyPatrolDeck;
    view->graphicsData->actions.useHackToken = gameData->actions.useHackToken;



    //    for (floorIt = floors.begin(); floorIt != floors.end(); floorIt++)
    //    {
    //        //guards
    //        view->graphicsData->guards[floorIt - floors.begin()].movements = (*floorIt)->getGuardSpeed();
    //        view->graphicsData->guards[floorIt - floors.begin()].location = (locationV_t) (*floorIt)->getGuardLocation();
    //        //view->graphicsData->guards[floorIt - floors.begin()].guardDie = (*floorIt)->getGuardDieLocation();
    //        //view->graphicsData->guards[floorIt - floors.begin()].patrolDeck = (*floorIt)->getPatrolCard();
    //
    //        //loots
    //        for (lootIt = loots.begin(); lootIt != loots.end(); lootIt++)
    //        {
    //            if ((*lootIt)->isLootVisible() == true)
    //            {
    //                view->graphicsData->loots[lootIt - loots.begin()].owner = (playerV_t) (*lootIt)->getOwner();
    //                view->graphicsData->loots[lootIt - loots.begin()].loot = (lootV_t) (*lootIt)->getLootName();
    //                view->graphicsData->loots[lootIt - loots.begin()].isVisible = true;
    //            }
    //            else
    //            {
    //                view->graphicsData->loots[lootIt - loots.begin()].owner = NO_PLAYER;
    //                view->graphicsData->loots[lootIt - loots.begin()].isVisible = false;
    //            }
    //        }
    //
    //        //tiles
    //        std::vector< std::vector<Tile*> > deck = (*floorIt)->getDeck();
    //        unsigned index = 0;
    //        for (unsigned i = 0; i < 4; i++)
    //        {
    //            for (unsigned j = 0; j < 4; j++)
    //            {
    //                index = (floorIt - floors.begin()) * FLOORTILE_QTY + i * 4 + j;
    //                view->graphicsData->tiles[index].combinationNumber =  deck[i][j]->getCombinationNumber();
    //                //            view->graphicsData->tiles[i].goldBarOnTheLoose = ;        //hacer algo con esto
    //
    //
    //                if (deck[i][j]->isTileVisible())
    //                    view->graphicsData->tiles[index].iAm = roomV_t::V_ROOMBACK;
    //                else
    //                    view->graphicsData->tiles[index].iAm = (roomV_t) deck[i][j]->getTileType();
    //
    //
    //                if (deck[i][j]->getTileType() == CR_FINGERPRINT)
    //                    view->graphicsData->tiles[index].howManyHackTokens = dynamic_cast < CRFingerprint* > (deck[i][j])->getHackTokensQty();
    //                else if (deck[i][j]->getTileType() == CR_LASER)
    //                    view->graphicsData->tiles[index].howManyHackTokens = dynamic_cast < CRLaser* > (deck[i][j])->getHackTokensQty();
    //                else if (deck[i][j]->getTileType() == CR_MOTION)
    //                    view->graphicsData->tiles[index].howManyHackTokens = dynamic_cast < CRMotion* > (deck[i][j])->getHackTokensQty();
    //                else
    //                    view->graphicsData->tiles[index].howManyHackTokens = 0;
    //
    //                if (deck[i][j]->getTileType() == LAVATORY)
    //                    view->graphicsData->tiles[index].howManyStealthTokens = dynamic_cast < Lavatory* > (deck[i][j])->getStealthTokensQty();
    //                else
    //                    view->graphicsData->tiles[index].howManyStealthTokens = 0;
    //
    //                //tokens
    //                for (unsigned k = 0; k < (int) tokenV_t::V_TOKEN_COUNT; k++)
    //                    view->graphicsData->tiles[index].tokens[k] = false;      //pongo en false todo el arreglo de tokens
    //
    //                std::vector<token_t*>::iterator tokensIt;
    //                for (tokensIt = deck[i][j]->getTokens()->begin(); tokensIt != deck[i][j]->getTokens()->end(); tokensIt++)
    //                {
    //                    view->graphicsData->tiles[index].tokens[(unsigned) (*tokensIt)->token] = true;
    //                }
    //
    //            }
    //
    //
    //
    //        }
    //
    //    }

}