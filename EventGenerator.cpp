#include "EventGenerator.h"

typedef enum
{
    TEST, BUTTONCOUNT, A1_F1, A2_F1, A3_F1, A4_F1, B1_F1, B2_F1, B3_F1, B4_F1, C1_F1, C2_F1, C3_F1, C4_F1, D1_F1, D2_F1, D3_F1, D4_F1,
    A1_F2, A2_F2, A3_F2, A4_F2, B1_F2, B2_F2, B3_F2, B4_F2, C1_F2, C2_F2, C3_F2, C4_F2, D1_F2, D2_F2, D3_F2, D4_F2,
    A1_F3, A2_F3, A3_F3, A4_F3, B1_F3, B2_F3, B3_F3, B4_F3, C1_F3, C2_F3, C3_F3, C4_F3, D1_F3, D2_F3, D3_F3, D4_F3,
    MOVE, PEEK, PASS, USE_TOKEN, BUTTON_COUNT, NO_BUTTON, HOME_EXIT
} button_t; //indices del arreglo

//Networking::Networking(char* ip)
//{
//    this->ip = ip;
//    this->sock = NULL;
//    this->mp = NULL;
//    this->sa = NULL;
//    this->mysocket = NULL;
//    apr_initialize();
//    apr_pool_create(&mp, NULL);
//
//    createLog();
//
//}
//
//bool
//Networking::tryConnecting()
//{
//
//    status = apr_sockaddr_info_get(&sa, ip, AF_INET, DEF_REMOTE_PORT, 0, mp);
//
//    if (status == APR_SUCCESS)
//    {
//
//        // Con el Socket Address creado, tenemos que crear ahora el "Network Socket" (básicamente el protocolo con el que le vamos a hablar al Socket Address...
//        // El pirmer parámetro es el ID del Network Address.
//        // El segundo es el protocolo a utilizar enrte IPv4 e IPV6. Si ponemos APR_INET intenta primero IPv4 si no puede va por IPv6. Si ponemos APR_INET6 hace lo inverso.
//        //     Si ponemos APR_UNSPEC le decimos que nos es indistinto. Que use cualquiera de los dos.
//        // El tercer parámetro refiere al modo de conexión que queremos tener. Básicamente con SOCK_STREAM tenemos una conexión hasta que del otro lado deciden cortarla.
//        //    Nosotros vamos a usar siempre SOCK_STREAM. Más detalles en: http://stackoverflow.com/questions/5815675/strange-thing-sock-dgram-and-sock-stream
//        // El cuarto parámetro refier al protocolo a utilizar. Nosotros vamos a usar siempre TCP en la cátedra. Por lo tanto APR_PROTO_TCP.
//        // El quinto parámetro es el pool de memoria que usa APR. previamente inicializado.
//        status = apr_socket_create(&mysocket, APR_INET /*APR_UNSPEC*/, SOCK_STREAM, APR_PROTO_TCP, mp);
//
//        if (status == APR_SUCCESS)
//        {
//            sleep(1);
//
//            //Si pudimos crear el Address Socket y Network Socket, antes de crear la conexión le tenemos que decir al programa como utilizar el Network Socket.
//            //Nosotros vamos a configurar los timeouts del Network Socket para que sea no bloqueante ya que nos interesa trabajar con Event Driven Programming
//            //Para lo que necesitamos funciones no bloqueantes.
//
//            //Aqui ACTIVAMOS (PONIENDO 1) la opcion APR_SO_NONBLOCK. Si pusieramos 0 seria bloqueante.
//            //Esto hace que al utilizar el Socket, la función que lo utiliza no se quede esperando a que pase algo con el socket. Se fija si pasó algo y vuelve enseguida.
//            apr_socket_opt_set(mysocket, APR_SO_NONBLOCK, 1);
//
//            //Una vez que seteamos no no es bloqueante, sino que vuelva, podemos poner en cuanto tiempo. Si queremos que vuelva en forma inmediata entonces le ponemos 0.
//            //Sino le ponemos el tiempo que deseemos que espere para volver. Al principio le ponemos un tiempito para establecer la conexión.
//            //Una vez establecida la conexión lo pasamos a 0 para que las lecturas/ escrituras sean instantáneas y no nos cuelguen nuestro Event Driven Programming.
//            apr_socket_timeout_set(mysocket, DEF_SOCK_TIMEOUT);
//
//            //Una vez que configuramos el Network Socket, Lo utilizamos junto con el Address Socket para tratar de conectarnos.
//            //Como arriba configuramos el socket timeout en DEF_SOCK_TIMEOUT va a tratar de conectarse por DEF_SOCK_TIMEOUT tiempos
//            //(fijarse arriba como está definida para que resulte en segundos) Si por ese tiempo no se conecta vuelve.
//            //Si fuera con 0 segundos, sólamante si del otro lado lo estan esperando vuelve con que se pudo conectar. En otras palabras,
//            //si de una no se pudo conectar porque no había nadie escuchando del otro lado, vuelve sin conectarse. De la forma que lo definimos acá,
//            //espera DEF_SOCK_TIMEOUT antes de volver (por si en ese tiempo en el address definido por el Socket Address alguien se pone a escuchar).
//            status = apr_socket_connect(mysocket, sa);
//
//
//            if (status == APR_SUCCESS)
//            {
//                //Una vez que nos conectamos mantenemos el Network Socket en no bloqueante
//                //Y lo pasamos a 0 segundos para cumplir con nuestra hipótesis de Event Driven Programming.
//                apr_socket_opt_set(mysocket, APR_SO_NONBLOCK, 1);
//                apr_socket_timeout_set(mysocket, 0);
//
//                //Por último devolvemos el Network Socket creado en nuestro primer parámetro.
//                //Noten que una vez que nos conectamos el Address Socket ya no sirve. La conexión
//                //Se identifica con el Network Socket.
//                sock = mysocket;
//            }
//            else
//            {
//                //Si no nos pudimos conectar, Buscamos qué error se produjo.
//                char errorstring[1024]; //creamos un espacio donde apr nos de el error.
//                apr_strerror(status, errorstring, 1023); //le pedimos a apr que nos lo traduzca
//                printf("%s", errorstring); //lo imprimimos.
//            }
//        }
//        else
//            printf("\nCANNOT CREATE SOCKET TO CONNECT");
//    }
//    else
//        printf("\nCANNOT GET SERVER INFO\n");
//
//    return status == APR_SUCCESS ? true : false;
//}
//
//bool
//Networking::listen(void)
//{
//    status = apr_sockaddr_info_get(&sa, HOME_ADRESS, AF_INET, DEF_LISTEN_PORT, 0, mp);
//
//    if (status == APR_SUCCESS)
//    {
//
//        // Con el Socket Address creado, tenemos que crear ahora el "Network Socket" (básicamente el protocolo con el que le vamos a hablar al Socket Address...)
//        // El pirmer parámetro es el ID del Network Address.
//        // El segundo es el protocolo a utilizar enrte IPv4 e IPV6. Si ponemos APR_INET intenta primero IPv4 si no puede va por IPv6. Si ponemos APR_INET6 hace lo inverso.
//        //     Si ponemos APR_UNSPEC le decimos que nos es indistinto. Que use cualquiera de los dos.
//        // El tercer parámetro refiere al modo de conexión que queremos tener. Básicamente con SOCK_STREAM tenemos una conexión hasta que del otro lado deciden cortarla.
//        //    Nosotros vamos a usar siempre SOCK_STREAM. Más detalles en: http://stackoverflow.com/questions/5815675/strange-thing-sock-dgram-and-sock-stream
//        // El cuarto parámetro refier al protocolo a utilizar. Nosotros vamos a usar siempre TCP en la cátedra. Por lo tanto APR_PROTO_TCP.
//        // El quinto parámetro es el pool de memoria que usa APR. previamente inicializado.
//
//        status = apr_socket_create(&mysocket, APR_IPV6_ADDR_OK/*APR_UNSPEC*/, SOCK_STREAM, APR_PROTO_TCP, mp);
//
//
//        if (status == APR_SUCCESS)
//        {
//
//            //Si pudimos crear el Address Socket y Network Socket, antes de crear la conexión le tenemos que decir al programa como utilizar el Network Socket.
//            //Nosotros vamos a configurar los timeouts del Network Socket para que sea no bloqueante ya que nos interesa trabajar con Event Driven Programming
//            //Para lo que necesitamos funciones no bloqueantes.
//
//            //Aqui ACTIVAMOS (PONIENDO 1) la opcion APR_SO_NONBLOCK. Si pusieramos 0 seria bloqueante.
//            //Esto hace que al utilizar el Socket, la función que lo utiliza no se quede esperando a que pase algo con el socket. Se fija si pasó algo y vuelve enseguida.
//            apr_socket_opt_set(mysocket, APR_SO_NONBLOCK, 1);
//
//            //Una vez que seteamos no no es bloqueante, sino que vuelva, podemos poner en cuanto tiempo. Si queremos que vuelva en forma inmediata entonces le ponemos 0.
//            //Sino le ponemos el tiempo que deseemos que espere para volver. Al principio le ponemos un tiempito para establecer la conexión.
//            //Una vez establecida la conexión lo pasamos a 0 para que las lecturas/ escrituras sean instantáneas y no nos cuelguen nuestro Event Driven Programming.
//            apr_socket_timeout_set(mysocket, 0);
//
//            //Si en el futuro matamos la conexion (con shutdows), podemos reusar el socket
//            apr_socket_opt_set(mysocket, APR_SO_REUSEADDR, 1);
//
//            //Una vez creado el Network Socket y el Address Socket, se llama a apr_socket_bind()
//            //Que básicamente une los dos en en Network Socket (s) para luego poder usarlo para escuchar.
//            status = apr_socket_bind(mysocket, sa);
//
//            if (status == APR_SUCCESS)
//            {
//                // En caso de que hayan unido los dos sockets correctamente
//                // Llamo a la función que escucha el puerto.
//                // Recuerden que en s voy a tener el socket que escucha.
//                // Por cada conexión que "escuchemos" se va a crear un nuevo socket para identificar dicha conexión (seguir viendo main).
//                // Voy a poder levantar hasta SOMAXCONN conexiones en simultáneo.
//                status = apr_socket_listen(mysocket, SOMAXCONN);
//
//                // Si logré comenzar a escuchar entonces le paso al usuario el apr_socket_t * en el que estoy escuchando.
//                if (status == APR_SUCCESS)
//                    sock = mysocket;
//                else
//                    printf("\nNOT LISTENING");
//
//            }
//            else
//                printf("\nfailed to bind socket");
//
//        }
//        else
//            printf("\ncannot create socket");
//
//    }
//    else
//        printf("\ncannot get info?");
//
//    return status == APR_SUCCESS ? true : false;
//}
//
//bool
//Networking::createLog(void)
//{
//    bool status;
//    struct tm *dateInfo; //estructura con informacion de la fecha y hora de la partida
//    time_t rawTime;
//    time(&rawTime);
//    dateInfo = localtime(&rawTime);
//
//    char auxArray[250];
//    auxArray[0] = '\0';
//    strcat(auxArray, asctime(dateInfo));
//    char* pointer = strchr(auxArray, '\n'); //porque la funcion asctime termina con \n
//    *pointer = '\0'; //reemplazamos el '\n' con un terminador '\0'
//    strcat(auxArray, ".txt"); //agregamos el .txt
//
//    this->file.open(auxArray, std::ofstream::out | std::ofstream::app);
//    file << "Log created.";
//    return status = file.is_open();
//}
//
//void
//Networking::startTimerCount()
//{
//    this->timerCount = apr_time_now();
//}
//
//unsigned
//Networking::getTimerCount()
//{
//    return apr_time_now() - timerCount;
//}
//
//Networking::~Networking()
//{
//    apr_pool_destroy(mp);
//    if (sock != NULL)
//    {
//        apr_socket_shutdown(sock, APR_SHUTDOWN_READWRITE);
//        apr_socket_close(sock);
//    }
//    apr_terminate();
//}
//
//bool
//Networking::getEvent(userData_t*)
//{
//
//}

userInterface::userInterface()
{
    this->queue = al_create_event_queue();

    if (this->queue != NULL)
    {
        al_register_event_source(this->queue, al_get_mouse_event_source());
        al_register_event_source(this->queue, al_get_keyboard_event_source());
        // al_register_event_source(this->queue, al_get_display_event_source(this->display));        HACER ALGO AL RESPECTO
    }
    this->buttons = (buttons_t*) malloc(sizeof (buttons_t) * BUTTON_COUNT);
    //this->event=NULL;
}

userInterface::~userInterface()
{
    free(this->buttons);
}

bool
userInterface::getEvent(userData_t* userData)
{
    bool state = false;
    ALLEGRO_EVENT preEvent;
    state = al_get_next_event(queue, &preEvent);
    checkClick(userData, state, preEvent); //analizamos que boton se toco
}

unsigned
userInterface::checkClick(userData_t* userData, unsigned state, ALLEGRO_EVENT event) //chequea si se toco algun boton y devuelve la posicion en el arreglo del boton q se toco
{
    unsigned i;

    if ((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) && state) //Se analizan solo eventos de mouse y solo en el caso de que un evento haya ocurrido
    {
        for (i = 0; i < BUTTON_COUNT; i++) //recorre el arreglo de los botones y se fija si se toco dentro del espacio del boton
        {
            //if (display->buttons[i].screen != userData->currentScreen) //Si la pantalla del boton en cuestion no coincide con la pantalla actual de juego no genera evento
            //continue;
            if (((event.mouse.x >= buttons[i].initialX) && (event.mouse.x <= (buttons[i].initialX + buttons[i].width))) &&
                    ((event.mouse.y >= buttons[i].initialY) && (event.mouse.y <= (buttons[i].initialY + buttons[i].height))))
            {
                userData->buttonClicked = i; //Indice en el arreglo de botones
                userData->mouseX = event.mouse.x;
                userData->mouseY = event.mouse.y;
                break;
            }
        }
    }
    else
        userData->buttonClicked = NO_BUTTON; //No se clickeo ningun boton

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //si el usuario quiere salir del juego
        userData->buttonClicked = HOME_EXIT;
    if (userData->buttonClicked == TEST)
        printf("tu vieja");
}

void
userInterface::setButton(unsigned buttonIndex, unsigned buttonW, unsigned buttonH, unsigned buttonX, unsigned buttonY)
{
    buttons[buttonIndex].initialX = buttonX;
    buttons[buttonIndex].initialY = buttonY;
    buttons[buttonIndex].height = buttonH;
    buttons[buttonIndex].width = buttonW;
}

