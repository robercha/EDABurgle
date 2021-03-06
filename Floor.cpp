#define ROWS 4
#define COLS 4

#include "Floor.h"
#include <chrono>
#include <random>
#include <algorithm>

#define ROWS    4
#define COLS    4
#define ALL_CRACK 6
#define INF 999999999



unsigned floor1(std::vector< std::vector<Tile*> > &floor);
unsigned floor2(std::vector< std::vector<Tile*> > &floor);
unsigned floor3(std::vector< std::vector<Tile*> > &floor);
bool compare(Tile* i, Tile* j);

Floor::Floor(std::vector<Tile*> &deck, unsigned floorNumber)
{
    this->floorNumber = floorNumber;
    unsigned location = 16 * floorNumber;

    std::vector <Tile*> tempRow;

    for (unsigned i = 0; i < 4 ; i++)
    {
        for (unsigned j = 0; j < 4; j++)
        {
            if (i == 3 && j >= 2) //para dejar espacio para la safe y la stair
                break;
            tempRow.push_back(deck.back());
            deck.pop_back();
        }

        tiles.push_back(tempRow);
        tempRow.clear();
    }


    tiles[3].push_back(new Stairs);

    tiles[3].push_back(new Safe);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(tiles.begin(), tiles.end(), std::default_random_engine(seed));

    for (unsigned row = 0; row < ROWS; row++)
    {

        for (unsigned col = 0; col < COLS; col++)
        {
            tiles[row][col]->setCurrentLocation((location_t) location);
            setAdjacentTiles(row, col);
            location++;
        }

    }

    createWalls(floorNumber);
    createPatrolDeck();

    location_t startTile = patrolDeck.back();

    this->trashedPatrolDeck.push_back(startTile);
    patrolDeck.pop_back();

    location_t patrolCard = patrolDeck.back();
    this->trashedPatrolDeck.push_back(patrolCard);
    patrolDeck.pop_back();

    guard = new Guard(floorNumber + 2, tiles[(unsigned) startTile / COLS][(unsigned) startTile % COLS], patrolCard);

    if (floorNumber == 0)
        guard->toggleGuard();


}

Floor::~Floor()
{
}

void Floor::createPatrolDeck()
{
    trashedPatrolDeck.clear();

    for (unsigned i = 0; i < (ROWS * COLS); i++)
        patrolDeck.push_back((location_t) i);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(patrolDeck.begin(), patrolDeck.end(), std::default_random_engine(seed));

    for (unsigned i = 0; i < DISCARDED_PATROL_COUNT; i++)
        patrolDeck.pop_back();

}

void Floor::updatePatrolCard()
{
    if (!patrolDeck.empty())
    {
        location_t patrolCard = patrolDeck.back();
        this->trashedPatrolDeck.push_back(patrolCard);
        patrolDeck.pop_back();
        guard->setDestination(patrolCard);
        guard->setPatrolCard(patrolCard);
    }
    else
    {
        createPatrolDeck();
        updatePatrolCard();
    }

}

void Floor::createWalls(unsigned floorNumber)
{
    switch (floorNumber)
    {
        case 0: floor1(tiles);
            break;
        case 1: floor2(tiles);
            break;
        case 2: floor3(tiles);
            break;
    }
}

void Floor::setAdjacentTiles(unsigned row, unsigned col)
{
    if (row == 0)
    {
        if (col == 0)
            tiles[row][col]->setAdjacentTiles(NULL, tiles[row][col + 1], NULL, tiles[row + 1][col]);
        else if (col == 3)
            tiles[row][col]->setAdjacentTiles(tiles[row][col - 1], NULL, NULL, tiles[row + 1][col]);
        else
            tiles[row][col]->setAdjacentTiles(tiles[row][col - 1], tiles[row][col + 1], NULL, tiles[row + 1][col]);
    }

    else if (row == 3)
    {
        if (col == 0)
            tiles[row][col]->setAdjacentTiles(NULL, tiles[row][col + 1], tiles[row - 1][col], NULL);
        else if (col == 3)
            tiles[row][col]->setAdjacentTiles(tiles[row][col - 1], NULL, tiles[row - 1][col], NULL);
        else
            tiles[row][col]->setAdjacentTiles(tiles[row][col - 1], tiles[row][col + 1], tiles[row - 1][col], NULL);
    }

    else
    {
        if (col == 0)
            tiles[row][col]->setAdjacentTiles(NULL, tiles[row][col + 1], tiles[row - 1][col], tiles[row + 1][col]);
        else if (col == 3)
            tiles[row][col]->setAdjacentTiles(tiles[row][col - 1], NULL, tiles[row - 1][col], tiles[row + 1][col]);
        else
            tiles[row][col]->setAdjacentTiles(tiles[row][col - 1], tiles[row][col + 1], tiles[row - 1][col], tiles[row + 1][col]);
    }

}

unsigned floor1(std::vector< std::vector<Tile*> > &floor)
{
    floor[0][0]->setRightWall();
    floor[0][1]->setLeftWall();
    floor[0][2]->setLowerWall();
    floor[1][0]->setLowerWall();
    floor[1][1]->setLowerWall();
    floor[1][2]->setUpperWall();
    floor[1][2]->setRightWall();
    floor[1][3]->setLeftWall();
    floor[2][0]->setUpperWall();
    floor[2][1]->setUpperWall();
    floor[2][3]->setLowerWall();
    floor[3][0]->setRightWall();
    floor[3][1]->setLeftWall();
    floor[3][1]->setRightWall();
    floor[3][2]->setLeftWall();
    floor[3][3]->setUpperWall();
}

unsigned floor2(std::vector< std::vector<Tile*> > &floor)
{
    floor[0][0]->setRightWall();
    floor[0][1]->setLeftWall();
    floor[0][1]->setRightWall();
    floor[0][2]->setLeftWall();
    floor[0][2]->setRightWall();
    floor[0][3]->setLeftWall();
    floor[1][1]->setLowerWall();
    floor[1][2]->setLowerWall();
    floor[2][1]->setUpperWall();
    floor[2][2]->setUpperWall();
    floor[3][0]->setRightWall();
    floor[3][1]->setLeftWall();
    floor[3][1]->setRightWall();
    floor[3][2]->setLeftWall();
    floor[3][2]->setRightWall();
    floor[3][3]->setLeftWall();

}

unsigned floor3(std::vector< std::vector<Tile*> > &floor)
{
    floor[0][2]->setLowerWall();
    floor[1][0]->setLowerWall();
    floor[1][0]->setRightWall();
    floor[1][1]->setLeftWall();
    floor[1][2]->setUpperWall();
    floor[1][2]->setRightWall();
    floor[1][2]->setLowerWall();
    floor[1][3]->setLeftWall();
    floor[2][0]->setUpperWall();
    floor[2][0]->setRightWall();
    floor[2][1]->setLeftWall();
    floor[2][1]->setRightWall();
    floor[2][2]->setUpperWall();
    floor[2][2]->setLeftWall();
    floor[3][2]->setRightWall();
    floor[3][3]->setLeftWall();
}

location_t  Floor::getGuardLocation()
{
    return guard->getLocation();
}

unsigned Floor::getGuardSpeed()
{
    return guard->getSpeed();
}

std::vector< std::vector<Tile*> >& Floor::getDeck()
{
    return this->tiles;
}

Tile* Floor::setDistance2Guard()
{
    Tile* tilex;

    for (unsigned i = 0; i < ROWS; i++)
        for (unsigned j = 0; j < COLS; j++)
            tiles[i][j]->setDistance2Guard(tiles[i][j]->getCurrentLocation() == (unsigned) this->getGuardLocation() ? 0 : INF);
    //
    //    for (int i = 0; i < 16 ; i++)
    //        tilex->setDistance2Guard((i+16*floorNumber) == (unsigned)this->getGuardLocation() ? 0 : INF); //Setea la distancia al guardia de todas las tiles en INF menos la tile actual del guard

    for (int i = 0; i < 16; i++)
    {
        tilex = minDistance(); //devuelve la tile mas cercana a la tile del guard que no haya sido visitada todavia
        tilex->visit(); //la chequea como visitada

        /*Analiza las tiles adyacentes. Si la distancia de la tile adyacente a la del guardia es mayor que
         la de la tile en cuestion + 1, entonces es mas corto ir por el camino que se esta analizando que
         por otro que se haya analizado anteriormente*/
        if (tilex->getLowerTile() != NULL)
            if (tilex->getLowerTile()->getDistance2Guard()>(tilex->getDistance2Guard() + 1))
                tilex->getLowerTile()->setDistance2Guard(tilex->getDistance2Guard() + 1);

        if (tilex->getRightTile() != NULL)
            if (tilex->getRightTile()->getDistance2Guard()>(tilex->getDistance2Guard() + 1))
                tilex->getRightTile()->setDistance2Guard(tilex->getDistance2Guard() + 1);

        if (tilex->getUpperTile() != NULL)
            if (tilex->getUpperTile()->getDistance2Guard()>(tilex->getDistance2Guard() + 1))
                tilex->getUpperTile()->setDistance2Guard(tilex->getDistance2Guard() + 1);

        if (tilex->getLeftTile() != NULL)
            if (tilex->getLeftTile()->getDistance2Guard()>(tilex->getDistance2Guard() + 1))
                tilex->getLeftTile()->setDistance2Guard(tilex->getDistance2Guard() + 1);
    }

}

Tile* Floor::nextStep(Tile* destination)
{
    Tile* tilex;

    tilex = destination; //En este punto, todas las tiles tienen guardada su distancia hasta el guardia

    /*Voy desde la tile destino hasta la del guardia caminando por las tiles adyacentes
     que marcan el camino mas corto*/
    while (tilex->getDistance2Guard() != 1)
    {

        if (tilex->getUpperTile() != NULL &&
                (tilex->getUpperTile()->getDistance2Guard() == tilex->getDistance2Guard() - 1))
            tilex = tilex->getUpperTile();

        else if (tilex->getRightTile() != NULL &&
                (tilex->getRightTile()->getDistance2Guard() == tilex->getDistance2Guard() - 1))
            tilex = tilex->getRightTile();

        else if (tilex->getLowerTile() != NULL &&
                (tilex->getLowerTile()->getDistance2Guard() == tilex->getDistance2Guard() - 1))
            tilex = tilex->getLowerTile();

        else if (tilex->getLeftTile() != NULL &&
                (tilex->getLeftTile()->getDistance2Guard() == tilex->getDistance2Guard() - 1))
            tilex = tilex->getLeftTile();
    }


    unvisitTiles(); //marco las tiles como no visitadas

    return tilex; //devuelve la tile adyacente al guardia a la que tiene que moverse

}

Tile* Floor::minDistance()
{
    unsigned min = INF;
    Tile* tilex;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (!tiles[i][j]->wasItVisited() && (tiles[i][j]->getDistance2Guard() < min))
            {
                min = tiles[i][j]->getDistance2Guard();
                tilex = tiles[i][j];
            }

    return tilex;
}

void Floor::unvisitTiles()
{

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tiles[i][j]->unvisit();

}

void Floor::crack (unsigned diceQty, location_t location)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned Row = getRow (location);
    unsigned Col = getColumn (location);
    unsigned crackDiceNum;
    unsigned crackedTiles = 0;
    for (unsigned i = 0; i < 6; i++)
        this->diceResult[i] = 0;

    //Se tira el dado y a todos los tiles que tienen el combination number igual al numero que salio se le pone un crack token
    for (unsigned n = 0; n < diceQty; n++)
    {
        crackDiceNum = rand_r(&seed) % 6 + 1;
        diceResult[n] = crackDiceNum;
        for (int i = 0; i < ROWS; i++)
        {
            if ((tiles[i][Col]->getCombinationNumber() == crackDiceNum)&&(tiles[i][Col] != tiles[Row][Col]))  //Chequea toda la columna de la safe
                tiles[i][Col]->setCrackToken(); //Si el dado
        }
        for (int j = 0; j < COLS; j++)
        {
            if ((tiles[Row][j]->getCombinationNumber() == crackDiceNum)&&(tiles[Row][j] != tiles[Row][Col])) //Chequea toda la row de la safe
                tiles[Row][j]->setCrackToken();
        }

    }

    //Chequea si se termino de crackear la safe
    for (int i = 0; i < ROWS; i++)
    {
        if ((tiles[i][Col]->getCrackedToken() == true)&&(tiles[i][Col] != tiles[Row][Col]))
            crackedTiles++;
    }
    for (int j = 0; j < COLS; j++)
    {
        if ((tiles[Row][j]->getCrackedToken() == true)&&(tiles[Row][j] != tiles[Row][Col]))
            crackedTiles++;
    }
    if (crackedTiles == ALL_CRACK)   //Verifico si todas sus tiles adyacentes tienen crack token
    {
        dynamic_cast<Safe*> (tiles[Row][Col])->setCracked();    //Se crackeo la safe
        loot->setVisibility(true);
    }

}

void Floor::moveGuard()
{
    std::vector<Tile*> alarmTiles;

    Tile* patrolCardTile = tiles[getRow(guard->getPatrolCard())][getColumn(guard->getPatrolCard())];

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (tiles[i][j]->isAlarmOn())
            {
                alarmTiles.push_back(tiles[i][j]);
                this->increaseGuardSpeed();
            }

    setDistance2Guard();

    if (!alarmTiles.empty())
    {
        std::sort(alarmTiles.begin(), alarmTiles.end(), compare);    //la tile con la minima distancia al guardia queda en el ultimo elemento del vector
        guard->setDestination(nextStep(alarmTiles.back())->getCurrentLocation());
        guard->walk(nextStep(alarmTiles.back()));
        
        if (guard->getLocation() == (alarmTiles.back()->getCurrentLocation()))
            alarmTiles.back()->setAlarmToken(false);
    }

    else if (guard->getLocation() != guard->getPatrolCard())
    {
        guard->walk(nextStep(patrolCardTile));
        if (nextStep(patrolCardTile)== patrolCardTile)
            updatePatrolCard();
    }
    else if ( guard->getLocation() == guard->getPatrolCard())
    {
        updatePatrolCard();
        //        moveGuard();

        patrolCardTile = tiles[getRow(guard->getPatrolCard())][getColumn(guard->getPatrolCard())];
        guard->walk(nextStep(patrolCardTile));
    }

}

bool Floor::canIUseLaserHackToken()
{
    bool canUseHackToken = false;
    for (unsigned i = 0; i < ROWS; i++)
    {
        for (unsigned j = 0; j < ROWS; j++)
        {
            if (this->tiles[i][j]->getTileType() == CR_LASER)
                if (!(dynamic_cast<CRLaser*> (this->tiles[i][j])->areHackTokensZero()))    //si hay mas de cero hack tokens
                    canUseHackToken = true;
        }
    }
    return canUseHackToken;
}

bool Floor::canIUseFingerprintHackToken()
{
    bool canUseHackToken = false;
    for (unsigned i = 0; i < ROWS; i++)
    {
        for (unsigned j = 0; j < ROWS; j++)
        {
            if (this->tiles[i][j]->getTileType() == CR_FINGERPRINT)
                if (!(dynamic_cast<CRFingerprint*> (this->tiles[i][j])->areHackTokensZero()))    //si hay mas de cero hack tokens
                    canUseHackToken = true;
        }
    }
    return canUseHackToken;
}

bool Floor::canIUseMotionHackToken()
{
    bool canUseHackToken = false;
    for (unsigned i = 0; i < ROWS; i++)
    {
        for (unsigned j = 0; j < ROWS; j++)
        {
            if (this->tiles[i][j]->getTileType() == CR_MOTION)
                if (!(dynamic_cast<CRMotion*> (this->tiles[i][j])->areHackTokensZero()))    //si hay mas de cero hack tokens
                    canUseHackToken = true;
        }
    }
    return canUseHackToken;
}

bool compare(Tile* i, Tile* j)
{
    return i->getDistance2Guard() > j->getDistance2Guard();
}

