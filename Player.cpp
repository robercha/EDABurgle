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

Player::Player()
{
}

Player::~Player()
{
}

Player::eventHandler(event_t event, gameData_t gameData)    
{
    switch (event)      //Los eventos que me pasan son solo ACTION y TURN
    {
        case ACTION: sendAction(event, gameData); //No me ayuda en nada que me pasen ACTION para la evaluacion de la accion, DEBE ESTAR EN GAMEDATA LA ACCION??
            break; //Pasamos por parámetro el indice al arreglo de characters
        case TURN: switchPlayer();
            break;
    }
}

state_t
Player::getCurrentPlayer()
{
    return currentPlayer;
}

Player::switchPlayer()
{
}//dummy function

Player::sendAction(event_t, gameData_t) //Llama a analizaFunction de model, aca empieza la lógica del juego.
{
}

