#include "Model.h"
//#include "Player.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <time.h>

Model::Model(gameData_t* gameData)
{
    initGameData(gameData);
    std::vector<Tile*> deck;
    createTiles(deck);
    shuffleTiles(deck);

    this->gamePointers = new gamePointers_t;

    createFloors(deck);
    createModelFSM();
    createLoots();
    createCharacters();

}

Model::~Model()
{
    unsigned i;
    for (i = 0; i < FLOORS_QTY; i++)
        delete gamePointers->floors[i];
}

void Model::initGameData(gameData_t* gameData)
{
    gameData->actions.acceptDecline = false;
    gameData->actions.addDice = false;
    gameData->actions.createAlarm = false;
    gameData->actions.hackCR = false;
    gameData->actions.move = false;
    gameData->actions.offerLoot = false;
    gameData->actions.pass = true;
    gameData->actions.patrolIsTopBottom = false;
    gameData->actions.peek = false;
    gameData->actions.pickupLoot = false;
    gameData->actions.placeCrowToken = false;
    gameData->actions.requestLoot = false;
    gameData->actions.rollDice = false;
    gameData->actions.spyPatrolDeck = false;
    gameData->actions.useHackToken = false;


    gameData->currentCharacter = 0;
    gameData->selectedTile.tile = NULL;
    gameData->selectedTile.adyacent = false;
    gameData->selectedTile.hawkWall = false;
    gameData->selectedTile.ownTile = false;
    gameData->selectedTile.serviceDuct = false;
    gameData->selectedTile.twoTilesAwayTile = false;

}

void Model::createLoots()
{
    std::vector<Loot*> loots;
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
    for (unsigned i = 0; i < FLOORS_QTY; i++)
    {
        gamePointers->floors[i]->setLoot(loots.back());
        loots.pop_back();
    }

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
    gamePointers->characters.push_back(new Juicer);
    gamePointers->characters.push_back(new Acrobat);
    gamePointers->characters.push_back(new Hacker);
    gamePointers->characters.push_back(new Hawk);
    gamePointers->characters.push_back(new Spotter);
    gamePointers->characters.push_back(new Raven);
    gamePointers->characters.push_back(new Peterman);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(gamePointers->characters.begin(), gamePointers->characters.end(), std::default_random_engine(seed));

    for (std::vector<Character*>::iterator charIt = gamePointers->characters.end(); charIt != (gamePointers->characters.begin() + 2); charIt--)     //shuffleo y saco 5 (de 7) para que queden los dos jugadores
        gamePointers->characters.pop_back();

    srand(time(NULL));
    unsigned initialRow = rand() % 4;
    unsigned initialCol = rand() % 4;

    gamePointers->floors[0]->getDeck()[initialRow][initialCol]->reveal();
    gamePointers->characters[0]->setInitialTile(gamePointers->floors[0]->getDeck()[initialRow][initialCol]);
    gamePointers->characters[1]->setInitialTile(gamePointers->floors[0]->getDeck()[initialRow][initialCol]);
    gamePointers->currentCharacter = gamePointers->characters[0];

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
        gamePointers->floors.push_back(new Floor(floorDeck, i));
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
        {waitingSecondAction,   waitingSecondAction,    waitingSecondAction,waitingSecondAction,   waitingSecondAction,    waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction,     waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction,  waitingSecondAction,    waitingSecondAction,    waitingSecondAction, waitingSecondAction, idle,                   idle,                  waitingSecondAction,    waitingSecondAction }, //WAITING FOR SECOND ACTION
        {waitingResponse,       waitingResponse,        waitingResponse,    waitingResponse,       waitingResponse,        waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,         waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,      waitingResponse,        waitingResponse,        waitingResponse,     waitingResponse,     idle,                   idle,                  waitingResponse,        waitingResponse     }, //WAITING FOR PLAYER RESPONSE
        {playAgain,             playAgain,              playAgain,          playAgain,             playAgain,              playAgain,           playAgain,           playAgain,           playAgain,           playAgain,               playAgain,           playAgain,           playAgain,           playAgain,           playAgain,           playAgain,            playAgain,              playAgain,              playAgain,           playAgain,           idle,                   end,                   playAgain,              playAgain           }, //PLAY AGAIN?
        {end,                   end,                    end,                end,                   end,                    end,                 end,                 end,                 end,                 end,                     end,                 end,                 end,                 end,                 end,                 end,                  end,                    end,                    end,                 end,                 end,                    end,                   end,                    end                 }, //EXIT GAME
    };
    //Reglas: 1.Tiene que apretar su tile par poder poner un dice o roll dice en el safe tile
    //2. Tiene que apretar su tile para poder enable las acciones de offer loot, request loot y pick up loot
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

bool Model::analyzeAction(gameData_t* gameData)
{
    bool noActions = false;

    eventGenerator(gameData); //traduce de button_t a modelEvent para la fsm de model
    currentAction->eventHandler(gameData, gamePointers);
    currentAction = gameHandlerMatrix[currentAction->getState()][gameData->event];

    if (gamePointers->currentCharacter->getActionsLeft() == 0)
    {
        gameData->event = A_PASS;
        currentAction->eventHandler(gameData, gamePointers);
        currentAction = gameHandlerMatrix[currentAction->getState()][gameData->event];

        noActions = true;
    }
//    if (currentAction->getState() == IDLE)
//        dynamic_cast <Idle*> (currentAction)->enableActions(gameData, gamePointers);

    return noActions;
}

void Model::eventGenerator(gameData_t* gameData)
{
    if (gameWon)
        gameData->event = WIN;

    else if (gameLost)
        gameData->event = LOSE;

    else if ((int) gameData->preEvent >= (int) button_t::A1F1 && (int) gameData->preEvent <= (int) button_t::D4F3)
    {
        if (gamePointers->currentCharacter->canIUseThisTile((location_t) gameData->preEvent, &(gameData->selectedTile)))
            gameData->event = VALID_TILE;
        else
            gameData->event = INVALID_TILE;
    }
    else if (gameData->preEvent == button_t::PASS)
        gameData->event = A_PASS;

    else if (gameData->preEvent == button_t::MOVE)
    {
        std::vector< std::vector<Tile*> > deck = gamePointers->floors[getFloor(gameData->selectedTile.tile->getCurrentLocation())]->getDeck();
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
    view->graphicsData->currentCardSelected = (button_t)this->gamePointers->currentCharacter->getLocation();
    view->graphicsData->message = "Hi there bosss. Ready to rob the s*** outta this bank.";
}

void Model::fillGraphicsData(View* view, gameData_t* gameData)
{

    view->graphicsData->gameLost = isGameLost();
    view->graphicsData->gameWon = isGameWon();
    view->graphicsData->currentCardSelected = gameData->preEvent;
    view->graphicsData->message = gameData->message;
    if (gamePointers->characters[0]->getName() == gamePointers->currentCharacter->getName())
    {
        view->graphicsData->players[0].currentChar = true;
        view->graphicsData->players[1].currentChar = false;
    }
    else
    {
        view->graphicsData->players[0].currentChar = false;
        view->graphicsData->players[1].currentChar = true;
    }

    //players
    for (unsigned p = 0; p < V_TOTAL_PLAYERS; p++)
    {
        view->graphicsData->players[p].character = (characterV_t) gamePointers->characters[p]->getName();
        view->graphicsData->players[p].stealthTokens = gamePointers->characters[p]->getStealthTokensQty();
        view->graphicsData->players[p].location = (locationV_t) gamePointers->characters[p]->getLocation();
        view->graphicsData->players[p].actionsLeft = gamePointers->characters[p]->getActionsLeft();
    }


    for (unsigned floor = 0; floor < V_TOTAL_FLOORS; floor++)
    {
        if (gamePointers->floors[floor]->isGuardActive())
        {
            view->graphicsData->guards[floor].movements = gamePointers->floors[floor]->getGuardSpeed();
            view->graphicsData->guards[floor].location = (locationV_t) gamePointers->floors[floor]->getGuardLocation();
            view->graphicsData->guards[floor].guardDie = (locationV_t) gamePointers->floors[floor]->getGuardDestination();
            view->graphicsData->guards[floor].patrolDeck = (patrolV_t) gamePointers->floors[floor]->getGuardPatrolCard();
        }
        //loots
        if (gamePointers->floors[floor]->getLootVisibility() == true)
        {
            view->graphicsData->loots[floor].isVisible = true;
            view->graphicsData->loots[floor].loot = (lootV_t) gamePointers->floors[floor]->getLootName();
            view->graphicsData->loots[floor].owner = (playerV_t) gamePointers->floors[floor]->getLootOwner();

        }
        else
        {
            view->graphicsData->loots[floor].isVisible = false;
            view->graphicsData->loots[floor].loot = lootV_t::V_NO_LOOT;
            view->graphicsData->loots[floor].owner = playerV_t::V_NO_PLAYER;

        }

        //tiles

        std::vector< std::vector<Tile*> >& deck = gamePointers->floors[floor]->getDeck();
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

}
