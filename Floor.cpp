#define ROWS 4
#define COLS 4

#include "Floor.h"
#include <chrono>
#include <random>
#include <algorithm>

unsigned floor1(std::vector< std::vector<Tile*> > &floor);
unsigned floor2(std::vector< std::vector<Tile*> > &floor);
unsigned floor3(std::vector< std::vector<Tile*> > &floor);

Floor::Floor(std::vector<Tile*> &deck, unsigned floorNumber)
{
    std::vector< std::vector<Tile*> >::iterator Irow;
    std::vector<Tile*>::iterator Icol;
    unsigned location = 16 * floorNumber;

    for (unsigned i = 0; i < (FLOORTILE_QTY - 2); i++)
    {
        for (Irow = tiles.begin(); Irow != tiles.end(); Irow++)
        {
            for (Icol = Irow->begin(); Icol != Irow->end(); Icol++)
            {
                *Icol = deck.back();
                deck.pop_back();
            }
        }
    }

    tiles[3].push_back(new Stairs);

    tiles[3].push_back(new Safe);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(tiles.begin(), tiles.end(), std::default_random_engine(seed));

    unsigned row = 0;
    unsigned col = 0;

    for (unsigned i = 0; i < FLOORTILE_QTY; i++)
    {
        for (row = 0; row < ROWS; row++)
        {

            for (col = COLS; col < COLS; col++)
            {
                tiles[row][col]->setCurrentLocation((location_t) location);
                setAdjacentTiles(row, col);
                location++;
            }

        }


        createWalls(floorNumber);

    }
}

Floor::~Floor()
{
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

std::vector<Tile*>* Floor::getDeck()
{
    return this->tiles;
}

