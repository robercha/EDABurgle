#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <list>
#include "Floor.h"
#include "Tile.h"
#include "Guard.h"
#include "Character.h"
#include "Loot.h"
#include "GameStep.h"

class Model {
public:
    void analyzeAction(gameData_t* gameData);
    Model();
    virtual ~Model();
private:
    
    void createTiles(std::vector<Tile*>);
    void shuffleTiles(std::vector<Tile*>);
    void createFloors(std::vector<Tile*>);
    void createGuards();
    void createCharacters();
    void createModelFSM();
    void createLoots();
    
    void eventGenerator(event_t event, gameData_t* gameData);
    
    //std::list<Tile*> floorDeck;
    //std::vector<Tile*> deck; 
    std::vector<Floor*> floors;
    std::vector<Guard*> guards;
    std::vector<Character*> characters;
    std::vector<Loot*> loots;

    GameStep*** gameHandlerMatrix;
    GameStep* currentAction;



};

#endif /* MODEL_H */

