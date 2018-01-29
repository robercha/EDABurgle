#include <stdbool.h>

#include "Tile.h"

unsigned getColumn(location_t location);
unsigned getRow(location_t location);
unsigned getFloor(location_t location);

#define ROWS    4
#define COLS    4
#define FLOORS   3

typedef enum
{
    STEALTH, HACK, CRACKED, ALARM, DOWNSTAIRS, OPEN, CROW, KITTY, TOKEN_COUNT
} token_t;

Tile::Tile()
{
    alarmTile = false;
}

bool Tile::isAlarmTile()
{
    return alarmTile;
}

bool Tile::isTileValid(location_t selectedTile)
{
    bool isTileValid = isAdyacentTileValid(selectedTile);

    return isTileValid;

}

bool Tile::isAdyacentTileValid(location_t selectedTile)
{
    bool isTileValid = false;
    unsigned currRow = getRow(currentLocation);
    unsigned currCol = getColumn(currentLocation);
    unsigned currFloor = getFloor(currentLocation);

    unsigned selectedRow = getRow(selectedTile);
    unsigned selectedCol = getColumn(selectedTile);
    unsigned selectedFloor = getFloor(selectedTile);


    if (selectedFloor == currFloor)
    {
        if (selectedCol == (currCol + 1) || selectedCol == (currCol - 1))
        {
            if (selectedRow == (currRow + 1) || selectedRow == (currRow - 1))
            {
                if (selectedCol == (currCol + 1) && rightTile != NULL)
                    isTileValid = true;
                else if (selectedCol == (currCol - 1) && leftTile != NULL)
                    isTileValid = true;
                else if (selectedRow == (currRow + 1) && lowerTile != NULL)
                    isTileValid = true;
                else if (selectedRow == (currRow - 1) && upperTile != NULL)
                    isTileValid = true;
                else
                    isTileValid = false;
            }
        }
    }

    return isTileValid;
}

Tile::Tile(const Tile& orig)
{
}

Tile::~Tile()
{
}

void Tile::setCurrentLocation(location_t location)
{
    currentLocation = location;
}
void Tile::setAdjacentTiles(Tile* left, Tile* right, Tile* upper, Tile* lower)
{
    rightTile = right; secretRightTile = right;
    leftTile = left; secretLeftTile = left;
    upperTile = upper; secretUpperTile = upper;
    lowerTile = lower; secretLowerTile = lower;
}

void Tile::setLeftWall()
{
    leftTile = NULL;
}

void Tile::setRightWall()
{
    rightTile = NULL;
}

void Tile::setUpperWall()
{
    upperTile = NULL;
}

void Tile::setLowerWall()
{
    lowerTile = NULL;
}

unsigned getColumn(location_t location)
{
    unsigned floor = getFloor(location);
    unsigned index = (int) location - (floor) * ROWS*COLS;

    return index % COLS;
}

unsigned getRow(location_t location)
{
    unsigned floor = getFloor(location);
    unsigned index = (int) location - (floor) * ROWS*COLS;

    return (int) (index / COLS);
}

unsigned getFloor(location_t location)
{
    return ((int) location) / (ROWS * COLS);
}

bool Atrium::isTileValid(location_t selectedTile)
{
    bool isTileValid = false;

    if (isAdyacentTileValid(selectedTile) == true)
        isTileValid = true;
    else if (selectedTile == (currentLocation + ROWS * COLS) && upperFloorTile != NULL)
        isTileValid = true;
    else if (selectedTile == (currentLocation - ROWS * COLS) && lowerFloorTile != NULL)
        isTileValid = true;
    else
        isTileValid = false;
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
    // return (location == Camera) ? true : false;
}