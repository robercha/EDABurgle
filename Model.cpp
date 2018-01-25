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

    Idle* idle = new Idle;
    WaitingFirstAction* waitingFirstAction = new WaitingFirstAction;
    WaitingSecondAction* waitingSecondAction = new WaitingSecondAction;
    WaitingResponse* waitingResponse = new WaitingResponse;
    PlayAgain* playAgain = new PlayAgain;
    End* end = new End;

    GameStep * FSMTempMatrix[STATECOUNT][EVENTCOUNT] = //Creamos matriz temporal para luego copiar a la final
    {
        //VALID TILE            INVALID TILE    FREE MOVE                PAID MOVE              PEEK                    PASS                ADD_DICE_TO_SAFE    ROLL_DICE_FOR_SAFE  SPEND_ACTIONS_TO_ENTER      HACK_COMPUTER       USE_HACK_TOKEN          OFFER_LOOT          REQUEST_LOOT        PICK_UP_LOOT        CREATE_ALARM        SPY_PATROL_DECK     PATROL_IS_TOP       PATROL_IS_BOTTOM    PLACE_CROW_TOKEN    WIN             LOSE        ACCEPT                  DECLINE
        {waitingFirstAction,    idle,           idle,                      idle,                idle,                   idle,               idle,               idle,               idle,                       idle,               idle,                   waitingResponse,    waitingResponse,    idle,               idle,               waitingFirstAction, idle,               idle,               idle,               playAgain,      playAgain,  idle,                   idle }, //IDLE
        {waitingFirstAction,    idle,           idle,                      waitingSecondAction, waitingFirstAction,     waitingFirstAction, waitingFirstAction, waitingFirstAction, waitingFirstAction,         waitingFirstAction, waitingFirstAction,     waitingFirstAction, waitingFirstAction, waitingFirstAction, waitingFirstAction, waitingFirstAction, idle,               idle,               waitingFirstAction, playAgain,      playAgain,  waitingFirstAction,     waitingFirstAction }, //WAITING FOR FIRST ACTION
        {player2, player1}, //WAITING FOR SECOND ACTION
        {player2, player1}, //WAITING FOR PLAYER RESPONSE
        {player2, player1}, //PLAY AGAIN?
        {player2, player1}, //EXIT GAME

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

