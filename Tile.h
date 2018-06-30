#ifndef TILE_H
#define TILE_H

#include <stdio.h>
#include <vector>
#include <stdbool.h>
#include<chrono>

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

#define  HACKTOKENSMAX 6

typedef struct tokens token_t;

typedef enum {
    A1F1, B1F1, C1F1, D1F1, A2F1, B2F1, C2F1, D2F1, A3F1, B3F1, C3F1, D3F1, A4F1, B4F1, C4F1, D4F1,
    A1F2, B1F2, C1F2, D1F2, A2F2, B2F2, C2F2, D2F2, A3F2, B3F2, C3F2, D3F2, A4F2, B4F2, C4F2, D4F2,
    A1F3, B1F3, C1F3, D1F3, A2F3, B2F3, C2F3, D2F3, A3F3, B3F3, C3F3, D3F3, A4F3, B4F3, C4F3, D4F3,
    NO_LOCATION
} location_t;

unsigned getColumn(location_t location);
unsigned getRow(location_t location);
unsigned getFloor(location_t location);

typedef enum {
    ALARMTOKEN, OPENTOKEN, KITTYTOKEN, STEALTHTOKEN, CRACKEDTOKEN, DOWNSTAIRSTOKEN, CROWTOKEN, HACKTOKEN,
    TOKEN_COUNT
} tokenInfo_t;

typedef enum {
    RIGHT, LEFT, UP, DOWN, UPPER, LOWER
} coordinates_t;

typedef enum {
    ATRIUM, CAMERA, CR_FINGERPRINT, CR_LASER, CR_MOTION, DEADBOLT, DETECTOR, FINGERPRINT, FOYER, KEYPAD,
    LABORATORY, LASER, LAVATORY, MOTION, SAFE, SECRETDOOR, SERVICEDUCT, STAIRS, THERMO, WALKWAY, ROOMBACK
} tileType_t;

typedef struct tileInfo tileInfo_t;

class Tile {
public:
    Tile();
    virtual ~Tile();
    bool peek(coordinates_t);
    bool isTileVisible();
    virtual void reveal();
    bool isPaidMove(); //si hay que gastar acciones para entrar isPaidMove() devuelve true

    unsigned getFeeToEnter() {
        return feeToEnter;
    }
    virtual bool isTileValid(location_t, tileInfo_t*); //se fija si es adyacente
    void setCurrentLocation(location_t);
    void setRightWall();
    void setLeftWall();
    void setUpperWall();
    void setLowerWall();
    void setAdjacentTiles(Tile* left, Tile* right, Tile* up, Tile* down);
    location_t getCurrentLocation();
    bool checkDurlock(location_t selectedTile); //devuelve true cuando hay una pared entre currentTile y selectedTile
    bool isTileTwoTilesAway(location_t location);
    void setJuicerAlarm(); //alarma que puede poner el juicer en tiles
    bool isGoldBar();

    Tile* getRightTile();
    Tile* getLeftTile();
    Tile* getUpperTile();
    Tile* getLowerTile();

    bool setAlarmToken(bool state) {
        alarmToken = state;
    }

    bool isAlarmOn() {
        return this->alarmToken;
    }

    void setKittyToken(bool state) {
        crowToken = state;
    }

    bool getKittyToken() {
        return crowToken;
    }

    void setOpenToken(bool state) {
        openToken = state;
    }

    bool getOpenToken() {
        return openToken;
    }

    void setCrowToken(bool state) {
        crowToken = state;
    }

    bool getCrowToken() {
        return crowToken;
    }

    void setCrackToken() {
        crackedToken = true;
    }

    bool getCrackedToken() {
        return crackedToken;
    }

    void setDownstairsToken(bool state) {
        downstairsToken = state;
    }

    bool getDownstairsToken() {
        return downstairsToken;
    }

    bool isAlarmTile() {
        return alarmTile;
    }

    void visit() {
        visited = true;
    }

    void unvisit() {
        visited = false;
    }

    bool wasItVisited() {
        return visited;
    }

    unsigned getDistance2Guard() {
        return distance2guard;
    }

    void setDistance2Guard(unsigned distance) {
        distance2guard = distance;
    }

    tileType_t getTileType() {
        return tileType;
    }

    unsigned getCombinationNumber() {
        return combinationNumber;
    }
protected:
    location_t currentLocation;
    tileType_t tileType;

    Tile* rightTile;
    Tile* leftTile;
    Tile* upperTile;
    Tile* lowerTile;

    Tile* upperFloorTile;
    Tile* lowerFloorTile;

    Tile* secretRightTile;
    Tile* secretLeftTile;
    Tile* secretUpperTile;
    Tile* secretLowerTile;

    bool visited;       //deberia poder desvisitarla
    unsigned distance2guard;

    bool isVisible;
    bool crackedToken;
    bool crowToken;
    bool downstairsToken;
    bool kittyToken;
    bool openToken;
    bool goldBarToken;
    bool alarmTile;
    bool alarmToken;
    bool mustSpendActions;
    unsigned feeToEnter;
    unsigned combinationNumber;
    bool isAdyacentTileValid(location_t selectedLocation, tileInfo_t*);
    bool isThereASecretDoor(location_t selectedLocation, tileInfo_t*);
} ;

struct tileInfo {
    Tile* tile;
    bool ownTile;
    bool hawkWall;
    bool differentFloor;
    bool adyacent;
    bool twoTilesAwayTile;
    bool serviceDuct;
    //bool secretDoor;
} ;

typedef struct tokens {
    location_t tile;
    tokenInfo_t token;
    Tile* usefulTile;
} token_t;

class Atrium : public Tile {
public:
    Atrium();
    bool isTileValid(location_t, tileInfo_t*);
    void setTile(Tile*); //la tile a peekaer
    bool isGuardAbove(Tile* guardLocation); //devuelve true si hay q sacarle un stealth
    bool isGuardBelow(Tile* guardLocation); //devuelve true si hay q sacarle un stealth
private:
    Tile* peekaboo; //la tile a peekaer
    Tile* upperFloorTile;
    Tile* lowerFloorTile;
} ;

class Camera : public Tile {
public:
    Camera();
    bool isOnCamera(Tile* Location);
private:
    Tile* tileP1;
    Tile* tileP2;
} ;

class CRFingerprint : public Tile {
public:
    CRFingerprint();

    unsigned getHackTokensQty() {
        return hackTokensQty;
    };
    bool areHackTokensZero();
    bool areHackTokensMax();
    void useHackToken();
    void hack(); //adds hack token to tile
private:
    unsigned hackTokensQty;
} ;

class CRMotion : public Tile {
public:
    CRMotion();

    unsigned getHackTokensQty() {
        return hackTokensQty;
    };
    bool areHackTokensZero();
    bool areHackTokensMax();
    void useHackToken();
    void hack(); //adds hack token to tile
private:
    unsigned hackTokensQty;
} ;

class CRLaser : public Tile {
public:
    CRLaser();

    unsigned getHackTokensQty() {
        return hackTokensQty;
    };
    bool areHackTokensZero();
    bool areHackTokensMax();
    void useHackToken();
    void hack(); //adds hack token to tile
private:
    unsigned hackTokensQty;
} ;

class Deadbolt : public Tile {
public:
    Deadbolt();
private:
} ;

class Fingerprint : public Tile {
public:
    Fingerprint();
private:
} ;

class Foyer : public Tile {
public:
    Foyer();
private:
} ;

class Keypad : public Tile {
public:
    Keypad();
private:

    bool openToken;
} ;

class Laboratory : public Tile {
public:
    Laboratory();
private:
} ;

class Laser : public Tile {
public:
    Laser();
private:
} ;

class Lavatory : public Tile {
public:
    Lavatory();

    unsigned getStealthTokensQty() {
        return stealthTokensQty;
    };

    //    void setFirstReveal() {
    //        firstReveal = true;
    //    }
    //
    //    void setStealthTokens() {
    //        stealthTokensQty = 3;
    //    };
    void reveal();

private:
    unsigned stealthTokensQty;
    bool firstReveal;
} ;

class Motion : public Tile {
public:
    Motion();
private:
} ;

class Safe : public Tile {
public:
    Safe();
    void rollDice();
    void addDice();
    bool isCracked();
    void setCracked();
    void disableCracked();
    void reveal();

    unsigned getDieQty() {
        return numberOfDice;
    }
private:
    unsigned numberOfDice;
    bool crackedSafe;
} ;

class Detector : public Tile {
public:
    Detector();
private:
} ;

class SecretDoor : public Tile {
public:
    SecretDoor();
private:
} ;

class ServiceDuct : public Tile {
public:
    ServiceDuct();
    bool isTileValid(location_t, tileInfo_t*);
    void setSecondduct(Tile* secondDuct);
private:
    Tile* secondServiceDuct;
} ;

class Stairs : public Tile {
public:
    Stairs();
    bool isTileValid(location_t, tileInfo_t*);
    void reveal();

    void setUpstairsTile(Tile* tile) {
        this->upstairsTile = tile;
    }

    Tile* getUpstairsTile() {
        return this->upstairsTile;
    }

    void setDownstairsTile(Tile* tile) {
        this->downstairsTile = tile;
    }

    Tile* getDownstairsTile() {
        return this->downstairsTile;
    }

private:
    Tile* upstairsTile;
    Tile* downstairsTile;
} ;

class Thermo : public Tile {
public:
    Thermo();
private:
} ;

class Walkway : public Tile {
public:
    Walkway();
    bool itsATrap();
private:
} ;


#endif /* TILE_H */

