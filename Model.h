#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <list>
#include "Floor.h"
#include "Tile.h"
#include "Guard.h"
#include "Character.h"
#include "Loot.h"
#include "Floor.h"
#include "GameStep.h"
<<<<<<< HEAD
=======
=======
>>>>>>> 959d79a83e4deee651dcd2a5814b14217e623f1c
>>>>>>> 258a82c6cb528d6814d78759d8e1914f56e2525e

typedef struct gameData {
} gameData_t;

class Model {
public:
    void analyzeAction(gameData_t*);
    Model();
    virtual ~Model();
private:
    void eventGenerator(event_t event);
    
    std::list<Tile*> floorDeck;
    std::vector<Tile*> deck;
    std::vector<Floor*> floors;
    std::vector<Guard*> guards;
    std::vector<Character*> characters;

    Actions*** gameHandlerMatrix;
    Actions* currentAction;
};

#endif /* MODEL_H */

