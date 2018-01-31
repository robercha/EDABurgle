#include "Model.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

Model::Model()
{
    std::vector<Tile*> deck;

    createTiles(deck);
    shuffleTiles(deck);
    createFloors(deck);
    createModelFSM();
    createLoots();
    fillGraphicsData();
    //currentAction = player1; //SOLO DE PRUEBA;
    //event = NO_EVENT;




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

void Model::createTiles(std::vector<Tile*> deck)
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
        floors[i] = new Floor(floorDeck);
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
        {waitingFirstAction,    idle,                   idle,               waitingSecondAction,   waitingFirstAction,     waitingFirstAction,  waitingFirstAction,  waitingFirstAction,  waitingFirstAction,  waitingFirstAction,      waitingResponse,     waitingResponse,     waitingFirstAction,  waitingFirstAction,  waitingFirstAction,  idle,                 idle,                   waitingFirstAction,     waitingFirstAction,  waitingFirstAction,  waitingFirstAction,     waitingFirstAction,    waitingFirstAction,     waitingFirstAction  }, //WAITING FOR FIRST ACTION
        {waitingSecondAction,   waitingSecondAction,    idle,               waitingSecondAction,   waitingSecondAction,    waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction,     waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction,  waitingSecondAction,    waitingSecondAction,    waitingSecondAction, waitingSecondAction, idle,                   idle,                  waitingSecondAction,    waitingSecondAction }, //WAITING FOR SECOND ACTION
        {waitingResponse,       waitingResponse,        waitingResponse,    waitingResponse,       waitingResponse,        waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,         waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,      waitingResponse,        waitingResponse,        waitingResponse,     waitingResponse,     idle,                   idle,                  waitingResponse,        waitingResponse     }, //WAITING FOR PLAYER RESPONSE
        {playAgain,             playAgain,              playAgain,          playAgain,             playAgain,              playAgain,           playAgain,           playAgain,           playAgain,           playAgain,               playAgain,           playAgain,           playAgain,           playAgain,           playAgain,           playAgain,            playAgain,              playAgain,              playAgain,           playAgain,           idle,                   end,                   playAgain,              playAgain           }, //PLAY AGAIN?
        {end,                   end,                    end,                end,                   end,                    end,                 end,                 end,                 end,                 end,                     end,                 end,                 end,                 end,                 end,                 end,                  end,                    end,                    end,                 end,                 end,                    end,                   end,                    end                 }, //EXIT GAME
    };

    gameHandlerMatrix = new GameStep**[STATE_COUNT];
    for (int i = 0; i < STATE_COUNT; i++)
    {
        gameHandlerMatrix[i] = new GameStep*[EVENT_COUNT]; //Alocamos las columnas

        for (int j = 0; j < EVENT_COUNT; j++)
        {
            gameHandlerMatrix[i][j] = FSMTempMatrix[i][j]; //copiamos celda a celda la matriz temporal
        }
    }

}

void Model::analyzeAction(gameData_t*)
{
    switch ()
    {
        case:
            break;
        default:
            break;
    }
}
//    VALID_TILE, INVALID_TILE, A_PASS, A_FREE_MOVE, A_PAID_MOVE, A_PEEK, A_ADD_DICE_TO_SAFE,
//    A_ROL_DICE_FOR_SAFE, A_HACK_COMPUTER, A_USE_HACK_TOKEN, A_OFFER_LOOT,
//    A_REQUEST_LOOT, A_PICKUP_LOOT, A_CREATE_ALARM, A_SPY_PATROL_DECK, A_PATROL_IS_TOP,
//    A_PATROL_IS_BOTTOM, A_PLACE_CROW_TOKEN, WIN, LOSE, ACCEPT, DECLINE, LOOT, PATROL_CARD, EVENT_COUNT

void Model::eventGenerator(button_t event, gameData_t* gameData)
{
    if ((int) event >= (int) button_t::A1F1 && (int) event <= (int) button_t::D4F3)
    {
        if (currentCharacter->canIUseThisTile((location_t) event))
            gameData->event = VALID_TILE;
        else
            gameData->event = INVALID_TILE;
    }

    else if (event == button_t::PASS)
        gameData->event = A_PASS;
    else if (event == button_t::MOVE)
    {
        std::vector<Tile*>* deck = floors[getFloor(gameData->selectedTile)]->getDeck();
        std::vector<Tile*>::iterator it;
        it = deck->begin();
        while (it->getCurrentLocation() == gameData->selectedTile)
            it++;

        if (it->isPaidMove())
            gameData->event = A_PAID_MOVE;
        else
            gameData->event = A_FREE_MOVE;
    }




}

void Model::fillGraphicsData(View* view)
{

    view->graphicsData->gameLost = isGameLost();
    view->graphicsData->gameWon = isGameWon();

    std::vector<Character*>::iterator characterIt;
    std::vector<Floor*>::iterator floorIt;
    std::vector<Loot*>::iterator lootIt;

    //players
    for (characterIt = characters.begin(); characterIt != characters.end(); characterIt++)
    {
        view->graphicsData->players[characterIt - characters.begin()].character = (characterV_t) (*characterIt)->getName();
        view->graphicsData->players[characterIt - characters.begin()].stealthTokens = (*characterIt)->getStealthTokensQty();
        view->graphicsData->players[characterIt - characters.begin()].location = (locationV_t) (*characterIt)->getLocation();
        view->graphicsData->players[characterIt - characters.begin()].actionsLeft = (*characterIt)->getActionsLeft();
    }

    for (floorIt = floors.begin(); floorIt = floors.end(); floorIt++)
    {
        //guards
        view->graphicsData->guards[floorIt - floors.begin()].movements = (*floorIt)->getGuardSpeed();
        view->graphicsData->guards[floorIt - floors.begin()].location = (locationV_t) (*floorIt)->getGuardLocation();
        //view->graphicsData->guards[floorIt - floors.begin()].guardDie = (*floorIt)->getGuardDieLocation();
        //view->graphicsData->guards[floorIt - floors.begin()].patrolDeck = (*floorIt)->getPatrolCard();

        //loots
        for (lootIt = loots.begin(); lootIt = loots.end(); lootIt++)
        {
            if ((*lootIt)->isLootVisible() == true)
            {
                view->graphicsData->loots[lootIt - loots.begin()].owner = (playerV_t) (*lootIt)->getOwner();
                view->graphicsData->loots[lootIt - loots.begin()].loot = (lootV_t) (*lootIt)->getLootName();
                view->graphicsData->loots[lootIt - loots.begin()].isVisible = true;
            }
            else
            {
                view->graphicsData->loots[lootIt - loots.begin()].owner = NO_PLAYER;
                view->graphicsData->loots[lootIt - loots.begin()].isVisible = false;
            }
        }

        //tiles
        std::vector<Tile*>* deck = (*floorIt)->getDeck();
        std::vector<Tile*>::iterator it = deck->begin();
        for (unsigned i = FLOORTILE_QTY * (floorIt - floors.begin()); i < FLOORTILE_QTY * (++floorIt - floors.begin()); i++, it++, --floorIt)
        {
            view->graphicsData->tiles[i].combinationNumber =  (*it)->getCombinationNumber();
            //            view->graphicsData->tiles[i].goldBarOnTheLoose = ;        //hacer algo con esto

            if ((*it)->isTileVisible())
                view->graphicsData->tiles[i].iAm = roomV_t::V_ROOMBACK;
            else
                view->graphicsData->tiles[i].iAm = (roomV_t) (*it)->getTileType();


            if ((*it)->getTileType() == CR_FINGERPRINT)
                view->graphicsData->tiles[i].howManyHackTokens = ((CRFingerprint) (*it))->getHackTokensQty();
            else if ((*it)->getTileType() == CR_LASER)
                view->graphicsData->tiles[i].howManyHackTokens = ((CRLaser) (*it))->getHackTokensQty();
            else if ((*it)->getTileType() == CR_MOTION)
                view->graphicsData->tiles[i].howManyHackTokens = ((CRMotion) (*it))->getHackTokensQty();
            else
                view->graphicsData->tiles[i].howManyHackTokens = 0;

            if ((*it)->getTileType() == LAVATORY)
                view->graphicsData->tiles[i].howManyStealthTokens = ((Lavatory) (*it))->getStealthTokensQty();
            else
                view->graphicsData->tiles[i].howManyStealthTokens = 0;

            //tokens; lo que hay que hacer que lo dejamos para mañana es cargar el arreglo de tokens   
            std::vector<token_t*>::iterator tokensIt;


        }



    }




    std::vector<Tile*>::iterator tileIt;
    for (floorIt = floors.begin(); floorIt != floors.end(); floorIt++)
    {

        view->graphicsData->tiles[i].iAm = roomV_t::V_ROOMBACK;
        view->graphicsData->tiles[i].goldBarOnTheLoose = false;
    }
    view->graphicsData->tiles[46].goldBarOnTheLoose = true;


    //    for (unsigned i = 0; i < 3; i++)
    //    {
    //        view->graphicsData->loots[i].loot = loot_t::TIARA;
    //                view->graphicsData->loots[i].owner = YOU;
    //    }
    //    view->graphicsData->currentCardSelected = button_t::A1F1;
    //    for (unsigned i = 0; i < 8; i++)
    //            view->graphicsData->tiles[(int) button_t::A2F1].tokens[i] = true;
    //            view->graphicsData->tiles[(int) button_t::A2F1].tokens[1] = false;
    //
    //        for (unsigned i = 0; i < 8; i++)
    //                view->graphicsData->tiles[(int) button_t::A1F1].tokens[i] = true;
    //
    //        }
}