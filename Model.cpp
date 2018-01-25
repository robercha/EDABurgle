#include "Model.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#define FLOORS_QTY 3
#define FLOORTILE_QTY 16
#define TOTALTILE_QTY 48

#define ATRIUM_QTY 2
#define CAMERA_QTY 4
#define CROOM_FINGERPRINT_QTY 1
#define CROOM_LASER_QTY 1
#define CROOM_MOTION_QTY 1
#define DEADBOLT_QTY 3
#define FINGERPRINT_QTY 3
#define FOYER_QTY 2
#define KEYPAD_QTY 3
#define LABORATORY_QTY 2
#define LASER_QTY 3
#define LAVATORY_QTY 1
#define MOTION_QTY 3
#define SAFE_QTY 3
#define SCANNER_DETECTOR_QTY 3
#define SECRET_DOOR_QTY 2
#define SERVICE_DUCT_QTY 2
#define STAIRS_QTY 3
#define THERMO_QTY 3
#define WALKWAY_QTY 3

Model::Model()
{
    unsigned i = 0;

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

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

    std::list<Tile*> finalDeck;

    for (i = 0; i < TOTALTILE_QTY; i++)
    {
        finalDeck.push_back(deck[i]);
    }

    for (i = 0; i < FLOORS_QTY; i++)
    {
        for (unsigned j = 0; j < FLOORTILE_QTY; j++)
        {
            floorDeck.push_back(finalDeck.back());
            finalDeck.pop_back();
        }
        floors[i] = new Floor(floorDeck);
    }

    GameStep * FSMTempMatrix[STATECOUNT][EVENTCOUNT] = //Creamos matriz temporal para luego copiar a la final
    {
<<<<<<< HEAD
        //VALID TILE    INVALID TILE    VALID ACTION0   INVALID ACTION0   VALID ACTION1   INVALID ACTION1   VALID ACTION2   INVALID ACTION2     WIN     LOSE    ACCEPT  DECLINE          
        {Player1,       player2},     //IDLE
        {player2,       player1},     //WAITING FOR FIRST ACTION
        {player2,       player1},     //WAITING FOR SECOND ACTION
        {player2,       player1},     //WAITING FOR PLAYER RESPONSE
        {player2,       player1},     //PLAY AGAIN?
        {player2,       player1},     //EXIT GAME
   
        
        
=======
        //ACTION  SWITCH_PLAYER
        {player1, player2}, //Player 1
        {player2, player1}, //Player 2
>>>>>>> bd4945f5860f96222a168f219343e0542f1c369a
    };

    gameHandlerMatrix = new GameStep**[STATECOUNT];
    for (int i = 0; i < STATECOUNT; i++)
    {
        gameHandlerMatrix[i] = new GameStep*[EVENTCOUNT]; //Alocamos las columnas

        for (int j = 0; j < EVENTCOUNT; j++)
        {
            gameHandlerMatrix[i][j] = FSMTempMatrix[i][j]; //copiamos celda a celda la matriz temporal
        }
    }

    //currentAction = player1; //SOLO DE PRUEBA;
    //event = NO_EVENT;
}

Model::~Model()
{
    unsigned i;
    for (i = 0; i < TOTALTILE_QTY; i++)
        delete deck[i];
}

void
Model::analyzeAction(gameData_t*)
{
    switch ()
    {
        case:
            break;
        default:
            break;
    }
}

