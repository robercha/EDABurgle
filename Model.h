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

typedef struct gameData {
    modelEvent_t event;
} gameData_t;

class Model {
public:
    void analyzeAction(gameData_t* gameData);
    Model();
    virtual ~Model();
private:
    void eventGenerator(event_t event, gameData_t* gameData);
    
    std::list<Tile*> floorDeck;
    std::vector<Tile*> deck;
    std::vector<Floor*> floors;
    std::vector<Guard*> guards;
    std::vector<Character*> characters;

    GameStep*** gameHandlerMatrix;
    GameStep* currentAction;
};

#endif /* MODEL_H */

