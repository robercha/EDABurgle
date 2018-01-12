#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/timer.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>



#define DISPLAYW 1280
#define DISPLAYH 706
#define V_TOTAL_PLAYERS         2
#define V_TOTAL_GUARDS          3
#define V_TOTAL_LOOTS           3
#define V_TOTAL_TILES           48
#define V_TOTAL_CRACKINGDICE    6

enum class button {
    //tiles
    A1F1, A2F1, A3F1, A4F1, B1F1, B2F1, B3F1, B4F1, C1F1, C2F1, C3F1, C4F1, D1F1, D2F1, D3F1, D4F1,
    A1F2, A2F2, A3F2, A4F2, B1F2, B2F2, B3F2, B4F2, C1F2, C2F2, C3F2, C4F2, D1F2, D2F2, D3F2, D4F2,
    A1F3, A2F3, A3F3, A4F3, B1F3, B2F3, B3F3, B4F3, C1F3, C2F3, C3F3, C4F3, D1F3, D2F3, D3F3, D4F3,
    //LOOTF1, LOOTF2, LOOTF3,
    //actions
    MOVE, PEEK, PASS, ETC,

    BUTTON_COUNT, NOBUTTON// , HOME_EXIT
};

enum class character_t {
    JUICER, HACKER, ACROBAT, SPOTTER, HAWK, RAVEN, PETERMAN, GUARD
};

enum class loot_t {
    TIARA, KITTY, PAINTING, MIRROR, KEYCARD, ISOTOPE, GEMSTONE, GOBLET, CHIHUAHUA, GOLD, GOLD2, NO_LOOT,
};

enum class token_t {
    ALARMTOKEN, STEALTHTOKEN, HACKTOKEN, CRACKEDTOKEN, DOWNSTAIRSTOKEN, KITTYTOKEN, CROWTOKEN, OPENTOKEN
};

enum class room_t {
    ATRIUM, CAMERA, CR_FINGERPRINT, CR_LASER, CR_MOTION, DEADBOLT, DETECTOR, FINGERPRINT, FOYER, KEYPAD,
    LABORATORY, LASER, LAVATORY, MOTION, SAFE, SECRETDOOR, SERVICEDUCT, STAIRS, THERMO, WALKWAY, ROOMBACK
};

enum class location_t {
    A1F1, A2F1, A3F1, A4F1, B1F1, B2F1, B3F1, B4F1, C1F1, C2F1, C3F1, C4F1, D1F1, D2F1, D3F1, D4F1,
    A1F2, A2F2, A3F2, A4F2, B1F2, B2F2, B3F2, B4F2, C1F2, C2F2, C3F2, C4F2, D1F2, D2F2, D3F2, D4F2,
    A1F3, A2F3, A3F3, A4F3, B1F3, B2F3, B3F3, B4F3, C1F3, C2F3, C3F3, C4F3, D1F3, D2F3, D3F3, D4F3, V_NO_LOCATION
};

enum class patrol_t {
    A1, A2, A3, A4, B1, B2, B3, B4, C1, C2, C3, C4, D1, D2, D3, D4, NO_PATROL
};

enum class safe_t { //combination numbers
    NUMBER1, NUMBER2, NUMBER3, NUMBER4, NUMBER5, NUMBER6
};

enum class dice_t { //tipos de dados
    GUARD_DIE1, GUARD_DIE2, GUARD_DIE3, GUARD_DIE4, GUARD_DIE5, GUARD_DIE6,
    SAFE_DIE1, SAFE_DIE2, SAFE_DIE3, SAFE_DIE4, SAFE_DIE5, SAFE_DIE6
};

typedef struct {
    character_t character;
    unsigned stealthTokens;
    unsigned actionsLeft;
    location_t location;

} player_t;

typedef struct {
    character_t character; //es necesario? se sabe q es guardia
    unsigned movements; //moves por turno del guardia, 6 como maximo
    location_t location;
    location_t guardDie; //donde esta el dado (a donde va si no suenan alarmas)
    patrol_t patrolDeck;

} guard_t;

typedef struct {
    room_t iAm; //e.g. atrium
    bool InvisibilityCloak; //esta dada vuelta o se sabe qué es?
    bool alarm; //on-off
    unsigned combinationNumber; //0 si es la safe, ó 1,2,3,4,5,6
    bool crackedToken; //si salió con los cracking dice, para dibujar cracked token sobre el combination number
    unsigned howManyHackTokens; //solo computers room (3 comp rooms)
    bool goldBarOnTheLoose; //dónde esta la segunda gold bar q debe ser agarrada por alguno de los ladrones
    bool kittyToken; //para kitty token
    bool crowToken;
    bool keypadOpenToken; //para keypad room
    bool stairsToken;
    unsigned howManyStealthTokens; //solo para lavatory

} tile_t;

typedef struct {
    player_t players[V_TOTAL_PLAYERS];
    guard_t guards[V_TOTAL_GUARDS];
    tile_t tiles[V_TOTAL_TILES];
    loot_t loots [V_TOTAL_LOOTS]; //para mostrar los loots de c/piso abajo de los floors
    tile_t currentCardSelected; //muestra en upper-right corner toda la informacion
    unsigned crackingDice[V_TOTAL_CRACKINGDICE];

    //aca faltan los mensajes
    //aca faltan las actions (botones)

    bool gameWon; //solo fijarse por gameWon=true
    bool gameLost; //solo fijarse por gameLost=true


} graphicsData_t;

typedef struct bitmap //informacion de cada boton (bitmap)
{
    //ALLEGRO_BITMAP* image; //el archivo
    //unsigned screen; //a que pantalla pertenece
    unsigned int x; //posicion en la pantalla
    unsigned int y;
    unsigned int width; //ancho y largo de la misma
    unsigned int height;
} bitmap_t;

class View {
public:

    void menuDisplay(void); //borrar
    unsigned getButtonX(unsigned); //se le pasa el indice del arreglo de botones
    unsigned getButtonY(unsigned);
    unsigned getButtonH(unsigned);
    unsigned getButtonW(unsigned);
    View();
    virtual ~View();
    bool updateGraphics(); //devuelve false si hubo problema al updatear los graficos, e.g. al cargar algun bitmap


private:

    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *background;
    ALLEGRO_EVENT_QUEUE* eventQueue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_FONT *titleFont;
    ALLEGRO_FONT *textFont;
    unsigned int backgroundWidth;
    unsigned int backgroundHeight;
    unsigned int width;
    unsigned int height;
    graphicsData_t* graphicsData; //deberia ser public para q model la modifique
    //bitmap_t* buttons;
    std::vector<bitmap_t>* buttons; //  no se si necesitamos buttons, porque toda la info para dibujar esta en graphicsData
    //  y las coordenadas salen de la galera, asi como el width&height so

    unsigned getBitmapX(ALLEGRO_BITMAP*);
    unsigned getBitmapY(ALLEGRO_BITMAP*);
    unsigned getBitmapW(ALLEGRO_BITMAP*);
    unsigned getBitmapH(ALLEGRO_BITMAP*);
    ALLEGRO_BITMAP* loadCharacter(character_t); //funciones que cargan el bitmap
    ALLEGRO_BITMAP* loadLoot(loot_t);
    ALLEGRO_BITMAP* loadToken(token_t);
    ALLEGRO_BITMAP* loadRoom(room_t);
    ALLEGRO_BITMAP* loadPatrolCard(patrol_t);
    ALLEGRO_BITMAP* loadDie(dice_t);
    ALLEGRO_BITMAP* loadSafeNumber(safe_t);

    void writeTitle();

    void drawChatDividers();

    void drawBoard();
    void drawCharactersInfo();
    void drawFloors();
    void drawTiles();
    void drawWalls();

    void writeFloorTexts();
    void drawPatrolDecks();
    void drawLoots();

    void drawCharacters();
    void drawGuardDice();
    void drawGuards();
    void drawTokensOnTiles(); //ver bien
    //void drawBackground();

    void drawCardInfo();
    void showNoCardSelected();
    void drawTileSelectedInfo();
    void drawSelectedTileTokens();
    void drawLootSelectedInfo();
    void writeActions();
    void writeMessages();

};

#endif /* VIEW_H */


