
#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_H

#include <apr-1.0/apr_time.h>
#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr.h>
#include <apr-1.0/apr_file_io.h>
#include <apr-1.0/apr_strings.h>
#include <apr-1.0/apr_network_io.h>

#define DEF_LISTEN_PORT 15251       //Port que queremos escuchar
#define DEF_REMOTE_PORT 15251         //Port al que nos queremos conectar
#define DEF_REMOTE_HOST "127.0.0.1"
#define MINTIME 200000
#define MAXTIME 10000000

class EventGenerator {
public:
    virtual void getEvent(userData_t*) = 0;
};

class Networking : public EventGenerator {
public:
    Networking(char* ip);
    ~Networking();
    void getEvent(userData_t*);
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
    apr_status_t doConnect(const char*, apr_sockaddr_t *, apr_socket_t *);
    FILE* file;
    apr_time_t timerCount;
    apr_status_t status; //esta variable la usamos para leer los errores y verificar cuando las cosas andan o no.
    apr_pool_t *mp; //esta variable la conocemos del tp anterior
    apr_socket_t *clientSock;
    apr_sockaddr_t *sa; //temp
    apr_socket_t *mysocket; //temp

};




#endif /* EVENTGENERATOR_H */

