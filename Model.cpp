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
//A1F1, B1F1, C1F1, D1F1, A2F1, B2F1, C2F1, D2F1, A3F1, B3F1, C3F1, D3F1, A4F1, B4F1, C4F1, D4F1,
//    A1F2, B1F2, C1F2, D1F2, A2F2, B2F2, C2F2, D2F2, A3F2, B3F2, C3F2, D3F2, A4F2, B4F2, C4F2, D4F2,
//    A1F3, B1F3, C1F3, D1F3, A2F3, B2F3, C2F3, D2F3, A3F3, B3F3, C3F3, D3F3, A4F3, B4F3, C4F3, D4F3,

void Model::eventGenerator(button_t event, gameData_t* gameData)
{
    if ((int) event >= (int) button_t::A1F1 && (int) event <= (int) button_t::D4F3)
    {
        if (currentCharacter->canIUseThisTile((location_t) event))
            gameData->event = VALID_TILE;
        else
            gameData->event = INVALID_TILE;
    }



}

void Model::fillGraphicsData(View* view)
{

    view->graphicsData->gameLost = isGameLost();
    view->graphicsData->gameWon = isGameWon();

    //players
    view->graphicsData->players[0].character = (characterV_t) characters.at(0)->getName();
    view->graphicsData->players[0].stealthTokens = characters.at(0)->getStealthTokensQty();
    view->graphicsData->players[0].location = (locationV_t) characters.at(0)->getLocation();
    view->graphicsData->players[0].actionsLeft = characters.at(0)->getActionsLeft();
    view->graphicsData->players[0].character = (characterV_t) characters.at(1)->getName();
    view->graphicsData->players[0].stealthTokens = characters.at(1)->getStealthTokensQty();
    view->graphicsData->players[0].location = (locationV_t) characters.at(1)->getLocation();
    view->graphicsData->players[0].actionsLeft = characters.at(1)->getActionsLeft();

    //guards
    //view->graphicsData->guards[0].location = location_t::;
    //view->graphicsData->guards[1].location = location_t::;
    //view->graphicsData->guards[2].location = location_t::;
    //view->graphicsData->guards[0].patrolDeck = patrol_t::;
    //view->graphicsData->guards[1].patrolDeck = patrol_t::;
    //view->graphicsData->guards[2].patrolDeck = patrol_t::;
    view->graphicsData->guards[0].movements = 2;
    view->graphicsData->guards[1].movements = 3;
    view->graphicsData->guards[2].movements = 4;
    //    view->graphicsData->guards[0].guardDie = location_t::;
    //    view->graphicsData->guards[1].guardDie = location_t::;
    //    view->graphicsData->guards[2].guardDie = location_t::;


    std::vector<Floor*>::iterator floorIt;
    std::vector<Tile*>::iterator tileIt;
    for (floorIt = floors.begin(); floorIt != floors.end(); floorIt++)
    {
        for (tileIt = (*floorIt).
                view->graphicsData->tiles[i].iAm = room_t::ROOMBACK;
                view->graphicsData->tiles[i].goldBarOnTheLoose = false;
        }
    view->graphicsData->tiles[46].goldBarOnTheLoose = true;

            view->graphicsData->tiles[0].iAm = room_t::LAVATORY;
            view->graphicsData->tiles[0].combinationNumber = 1;
            view->graphicsData->tiles[0].howManyStealthTokens = 1;
            view->graphicsData->tiles[1].iAm = room_t::CR_FINGERPRINT;
            view->graphicsData->tiles[1].combinationNumber = 2;
            view->graphicsData->tiles[1].howManyHackTokens = 6;
            view->graphicsData->tiles[4].iAm = room_t::CR_LASER;
            view->graphicsData->tiles[4].combinationNumber = 3;
            view->graphicsData->tiles[5].iAm = room_t::CR_MOTION;
            view->graphicsData->tiles[5].combinationNumber = 4;
            view->graphicsData->tiles[6].iAm = room_t::DEADBOLT;
            view->graphicsData->tiles[6].combinationNumber = 5;
            view->graphicsData->tiles[7].iAm = room_t::ATRIUM;
            view->graphicsData->tiles[7].combinationNumber = 6;
            view->graphicsData->tiles[20].iAm = room_t::DETECTOR;
            view->graphicsData->tiles[20].combinationNumber = 1;
            view->graphicsData->tiles[22].iAm = room_t::FINGERPRINT;
            view->graphicsData->tiles[22].combinationNumber = 2;
            view->graphicsData->tiles[23].iAm = room_t::FOYER;
            view->graphicsData->tiles[23].combinationNumber = 3;
            view->graphicsData->tiles[26].iAm = room_t::KEYPAD;
            view->graphicsData->tiles[26].combinationNumber = 4;
            view->graphicsData->tiles[27].iAm = room_t::LABORATORY;
            view->graphicsData->tiles[27].combinationNumber = 5;
            view->graphicsData->tiles[29].iAm = room_t::LASER;
            view->graphicsData->tiles[29].combinationNumber = 6;
            view->graphicsData->tiles[30].iAm = room_t::LAVATORY;
            view->graphicsData->tiles[30].combinationNumber = 1;
            view->graphicsData->tiles[32].iAm = room_t::MOTION;
            view->graphicsData->tiles[32].combinationNumber = 2;
            view->graphicsData->tiles[34].iAm = room_t::ROOMBACK;
            view->graphicsData->tiles[34].combinationNumber = 3;
            view->graphicsData->tiles[35].iAm = room_t::SAFE;
            view->graphicsData->tiles[35].combinationNumber = 4;
            view->graphicsData->tiles[37].iAm = room_t::SECRETDOOR;
            view->graphicsData->tiles[37].combinationNumber = 5;
            view->graphicsData->tiles[39].iAm = room_t::SERVICEDUCT;
            view->graphicsData->tiles[39].combinationNumber = 6;
            view->graphicsData->tiles[32].iAm = room_t::MOTION;
            view->graphicsData->tiles[32].combinationNumber = 2;
            view->graphicsData->tiles[34].iAm = room_t::ROOMBACK;
            view->graphicsData->tiles[34].combinationNumber = 3;
            view->graphicsData->tiles[35].iAm = room_t::SAFE;
            view->graphicsData->tiles[35].combinationNumber = 4;
            view->graphicsData->tiles[37].iAm = room_t::SECRETDOOR;
            view->graphicsData->tiles[37].combinationNumber = 5;
            view->graphicsData->tiles[39].iAm = room_t::SERVICEDUCT;
            view->graphicsData->tiles[39].combinationNumber = 6;
            view->graphicsData->tiles[41].iAm = room_t::STAIRS;
            view->graphicsData->tiles[41].combinationNumber = 2;
            view->graphicsData->tiles[43].iAm = room_t::THERMO;
            view->graphicsData->tiles[43].combinationNumber = 3;
            view->graphicsData->tiles[44].iAm = room_t::WALKWAY;
            view->graphicsData->tiles[44].combinationNumber = 4;
            view->graphicsData->tiles[46].iAm = room_t::FOYER;
            view->graphicsData->tiles[46].combinationNumber = 5;
            view->graphicsData->tiles[47].iAm = room_t::SAFE;
            view->graphicsData->tiles[47].combinationNumber = 6;

    for (unsigned i = 0; i < 3; i++)
    {
        view->graphicsData->loots[i].loot = loot_t::TIARA;
                view->graphicsData->loots[i].owner = YOU;
    }
    view->graphicsData->currentCardSelected = button_t::A1F1;
    for (unsigned i = 0; i < 8; i++)
            view->graphicsData->tiles[(int) button_t::A2F1].tokens[i] = true;
            view->graphicsData->tiles[(int) button_t::A2F1].tokens[1] = false;

        for (unsigned i = 0; i < 8; i++)
                view->graphicsData->tiles[(int) button_t::A1F1].tokens[i] = true;

        }