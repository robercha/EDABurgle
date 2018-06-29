#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <list>
#include "Tile.h"
#include "Guard.h"
#include "Loot.h"

#define ROWS 4
#define COLS 4

class Floor {
public:
    Floor(std::vector<Tile*> &tileDeck, unsigned floorNumber);
    ~Floor();
    void randomizeFloor();
    void setTile(Tile* tile);
    void crack(unsigned, location_t); //se fija si las tiles son crackeadas
    unsigned getGuardSpeed();
    void updatePatrolCard();
    location_t getGuardLocation();

    location_t getGuardDestination() {
        return guard->getDestination();
    }

    location_t getGuardPatrolCard() {
        return guard->getPatrolCard();
    }

    loot_t getLootName() {
        return this->loot->getLootName();
    }

    void setLoot(Loot* loot) {
        this->loot = loot;
    }

    Loot* getLoot() {
        return this->loot;
    }

    bool getLootVisibility() {
        return loot->isLootVisible();
    }
    void moveGuard();

    void toggleGuard() {
        guard->toggleGuard();
    }

    player_t getLootOwner() {
        return this->loot->getOwner();
    }

    bool isGuardActive() {
        return guard->getGuardState();
    }

    bool isSafeCracked(location_t location) {
        return dynamic_cast<Safe*> (this->tiles[getRow(location)][getColumn(location)])->isCracked();
    }

    void addDiceToSafe(location_t location) {
        dynamic_cast<Safe*> (this->tiles[getRow(location)][getColumn(location)])->addDice();
    }

    void setAlarmToken(location_t location, bool state) {
        this->tiles[getRow(location)][getColumn(location)]->setAlarmToken(state);
    }

    bool isAlarmTile(location_t location) {
        this->tiles[getRow(location)][getColumn(location)]->isAlarmTile(location);
    }

    location_t getGuardDieLocation(); //donde esta el dado (a donde va si no suenan alarmas)
    std::vector< std::vector<Tile*> >& getDeck();

private:
    unsigned floorNumber;
    void createPatrolDeck();
    bool takePatrolCard();
    void setAdjacentTiles(unsigned row, unsigned col);
    void createWalls(unsigned);
    Tile* setDistance2Guard();
    Tile* nextStep(Tile* destination);
    Tile* minDistance();
    void unvisitTiles();
    Guard* guard;
    std::vector<location_t> patrolDeck;
    std::vector<location_t> trashedPatrolDeck;
    std::vector< std::vector<Tile*> > tiles;
    unsigned diceResult[6];
    Loot* loot;
} ;

#endif /* FLOOR_H */

