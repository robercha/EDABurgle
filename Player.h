/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: rober
 *
 * Created on October 7, 2017, 4:59 PM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "Model.h"


//class Player { //Capaz no es necesario heredar porque las funciones son las mismas
//public:
//    Player();
//    virtual void eventHandler()=0;
//    ~Player();
//protected:
//    virtual void sendAction()=0; //Llama a analyseFunction(); (gameData_t)
//    virtual void switchPlayer()=0;
//    Model* Model;
//    player_t cPlayer; //No sabemos si es player1 player2 o el character
//}; //Estados de la FSM, de acá heredan P1 y P2

class Player
{
public:
    Player();
    void eventHandler(event_t, gameData_t);
    player_t getCurrentPlayer();
    ~Player();
private:
    void sendAction(event_t, gameData_t);
    void switchPlayer();
    player_t currentPlayer;
};

//class Player2: public Player
//{
//public:
//    Player2();
//    eventHandler();
//    ~Player2();
//private:
//    sendAction();
//    switchPlayer();
//};
//
//#endif /* PLAYER_H */