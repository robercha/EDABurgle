#ifndef TILE_H
#define TILE_H

typedef enum {
    STEALTH, HACK, CRACKED, ALARM, DOWNSTAIRS, OPEN, CROW, KITTY, TOKEN_COUNT
} token_t;

class Tile {
public:
    Tile();
    Tile(const Tile& orig);
    virtual ~Tile();
    bool virtual hiddenTalent() = 0;
protected:
    Tile* rightTile;
    Tile* leftTile;
    Tile* upperTile;
    Tile* lowerTile;
    Tile* upperFloorTile;
    Tile* lowerFloorTile;
    bool crackedToken;
};

class Atrium : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Camera : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class CRFingerprint : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
    unsigned hackTokensQty;
};

class CRMotion : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
    unsigned hackTokensQty;
};

class CRLaser : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
    unsigned hackTokensQty;
};

class Deadbolt : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Fingerprint : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Foyer : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Keypad : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Laboratory : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Laser : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Lavatory : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
    unsigned stealthTokensQty;
};

class Motion : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Safe : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Detector : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class SecretDoor : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class ServiceDuct : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Stairs : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Thermo : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};

class Walkway : public Tile {
public:
    bool hiddenTalent(/*?*/);
private:
};


#endif /* TILE_H */

