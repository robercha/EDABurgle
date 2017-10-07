/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: rober
 * 
 * Created on October 7, 2017, 4:59 PM
 */

#include "Player.h"

Player::Player() {
}



Player::~Player() {
}

Player::eventHandler(event_t event, gameData_t gameData){
    switch(event)
    {
        case ACTION: sendAction(event, gameData); break; //Pasamos por parámetro el indice al arreglo de characters
        case TURN: switchPlayer(); break;
    }
}

player_t Player::getCurrentPlayer()
{
    return currentPlayer;
}

Player::switchPlayer(){
}//dummy function

Player::sendAction(event_t, gameData_t) //Llama a analizaFunction de model, aca empieza la lógica del juego.
{
}

