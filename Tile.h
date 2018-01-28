#ifndef TILE_H
#define TILE_H

typedef enum {
    A1F1, B1F1, C1F1, D1F1, A2F1, B2F1, C2F1, D2F1, A3F1, B3F1, C3F1, D3F1, A4F1, B4F1, C4F1, D4F1,
    A1F2, B1F2, C1F2, D1F2, A2F2, B2F2, C2F2, D2F2, A3F2, B3F2, C3F2, D3F2, A4F2, B4F2, C4F2, D4F2,
    A1F3, B1F3, C1F3, D1F3, A2F3, B2F3, C2F3, D2F3, A3F3, B3F3, C3F3, D3F3, A4F3, B4F3, C4F3, D4F3,
    NO_LOCATION
} location_t;

typedef enum {
    RIGHT, LEFT, UP, DOWN, UPPER, LOWER
} coordinates_t;

class Tile {
public:

    Tile(); //si la tile es de tipo alarma, declaramos explicitamente el constructor y seteamos isAlarmTile a true
    Tile(const Tile& orig);
    virtual ~Tile();
    bool peek(coordinates_t);
    virtual bool itsATrap() = 0;
    bool triggerAlarm();
    void useHackToken();
    bool isAlarmTile(); //getter de isAlarmTile
protected:
    location_t currentLocation;
    Tile* rightTile;
    Tile* leftTile;
    Tile* upperTile;
    Tile* lowerTile;
    Tile* upperFloorTile;
    Tile* lowerFloorTile;
    bool isVisible;
    bool crackedToken;
    bool alarmTile;
};

//enum class action_t {
//     ADD_DICE_TO_SAFE, ROLL_DICE_FOR_SAFE, SPEND_ACTIONS_TO_ENTER, HACK_COMPUTER, ,
//    OFFER_LOOT, REQUEST_LOOT, PICK_UP_LOOT, CREATE_ALARM, SPY_PATROL_DECK, PATROL_IS_TOP, PATROL_IS_BOTTOM,
//    PLACE_CROW_TOKEN, ACCEPT, DECLINE, PLAY_AGAIN_YES, PLAY_AGAIN_NO, ACTION_COUNT
//};

class Atrium : public Tile {
public:
    bool itsATrap();
    void setTile(Tile*); //la tile a peekaer
    bool isGuardAbove(Tile* guardLocation); //devuelve true si hay q sacarle un stealth
    bool isGuardBelow(Tile* guardLocation); //devuelve true si hay q sacarle un stealth
private:
    Tile* peekaboo; //la tile a peekaer
};

class Camera : public Tile {
public:
    bool itsATrap();
    bool isOnCamera(Tile* Location);
private:
    Tile* tileP1;
    Tile* tileP2;
};

class CRFingerprint : public Tile {
public:
    bool itsATrap();
    void hack(); //adds hack token to tile
private:
    unsigned hackTokensQty;
};

class CRMotion : public Tile {
public:
    bool itsATrap();
    void hack(); //adds hack token to tile
private:
    unsigned hackTokensQty;
};

class CRLaser : public Tile {
public:
    bool itsATrap();
    void hack(); //adds hack token to tile
private:
    unsigned hackTokensQty;
};

class Deadbolt : public Tile {
public:
    bool itsATrap();
private:
};

class Fingerprint : public Tile {
public:
    bool itsATrap();
private:
};

class Foyer : public Tile {
public:
    bool itsATrap();
private:
};

class Keypad : public Tile {
public:
    bool itsATrap();
private:
};

class Laboratory : public Tile {
public:
    bool itsATrap();
private:
};

class Laser : public Tile {
public:
    bool itsATrap();
private:
};

class Lavatory : public Tile {
public:
    bool itsATrap();
private:
    unsigned stealthTokensQty;
};

class Motion : public Tile {
public:
    bool itsATrap();
private:
};

class Safe : public Tile {
public:
    bool itsATrap();
    void rollDice();
    void addDiceToSafe();
private:
};

class Detector : public Tile {
public:
    bool itsATrap();
private:
};

class SecretDoor : public Tile {
public:
    bool itsATrap();
private:
};

class ServiceDuct : public Tile {
public:
    bool itsATrap();
private:
};

class Stairs : public Tile {
public:
    bool itsATrap();
private:
};

class Thermo : public Tile {
public:
    bool itsATrap();
private:
};

class Walkway : public Tile {
public:
    bool itsATrap();
private:
};


#endif /* TILE_H */

