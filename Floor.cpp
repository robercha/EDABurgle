#include <list>

#include "Floor.h"

Floor::Floor(std::list<Tile*> &tileDeck)
{
    std::vector< std::vector<Tile*> >::iterator row;
    std::vector<Tile*>::iterator col;

    for (unsigned i = 0; i < 16; i++)
    {
        for (row = tiles.begin(); row != tiles.end(); row++)
        {
            for (col = row->begin(); col != row->end(); col++)
            {
                *col = tileDeck.back();
                tileDeck.pop_back();
            }
        }
    }
}

Floor::~Floor()
{
}

