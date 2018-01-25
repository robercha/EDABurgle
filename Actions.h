/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:  Actions.h
 * Author: rober
 *
 * Created on January 25, 2018, 4:11 PM
 */

#ifndef ACTIONS_H
#define ACTIONS_H

typedef enum {

}modelEvent_t;

class Actions {
public:
    Actions();
    virtual ~Actions();
    virtual void eventHandler(gameData_t gameData , modelEvent_t event)=0;
protected:
 
        
    

};

#endif /* ACTIONS_H */

