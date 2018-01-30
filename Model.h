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
#include "View.h"

class Model {
public:
    void analyzeAction(gameData_t* gameData);
    Model();
    virtual ~Model();
    void fillGraphicsData(View *view);
private:
    bool isGameWon();
    bool isGameLost();
    void createTiles(std::vector<Tile*>);
    void shuffleTiles(std::vector<Tile*>);
    void createFloors(std::vector<Tile*>);
    void createGuards();
    void createCharacters();
    void createModelFSM();
    void createLoots();
    void fillGraphicsData();
    void eventGenerator(button_t event, gameData_t* gameData);

    //std::list<Tile*> floorDeck;
    //std::vector<Tile*> deck;
    std::vector<Floor*> floors;
    //std::vector<Guard*> guards;       //esto lo tiene floor
    std::vector<Character*> characters;
    std::vector<Loot*> loots;
    Character* currentCharacter;

    GameStep*** gameHandlerMatrix;
    GameStep* currentAction;




};

#endif /* MODEL_H */

