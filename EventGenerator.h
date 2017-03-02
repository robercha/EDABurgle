
#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_H

#include <fstream>
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
    ACTION, SWITCH, PREEVENTCOUNT
} preEvent_t;

typedef enum {
    MOVE, TILE, PEEK, TRUEEVENTCOUNT
} trueEvent_t;

typedef enum {
    PLAYER1, PLAYER2
} player_t; //no se si va en este header o en otro, capaz de la fsm

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
    buttonIndex_t buttonClicked; //ENUM de botones
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
    bool tryConnecting();
    bool listen();
    bool connect();
    unsigned sendPacket(char*);
    writeLog(char*);
    apr_time_t getTimerCount();
    void startTimerCount();
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
    ALLEGRO_EVENT event;
    button_t buttons[BUTTON_COUNT];
}




#endif /* EVENTGENERATOR_H */

