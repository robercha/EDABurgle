#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <list>
#include "GameStep.h"
#include "View.h"

#define PLAYER1 0
#define PLAYER2 1

class Model {
public:
    bool analyzeAction(gameData_t* gameData);
    Model(gameData_t* gameData);
    virtual ~Model();
    void initGameData(gameData_t* gameData);
    void initGraphicsData(View* view, gameData_t*);
    void fillGraphicsData(View* view, gameData_t*);
private:
    bool isGameWon();
    bool isGameLost();
    void createTiles(std::vector<Tile*>&);
    void shuffleTiles(std::vector<Tile*>&);
    void createFloors(std::vector<Tile*>);
    void setStairs();
    void createGuards();
    void createModelFSM();
    void createLoots();
    void createCharacters();

    void eventGenerator(gameData_t* gameData);

    gamePointers_t* gamePointers;

    bool gameWon;
    bool gameLost;

    GameStep*** gameHandlerMatrix;
    GameStep* currentAction;




} ;

#endif /* MODEL_H */

