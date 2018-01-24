/*
 * 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Floor.cpp
 * Author: rober
 * 
 * Created on January 23, 2018, 6:40 PM
 */

#include <list>

#include "Floor.h"

Floor::Floor(std::list<Tile*> &tileDeck) 
{
    std::vector< std::vector<Tile*> >::iterator row;
    std::vector<Tile*>::iterator col;
    
    for(unsigned i=0; i<16; i++)
    {
        for(row = tiles.begin(); row != tiles.end(); row++)
        {
            for(col = row->begin(); col!=row->end(); col++)
            {
                *col = tileDeck.back();
                tileDeck.pop_back();
            }
        }
    }   
}


Floor::~Floor() {
}

