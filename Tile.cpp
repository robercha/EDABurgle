#include <stdbool.h>

#include "Tile.h"
#include "View.h"

#define ROWS    4
#define COLS    4
#define FLOORS   3

Atrium::Atrium()
{
    tileType = ATRIUM;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Camera::Camera()
{
    tileType = CAMERA;
    alarmTile = true;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

CRFingerprint::CRFingerprint()
{
    tileType = CR_FINGERPRINT;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

CRLaser::CRLaser()
{
    tileType = CR_LASER;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

CRMotion::CRMotion()
{
    tileType = CR_MOTION;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Deadbolt::Deadbolt()
{
    tileType = DEADBOLT;
    alarmTile = false;
    mustSpendActions = true;
    isVisible = false;
    combinationNumber = 0;
}

Detector::Detector()
{
    tileType = DETECTOR;
    alarmTile = true;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Fingerprint::Fingerprint()
{
    tileType = FINGERPRINT;
    alarmTile = true;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Foyer::Foyer()
{
    tileType = FOYER;
    alarmTile = true;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Keypad::Keypad()
{
    tileType = KEYPAD;
    alarmTile = false;
    mustSpendActions = true; //le preguntamos al user si quiere tirar los dados para abrir el keypad
    isVisible = false;
    combinationNumber = 0;
}

Laboratory::Laboratory()
{
    tileType = LABORATORY;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Laser::Laser()
{
    tileType = LASER;
    alarmTile = true;
    mustSpendActions = true;
    isVisible = false;
    combinationNumber = 0;
}

Lavatory::Lavatory()
{
    tileType = LAVATORY;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Motion::Motion()
{
    tileType = MOTION;
    alarmTile = true;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Safe::Safe()
{
    tileType = SAFE;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

SecretDoor::SecretDoor()
{
    tileType = SECRETDOOR;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

ServiceDuct::ServiceDuct()
{
    tileType = SERVICEDUCT;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Stairs::Stairs()
{
    tileType = STAIRS;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Thermo::Thermo()
{
    tileType = THERMO;
    alarmTile = true;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

Walkway::Walkway()
{
    tileType = WALKWAY;
    alarmTile = false;
    mustSpendActions = false;
    isVisible = false;
    combinationNumber = 0;
}

void Tile::setJuicerAlarm()
{
    this->alarmTile = true;
}

tileType_t Tile::getTileType()
{
    return tileType;
}

unsigned Tile::getCombinationNumber()
{
    return combinationNumber;
}

Tile* Tile::getRightTile()
{
    return this->rightTile;
}

Tile* Tile::getLeftTile()
{
    return this->leftTile;
}

Tile* Tile::getUpperTile()
{
    return this->upperTile;
}

Tile* Tile::getLowerTile()
{
    return this->lowerTile;
}

bool Tile::isAlarmTile()
{
    return alarmTile;
}

bool Tile::isPaidMove()
{
    return mustSpendActions;
}

location_t Tile::getCurrentLocation()
{
    return currentLocation;
};

bool Tile::checkDurlock(location_t selectedTile)
{
    bool wall = false;
    if (selectedTile == secretRightTile->currentLocation || selectedTile == secretLeftTile->currentLocation ||
            selectedTile == secretUpperTile->currentLocation || selectedTile == secretLowerTile->currentLocation)
        wall = true;

    return wall;
}

bool Tile::isTileTwoTilesAway(location_t selectedTile)
{
    bool isTileValid = false;
    if (rightTile != NULL && rightTile->rightTile != NULL)
        if (selectedTile == rightTile->rightTile->currentLocation)
            isTileValid = true;
    if (leftTile != NULL && leftTile->leftTile != NULL)
        if (selectedTile == leftTile->leftTile->currentLocation)
            isTileValid = true;
    if (upperTile != NULL && upperTile->upperTile != NULL)
        if (selectedTile == upperTile->upperTile->currentLocation)
            isTileValid = true;
    if (lowerTile != NULL && lowerTile->lowerTile != NULL)
        if (selectedTile == lowerTile->lowerTile->currentLocation)
            isTileValid = true;

    return isTileValid;
}

bool Tile::isTileValid(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;
    if (isAdyacentTileValid(selectedTile))
    {
        isTileValid = true;
        tileInfo->adyacent = true;
    }
    else if (isThereASecretDoor(selectedTile))
    {
        isTileValid = true;
        tileInfo->adyacent = true;
    }


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

bool Tile::isThereASecretDoor(location_t selectedTile)
{
    bool secretDoor = false;

    unsigned selectedFloor = getFloor(selectedTile);
    unsigned currentFloor = getFloor(currentLocation);


    if (selectedFloor == currentFloor)
    {
        if (checkDurlock(selectedTile))
        {

            if (leftTile != secretLeftTile)
                if (secretLeftTile->isVisible && secretLeftTile->tileType == SECRETDOOR)
                    bool secretDoor = true;
            if (rightTile != secretRightTile)
                if (secretRightTile->isVisible && secretRightTile->tileType == SECRETDOOR)
                    bool secretDoor = true;
            if (upperTile != secretUpperTile)
                if (secretUpperTile->isVisible && secretUpperTile->tileType == SECRETDOOR)
                    bool secretDoor = true;
            if (lowerTile != secretLowerTile)
                if (secretLowerTile->isVisible && secretLowerTile->tileType == SECRETDOOR)
                    bool secretDoor = true;
        }
    }
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
    rightTile = right;
    secretRightTile = right;
    leftTile = left;
    secretLeftTile = left;
    upperTile = upper;
    secretUpperTile = upper;
    lowerTile = lower;
    secretLowerTile = lower;
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

bool Tile::isTileVisible()
{
    return isVisible;
}

void Tile::reveal()
{
    if (isVisible == false)
    {
        isVisible = true;
        unsigned number = ((random() % 6) + 1);   //numero random entre 0 y 5, le sumo 1 para que sea entre 1 o 6
        this->combinationNumber = number;

        if (this->tileType == SAFE)        //si es la safe, el combination number sera 0
            this->combinationNumber = 0;
    }
}

void Tile::setToken(tokenInfo_t tokenType, Tile* usefulTile)
{
    if (tokenType == CROWTOKEN)
        for (std::vector<token_t*>::iterator tokIt = tokens->begin(); tokIt != tokens->end(); tokIt++)     //si ya hay un token tipo crow lo borro y lo reemplazo por el nuevo
            if ((*tokIt)->token == CROWTOKEN)
                tokens.erase(tokIt);


    tokens.push_back(new token_t);
    tokens.back()->token = tokenType;
    tokens.back()->tile = this->currentLocation;

    if (tokenType == DOWNSTAIRSTOKEN)
        tokens.back()->usefulTile = usefulTile;
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

bool Atrium::isTileValid(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;

    if (isAdyacentTileValid(selectedTile) == true)
    {
        isTileValid = true;
        tileInfo->adyacent = true;
    }
    else if (selectedTile == (currentLocation + ROWS * COLS) && upperFloorTile != NULL)
    {
        isTileValid = true;
        tileInfo->adyacent = true;
    }
    else if (selectedTile == (currentLocation - ROWS * COLS) && lowerFloorTile != NULL)
    {
        isTileValid = true;
        tileInfo->adyacent = true;
    }
    else
        isTileValid = false;

    return isTileValid;
}

//bool
//Camera::itsATrap()
//{
//    //en model
//    //if(isOnCamera(tile del guardia) && (isOnCamera(tile del player1)||isOnCamera(tile del player2) ))
//    //camera->itsatrap();
//    if (isOnCamera(tileP1))
//        tileP1->triggerAlarm();
//
//    if (isOnCamera(tileP2))
//        tileP2->triggerAlarm();
//
//    return true;
//}

bool
Camera::isOnCamera(Tile* location)
{
    // return (location == Camera) ? true : false;
}

bool ServiceDuct::isTileValid(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;

    if (isAdyacentTileValid(selectedTile))
    {
        isTileValid = true;
        tileInfo->serviceDuct = true;
    }
    else if (isThereASecretDoor(selectedTile))
    {
        isTileValid = true;
        tileInfo->serviceDuct = true;
    }
    else if (secondServiceDuct->getCurrentLocation() == selectedTile && secondServiceDuct->isTileVisible())
    {
        isTileValid = true;
        tileInfo->serviceDuct = true;
    }

    return isTileValid;

}

void ServiceDuct::setSecondduct(Tile* secondDuct)
{
    secondServiceDuct = secondDuct;
}

bool Stairs::isTileValid(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;

    if (isAdyacentTileValid(selectedTile))
    {
        isTileValid = true;
        tileInfo->adyacent = true;
    }
    else if (selectedTile == (currentLocation + 16))
    {
        isTileValid = true;
        tileInfo->adyacent = true;
    }

    return isTileValid;
}

void Stairs::reveal()
{
    isVisible = true;

    upstairsTile->setToken(DOWNSTAIRSTOKEN, this);

}

std::vector<token_t*>* Tile::getTokens()
{
    return &this->tokens;
}

