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
        //VALID TILE            INVALID TILE            FREE MOVE           PAID MOVE              PEEK                    PASS                 ADD_DICE_TO_SAFE     ROLL_DICE_FOR_SAFE   HACK_COMPUTER        USE_HACK_TOKEN           OFFER_LOOT           REQUEST_LOOT         PICK_UP_LOOT         CREATE_ALARM         SPY_PATROL_DECK      PATROL_IS_TOP         PATROL_IS_BOTTOM        PLACE_CROW_TOKEN        WIN                  LOSE                 ACCEPT                  DECLINE                LOOT
        {waitingFirstAction,    idle,                   idle,               idle,                  idle,                   idle,                idle,                idle,                idle,                idle,                    idle,                idle,                idle,                idle,                waitingFirstAction,  idle,                 idle,                   idle,                   playAgain,           playAgain,           idle,                   idle,                  waitingFirstAction  },  //IDLE
        {waitingFirstAction,    idle,                   idle,               waitingSecondAction,   waitingFirstAction,     waitingFirstAction,  waitingFirstAction,  waitingFirstAction,  waitingFirstAction,  waitingFirstAction,      waitingResponse,     waitingResponse,     waitingFirstAction,  waitingFirstAction,  waitingFirstAction,  idle,                 idle,                   waitingFirstAction,     waitingFirstAction,  waitingFirstAction,  waitingFirstAction,     waitingFirstAction,    waitingFirstAction  }, //WAITING FOR FIRST ACTION
        {waitingSecondAction,   waitingSecondAction,    idle,               waitingSecondAction,   waitingSecondAction,    waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction,     waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction, waitingSecondAction,  waitingSecondAction,    waitingSecondAction,    waitingSecondAction, waitingSecondAction, idle,                   idle,                  waitingSecondAction }, //WAITING FOR SECOND ACTION
        {waitingResponse,       waitingResponse,        waitingResponse,    waitingResponse,       waitingResponse,        waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,         waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,     waitingResponse,      waitingResponse,        waitingResponse,        waitingResponse,     waitingResponse,     idle,                   idle,                  waitingResponse     }, //WAITING FOR PLAYER RESPONSE
        {playAgain,             playAgain,              playAgain,          playAgain,             playAgain,              playAgain,           playAgain,           playAgain,           playAgain,           playAgain,               playAgain,           playAgain,           playAgain,           playAgain,           playAgain,           playAgain,            playAgain,              playAgain,              playAgain,           playAgain,           idle,                   end,                   playAgain           }, //PLAY AGAIN?
        {end,                   end,                    end,                end,                   end,                    end,                 end,                 end,                 end,                 end,                     end,                 end,                 end,                 end,                 end,                 end,                  end,                    end,                    end,                 end,                 end,                    end,                   end                 }, //EXIT GAME
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

void Model::eventGenerator(button_t event, gameData_t gameData)
{




    switch (event)
    {
        case A1F1: case B1F1: case C1F1: case D1F1: case A2F1: case B2F1: case C2F1: case D2F1:
        case A3F1: case B3F1: case C3F1: case D3F1: case A4F1: case B4F1: case C4F1: case D4F1:
        case A1F2: case B1F2: case C1F2: case D1F2: case A2F2: case B2F2: case C2F2: case D2F2:
        case A3F2: case B3F2: case C3F2: case D3F2: case A4F2: case B4F2: case C4F2: case D4F2:
        case A1F3: case B1F3: case C1F3: case D1F3: case A2F3: case B2F3: case C2F3: case D2F3:
        case A3F3: case B3F3: case C3F3: case D3F3: case A4F3: case B4F3: case C4F3: case D4F3: ;
    }
}