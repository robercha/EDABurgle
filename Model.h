#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <list>
#include "Floor.h"
#include "Tile.h"
#include "Guard.h"
#include "Character.h"
#include "Loot.h"

typedef struct gameData {
} gameData_t;

class Model {
public:
    void analyzeAction(gameData_t*);
    Model();
    Model(const Model& orig);
    virtual ~Model();
private:
    //std::vector<std::vector< std::vector<Tile> >> bank; //tile asi o punteros a tile?
    std::vector<Floor> floors;    
    std::vector<Guard> guards;
    std::vector<Character> characters;

};

#endif /* MODEL_H */

