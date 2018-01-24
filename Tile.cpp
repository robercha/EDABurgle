
#include "Tile.h"

typedef enum
{
    STEALTH, HACK, CRACKED, ALARM, DOWNSTAIRS, OPEN, CROW, KITTY, TOKEN_COUNT
} token_t;

Tile::Tile()
{
}

Tile::Tile(const Tile& orig)
{
}

Tile::~Tile()
{
}

bool
Camera::itsATrap()
{
    //en model
    //if(isOnCamera(tile del guardia) && (isOnCamera(tile del player1)||isOnCamera(tile del player2) ))
    //camera->itsatrap();
    if (isOnCamera(tileP1))
        tileP1->triggerAlarm();

    if (isOnCamera(tileP2))
        tileP2->triggerAlarm();
}

bool
Camera::itsATrap()
{
    //en model
    //if(isOnCamera(tile del guardia) && (isOnCamera(tile del player1)||isOnCamera(tile del player2) ))
    //camera->itsatrap();
    if (isOnCamera(tileP1))
        tileP1->triggerAlarm();

    if (isOnCamera(tileP2))
        tileP2->triggerAlarm();

    return true;
}

bool
Camera::isOnCamera(Tile* location)
{
    return (location == Camera) ? true : false;
}