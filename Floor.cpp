#include <list>

#include "Floor.h"

Floor::Floor(std::vector<Tile*> &deck)
{
    std::vector< std::vector<Tile*> >::iterator row;
    std::vector<Tile*>::iterator col;
    
    for (unsigned i = 0; i < (FLOORTILE_QTY-2); i++)
    {
        for (row = tiles.begin(); row != tiles.end(); row++)
        {
            for (col = row->begin(); col != row->end(); col++)
            {
                *col = deck.back();
                deck.pop_back();
            }
        }
    }
    
    tiles.push_back(new Stairs);
    tiles.push_back(new Safe);
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(tiles.begin(), tiles.end(), std::default_random_engine(seed));

    
}

Floor::~Floor()
{
}

