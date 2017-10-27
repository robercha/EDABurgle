
#ifndef TILE_H
#define TILE_H

typedef enum {
    STEALTH, HACK, CRACKED, ALARM, DOWNSTAIRS, OPEN, CROW, KITTY, TOKEN_COUNT
} token_t;

typedef enum {
    TIARA, PERSIAN_KITTY, PAINTING, MIRROR, KEYCARD, ISOTOPE, GEMSTONE, CURSED_GOBLET, CHIHUAHUA, GOLD_BAR, LOOT_COUNT
} loot_t;

class Tile {
public:
    Tile();
    Tile(const Tile& orig);
    virtual ~Tile();
    bool virtual hiddenTalent(/*?*/) = 0;
protected:
    Tile* rightTile;
    Tile* leftTile;
    Tile* upperTile;
    Tile* lowerTile;
};

class Atrium : public Tile {
public:
private:
};

class Camera : public Tile {
public:
private:
};

class ComputerRoom : public Tile {
public:
private:
};

class Deadbolt : public Tile {
public:
private:
};

class Fingerprint : public Tile {
public:
private:
};

class Foyer : public Tile {
public:
private:
};

class Keypad : public Tile {
public:
private:
};

class Laboratory : public Tile {
public:
private:
};

class Laser : public Tile {
public:
private:
};

class Lavatory : public Tile {
public:
private:
};

class Motion : public Tile {
public:
private:
};

class Safe : public Tile {
public:
private:
};

class Detector : public Tile {
public:
private:
};

class SecretDoor : public Tile {
public:
private:
};

class ServiceDuct : public Tile {
public:
private:
};

class Stair : public Tile {
public:
private:
};

class Thermo : public Tile {
public:
private:
};

class Walkaway : public Tile {
public:
private:
};


#endif /* TILE_H */

