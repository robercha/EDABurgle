#ifndef LOOT_H
#define LOOT_H

#include "Character.h"

typedef enum {
    TIARA, PERSIAN_KITTY, PAINTING, MIRROR, KEYCARD, ISOTOPE, GEMSTONE, CURSED_GOBLET, CHIHUAHUA, GOLD_BAR, LOOT_COUNT
} loot_t;

class Loot {
public:
    Loot();
    Loot(const Loot& orig);
    virtual ~Loot();
protected:
};

class Goblet : public Loot {
public:
private:
    void poisonCharacter(Character*);
};


#endif /* LOOT_H */

