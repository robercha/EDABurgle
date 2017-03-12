
#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_H

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

typedef enum {
    ACK = 0x01, AGREE, DISAGREE, NAME = 0x10, NAME_IS, I_AM, INITIAL_G_POS, START_INFO, YOU_START = 0x20, I_START, PEEK = 0x30, MOVE, SPENT_OK, ADD_TOKEN, USE_TOKEN, THROW_DICE, SAFE_OPENED, CREATE_ALARM, SPY_PATROL, PLACE_CROW, OFFER_LOOT, REQUEST_LOOT, PICK_UP__LOOT, PASS, ROLL_DICE_FOR_LOOT, GUARD_MOVEMENT, WE_WON, WE_LOST, GAME_OVER, QUIT = 0xFE, ERROR
} packet_t;

typedef enum {
    ACTION, SWITCH, PREEVENTCOUNT
} preEvent_t;

typedef enum {
    MOVE, TILE, PEEK, TRUEEVENTCOUNT
} trueEvent_t;

typedef enum {
    MOVE,TILE, BUTTONCOUNT
}; button_t

typedef enum {
    PLAYER1, PLAYER2
} player_t; //no se si va en este header o en otro, capaz de la fsm

typedef struct buttons {
    //screen_t screen;
    double initialX;
    double initialY;
    double width;
    double height;
} button_t;

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
    button_t buttonClicked; //ENUM de botones
} userData_t;

class EventGenerator {
public:
    virtual void getEvent(userData_t*) = 0;
};

class Networking : public EventGenerator {
public:
    Networking(char* ip);
    ~Networking();
    void getEvent(userData_t*);
    bool tryConnecting(void);
    bool listen(void);
    bool connect(void);
    unsigned sendPacket(char*);
    writeLog(char*);
    apr_time_t getTimerCount(void);
    void startTimerCount(void);
    //setTimerCount();
private:
    char* ip;
    packet_t lastPacketSent;
    unsigned getPacket(char*);
    bool createLog(void);
    std::ofstream file;
    apr_time_t timerCount;
    apr_status_t status; //esta variable la usamos para leer los errores y verificar cuando las cosas andan o no.
    apr_pool_t *mp; //esta variable la conocemos del tp anterior
    apr_socket_t *sock;
    apr_sockaddr_t *sa; //temp
    apr_socket_t *mysocket; //temp

};

class userInterface : public EventGenerator {
public:
    bool getEvent(userData_t*);
    unsigned checkClick(double x, double y); //Devuelve el indice en el arreglo de botones que es un enum.
private:
    ALLEGRO_EVENT* event;
    button_t buttons[BUTTONCOUNT];
}




#endif /* EVENTGENERATOR_H */