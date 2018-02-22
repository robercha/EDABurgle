#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <list>
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
    void fillGraphicsData(View* view, gameData_t* gameData);
    void eventGenerator(gameData_t* gameData);

    //std::list<Tile*> floorDeck;
    //std::vector<Tile*> deck;
    std::vector<Floor*> floors;
    //std::vector<Guard*> guards;       //esto lo tiene floor
    std::vector<Character*> characters;
    std::vector<Loot*> loots;
    Character* currentCharacter;

    bool gameWon;
    bool gameLost;

    GameStep*** gameHandlerMatrix;
    GameStep* currentAction;




};

#endif /* MODEL_H */

