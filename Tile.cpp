#include <stdbool.h>
#include <fenv.h>

#include "Tile.h"
#include "View.h"

#define ROWS    4
#define COLS    4
#define FLOORS   3

Tile::Tile()
{
    upperFloorTile = NULL;
    lowerFloorTile = NULL;
    alarmTile = false;
    mustSpendActions = false;
    feeToEnter = 0;
    alarmToken = false;
    isVisible = false;
    combinationNumber = 0;
    crackedToken = false;
    crowToken = false;
    kittyToken = false;
    openToken = false;
    goldBarToken = false;
}

Atrium::Atrium()
{
    tileType = ATRIUM;

}

Camera::Camera()
{
    tileType = CAMERA;
    alarmTile = true;
}

CRFingerprint::CRFingerprint()
{
    tileType = CR_FINGERPRINT;
    hackTokensQty = 0;
}

CRLaser::CRLaser()
{
    tileType = CR_LASER;
    hackTokensQty = 0;
}

CRMotion::CRMotion()
{
    tileType = CR_MOTION;
    hackTokensQty = 0;
}

Deadbolt::Deadbolt()
{
    tileType = DEADBOLT;
    mustSpendActions = true;
    feeToEnter = 3;
}

Detector::Detector()
{
    tileType = DETECTOR;
    alarmTile = true;
}

Fingerprint::Fingerprint()
{
    tileType = FINGERPRINT;
    alarmTile = true;
}

Foyer::Foyer()
{
    tileType = FOYER;
    alarmTile = true;
}

Keypad::Keypad()
{
    tileType = KEYPAD;
    mustSpendActions = true; //le preguntamos al user si quiere tirar los dados para abrir el keypad
}

Laboratory::Laboratory()
{
    tileType = LABORATORY;
}

Laser::Laser()
{
    tileType = LASER;
    alarmTile = true;
    mustSpendActions = true;
    feeToEnter = 2;
}

Lavatory::Lavatory()
{
    tileType = LAVATORY;
    stealthTokensQty = 0;
    firstReveal = false;
}

Motion::Motion()
{
    tileType = MOTION;
    alarmTile = true;
}

Safe::Safe()
{
    tileType = SAFE;
    numberOfDice = 0;
    crackedSafe = false;
}

SecretDoor::SecretDoor()
{
    tileType = SECRETDOOR;
}

ServiceDuct::ServiceDuct()
{
    tileType = SERVICEDUCT;
}

Stairs::Stairs()
{
    tileType = STAIRS;
}

Thermo::Thermo()
{
    tileType = THERMO;
    alarmTile = true;
}

Walkway::Walkway()
{
    tileType = WALKWAY;
}

void Tile::setJuicerAlarm()
{
    this->alarmTile = true;
}

Tile* Tile::getRightTile()
{
    return this->rightTile;
}

bool Tile::isGoldBar()
{
    return this->goldBarToken;
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

    if (secretRightTile != NULL && selectedTile == secretRightTile->currentLocation)
        wall = true;
    else if (secretLeftTile != NULL && selectedTile == secretLeftTile->currentLocation)
        wall = true;
    else if (secretUpperTile != NULL && selectedTile == secretUpperTile->currentLocation)
        wall = true;
    else if (secretLowerTile != NULL && selectedTile == secretLowerTile->currentLocation);
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
    if (isAdyacentTileValid(selectedTile, tileInfo))
    {
        isTileValid = true;
        tileInfo->adyacent = true;
    }
    else if (isThereASecretDoor(selectedTile, tileInfo))
    {
        isTileValid = true;
        tileInfo->adyacent = true;
    }
    else
        tileInfo->adyacent = false;

    return isTileValid;

}

bool Tile::isAdyacentTileValid(location_t selectedTile, tileInfo_t* tileInfo)
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
        if (((selectedCol == (currCol + 1) || selectedCol == (currCol - 1))&&(selectedRow == currRow))
                || ((selectedRow == (currRow + 1) || selectedRow == (currRow - 1))&&(selectedCol == currCol)))
        {
            if (selectedCol == (currCol + 1) && rightTile != NULL)
            {
                tileInfo->tile = this->rightTile;
                isTileValid = true;
            }
            else if (selectedCol == (currCol - 1) && leftTile != NULL)
            {
                tileInfo->tile = this->leftTile;
                isTileValid = true;
            }
            else if (selectedRow == (currRow + 1) && lowerTile != NULL)
            {
                tileInfo->tile = this->lowerTile;
                isTileValid = true;
            }
            else if (selectedRow == (currRow - 1) && upperTile != NULL)
            {
                tileInfo->tile = this->upperTile;
                isTileValid = true;
            }
            else
                isTileValid = false;
        }

    }
    
    if (selectedFloor == currFloor+1)
    {
        if(this->alarmTile == STAIRS && this->upperFloorTile != NULL)
        {
            tileInfo->tile = this->upperFloorTile;
            isTileValid = true;
        }   
    }
    
    if (selectedFloor == currFloor-1)
    {
        if(this->alarmTile == STAIRS && this->lowerFloorTile != NULL)
        {
            tileInfo->tile = this->lowerFloorTile;
            isTileValid = true;
        }   
    }

    return isTileValid;
}

bool Tile::isThereASecretDoor(location_t selectedTile, tileInfo_t* tileInfo)
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
                {
                    bool secretDoor = true;
                    tileInfo->tile = secretLeftTile;
                }
            if (rightTile != secretRightTile)
                if (secretRightTile->isVisible && secretRightTile->tileType == SECRETDOOR)
                {
                    bool secretDoor = true;
                    tileInfo->tile = secretRightTile;
                }
            if (upperTile != secretUpperTile)
                if (secretUpperTile->isVisible && secretUpperTile->tileType == SECRETDOOR)
                {
                    bool secretDoor = true;
                    tileInfo->tile = secretUpperTile;
                }
            if (lowerTile != secretLowerTile)
                if (secretLowerTile->isVisible && secretLowerTile->tileType == SECRETDOOR)
                {
                    bool secretDoor = true;
                    tileInfo->tile = secretLowerTile;
                }
        }
    }
    return secretDoor;
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
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    if (isVisible == false)
    {
        isVisible = true;
        unsigned number = ((rand_r(&seed) % 6) + 1);   //numero random entre 0 y 5, le sumo 1 para que sea entre 1 o 6
        this->combinationNumber = number;

        if (this->tileType == SAFE)        //si es la safe, el combination number sera 0
            this->combinationNumber = 0;
    }
}

void Tile::setUpperLoorTile(Tile* tile)
{
    upperFloorTile = tile;
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

    if (isAdyacentTileValid(selectedTile, tileInfo) == true)
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

void CRFingerprint::hack()
{
    hackTokensQty++;
}

void CRFingerprint::useHackToken()
{
    hackTokensQty--;
}

void CRMotion::hack()
{
    hackTokensQty++;
}

void CRMotion::useHackToken()
{
    hackTokensQty--;
}

void CRLaser::hack()
{
    hackTokensQty++;
}

void CRLaser::useHackToken()
{
    hackTokensQty--;
}

bool
Camera::isOnCamera(Tile* location)
{
    // return (location == Camera) ? true : false;
}

void Safe::addDice()
{
    numberOfDice++;
}

bool Safe::isCracked()
{
    return crackedSafe;
}

void Safe::setCracked()
{
    crackedSafe = true;

}

void Safe::disableCracked()
{
    crackedSafe = false;

}

bool ServiceDuct::isTileValid(location_t selectedTile, tileInfo_t* tileInfo)
{
    bool isTileValid = false;

    if (isAdyacentTileValid(selectedTile, tileInfo))
    {
        isTileValid = true;
        tileInfo->serviceDuct = true;
    }
    else if (isThereASecretDoor(selectedTile, tileInfo))
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

    if (isAdyacentTileValid(selectedTile, tileInfo))
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
    upstairsTile->setDownstairsToken(true);
}
