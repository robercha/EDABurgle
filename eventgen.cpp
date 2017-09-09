typedef enum {ACTION, SWITCH, PREEVENTCOUNT} preEvent_t;
typedef enum {MOVE, TILE, PEEK, TRUEEVENTCOUNT} trueEvent_t;

typedef struct event
{
	preEvent_t preEvent;
	trueEvent_t trueEvent;
	player_t player;
}event_t;

typedef struct userData
{
	event_t event;
	char* packet;
	double mouseX;
	double mouseY;
	buttonIndex_t buttonClicked; //ENUM de botones
	
}; userData_t

class EventGenerator
{
public:
	virtual getEvent(userData_t*) = 0;
private:
	userData_t userData; //No debería tenerlo, se lo pasa controller.
}


class Networking: public EventGenerator
{
public:
	void getEvent(userData_t*); //Modifica la estrucutra event es userData, recibe el paquete
	bool connect(?);//Realiza la coneccion al principio de la partida, se queda en la funcion hasta que se conecta
	bool/n bytes sendPacket(userData_t*); //Devuelve cantidad de bytes mandados
	bool writeLog(char*); //loggea los paquetes
	getTimerCount();
	setTimerCount();
private:
	char* ip;
	APR_SOCKET (?) socket; //apr shit
	packet_t laspacketSend; //ENUM
	bool/n bytes getPacket(char* buffer);
	File* file;
	apr_timer timer; //timer de apr para el timeout
}


class File
{
public: 
	write(char*);
private:
	FILE* file;
}

typedef struct buttons
{
	screen_t screen;
	double initialX;
	double initialY;
	double width;
	double height;
}button_t;

class userInterface: public EventGenerator
{
public:
	bool getEvent(userData_t*);
	unsigned checkClick(double x, double y); //Devuelve el indice en el arreglo de botones que es un enum.
private:
	ALLEGRO_EVENT event;
	button_t buttons[BUTTON_COUNT];

}

