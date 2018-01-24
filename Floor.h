/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Floor.h
 * Author: rober
 *
 * Created on January 23, 2018, 6:40 PM
 */

#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "Tile.h"
#include "Guard.h"

class Floor {
public:
    Floor();
    ~Floor();
    //void randomizeFloor();
private:
    std::vector< std::vector<Tile> > tiles;
 
};

#endif /* FLOOR_H */

