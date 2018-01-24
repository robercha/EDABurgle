#include "Model.h"


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
    std::list<Tile*> deck; //toda la preparacion del juego, onda los random, las tiles etc
   
    unsigned i = 0;

    for (i = 0; i < ATRIUM_QTY; i++)
        deck.push_front(new Atrium);    
    for (i = 0; i < ATRIUM_QTY; i++)
        deck.push_front(new Atrium);
    for (i = 0; i < CAMERA_QTY; i++)
        deck.push_front(new Camera);
    for (i = 0; i < CROOM_FINGERPRINT_QTY; i++)
        deck.push_front(new CRFingerprint);
    for (i = 0; i < CROOM_LASER_QTY; i++)
        deck.push_front(new CRLaser);
    for (i = 0; i < CROOM_MOTION_QTY; i++)
        deck.push_front(new CRMotion);
    for (i = 0; i < DEADBOLT_QTY; i++)
        deck.push_front(new Deadbolt);
    for (i = 0; i < FINGERPRINT_QTY; i++)
        deck.push_front(new Fingerprint);    
    for (i = 0; i < FOYER_QTY; i++)
        deck.push_front(new Foyer);
    for (i = 0; i < KEYPAD_QTY; i++)
        deck.push_front(new Keypad);
    for (i = 0; i < LABORATORY_QTY; i++)
        deck.push_front(new Laboratory);
    for (i = 0; i < LASER_QTY; i++)
        deck.push_front(new Laser);

}

Model::Model(const Model& orig)
{

}

Model::~Model()
{
}

void
Model::analyzeAction(gameData_t*)
{

}

