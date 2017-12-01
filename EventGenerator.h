#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_H

#include "View.h"
#include <fstream>
#include <allegro5/allegro5.h>
#include <allegro5/events.h>
#include <apr-1.0/apr_time.h>
#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr.h>
#include <apr-1.0/apr_file_io.h>
#include <apr-1.0/apr_strings.h>
#include <apr-1.0/apr_network_io.h>

#define DEF_LISTEN_PORT 15251       //Port que queremos escuchar
#define DEF_REMOTE_PORT 15251         //Port al que nos queremos conectar
#define DEF_REMOTE_HOST "127.0.0.1"
#define HOME_ADRESS "127.0.0.1"
#define DEF_SOCKET_BACKLOG SOMAXCONN
#define SOCK_TIMEOUT (APR_USEC_PER_SEC * 5)
#define DEF_SOCK_TIMEOUT (APR_USEC_PER_SEC * 5) //TIMEOUT (ver más adelante).
#define SECONDS_TO_WAIT 10
#define TIMEOUT_SECONDS 60
#define MINTIME 200000
#define MAXTIME 10000000
#define BUFSIZE 516
#define MAXIP 15

#define DISPLAYW 1090
#define DISPLAYH 720

typedef enum {
    packet//   ACK = 0x01, AGREE, DISAGREE, NAME = 0x10, NAME_IS, I_AM, INITIAL_G_POS, START_INFO, YOU_START = 0x20, I_START, PEEK = 0x30, MOVE, SPENT_OK, ADD_TOKEN, USE_TOKEN, THROW_DICE, SAFE_OPENED, CREATE_ALARM, SPY_PATROL, PLACE_CROW, OFFER_LOOT, REQUEST_LOOT, PICK_UP__LOOT, PASS, ROLL_DICE_FOR_LOOT, GUARD_MOVEMENT, WE_WON, WE_LOST, GAME_OVER, QUIT = 0xFE, ERROR
} packet_t;

typedef enum {
    CHAU//   ACTION, SWITCH, PREEVENTCOUNT
} preEvent_t;

typedef enum {
    MOVE, TILE, PEEK, TRUEEVENTCOUNT, TIMEOUT, ESC
} trueEvent_t;

typedef enum {
    A1_F1,A2_F1,A3_F1,A4_F1,B1_F1,B2_F1,B3_F1,B4_F1,C1_F1,C2_F1,C3_F1,C4_F1,D1_F1,D2_F1,D3_F1,D4_F1,
            A1_F2,A2_F2,A3_F2,A4_F2,B1_F2,B2_F2,B3_F2,B4_F2,C1_F2,C2_F2,C3_F2,C4_F2,D1_F2,D2_F2,D3_F2,D4_F2,
            A1_F3,A2_F3,A3_F3,A4_F3,B1_F3,B2_F3,B3_F3,B4_F3,C1_F3,C2_F3,C3_F3,C4_F3,D1_F3,D2_F3,D3_F3,D4_F3,
            MOVE,PICK,PASS,USE_TOKEN,BUTTON_COUNT,NO_BUTTON,HOME_EXIT 
} button_t; //indices del arreglo

typedef struct buttons {
    //screen_t screen;
    double initialX;
    double initialY;
    double width;
    double height;
} buttons_t;

typedef struct event {
    preEvent_t preEvent;
    trueEvent_t trueEvent;
    player_t player;
} event_t;

typedef struct userData {
    event_t event;
    char* packet;
    double mouseX;
    double mouseY;
    buttons_t buttonClicked; //ENUM de botones
} userData_t;

class EventGenerator {
public:
    bool virtual getEvent(userData_t*) = 0;
};

//class Networking : public EventGenerator {
//public:
//    Networking(char* ip);
//    ~Networking();
//    bool getEvent(userData_t*);
//    bool tryConnecting(void);
//    bool listen(void);
//    bool connect(void);
//    unsigned sendPacket(char*);
//    bool writeLog(char*);
//    unsigned getTimerCount(void);
//    void startTimerCount(void);
//    //setTimerCount();
//private:
//    char* ip;
//    packet_t lastPacketSent;
//    unsigned getPacket(char*);
//    bool createLog(void);
//    std::ofstream file;
//    apr_time_t timerCount;
//    apr_status_t status; //esta variable la usamos para leer los errores y verificar cuando las cosas andan o no.
//    apr_pool_t *mp; //esta variable la conocemos del tp anterior
//    apr_socket_t *sock;
//    apr_sockaddr_t *sa; //temp
//    apr_socket_t *mysocket; //temp
//
//};

class userInterface : public EventGenerator {
public:
    userInterface();
    bool getEvent(userData_t*);
    unsigned checkClick(userData_t*); //Devuelve el indice en el arreglo de botones que es un enum.
    ~userInterface();
private:
    
    ALLEGRO_EVENT* event;
    ALLEGRO_EVENT_QUEUE* queue;
    buttons_t buttons[BUTTONCOUNT];
};




#endif /* EVENTGENERATOR_H */