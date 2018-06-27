#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/timer.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <string>




#define DISPLAYW 1280
#define DISPLAYH 706
#define V_TOTAL_PLAYERS         2
#define V_TOTAL_GUARDS          3
#define V_TOTAL_LOOTS           3
#define V_TOTAL_TILES           48
#define V_TOTAL_CRACKINGDICE    6
#define V_TOTAL_FLOORS          3
#define V_ROWS                  4
#define V_COLUMNS               4

enum class button_t {
    //tiles
    A1F1, B1F1, C1F1, D1F1, A2F1, B2F1, C2F1, D2F1, A3F1, B3F1, C3F1, D3F1, A4F1, B4F1, C4F1, D4F1,
    A1F2, B1F2, C1F2, D1F2, A2F2, B2F2, C2F2, D2F2, A3F2, B3F2, C3F2, D3F2, A4F2, B4F2, C4F2, D4F2,
    A1F3, B1F3, C1F3, D1F3, A2F3, B2F3, C2F3, D2F3, A3F3, B3F3, C3F3, D3F3, A4F3, B4F3, C4F3, D4F3,
    //loots
    LOOTF1, LOOTF2, LOOTF3,
    //patrol decks
    PATROL_DECK_1, PATROL_DECK_2, PATROL_DECK_3,
    //actions
    MOVE, PEEK, PASS, ADD_DICE_TO_SAFE, ROLL_DICE_FOR_SAFE, SPEND_ACTIONS_TO_ENTER, HACK_COMPUTER, USE_HACK_TOKEN,
    OFFER_LOOT, REQUEST_LOOT, PICK_UP_LOOT, CREATE_ALARM, SPY_PATROL_DECK, PATROL_IS_TOP, PATROL_IS_BOTTOM,
    PLACE_CROW_TOKEN, ACCEPT, DECLINE, PLAY_AGAIN_YES, PLAY_AGAIN_NO,
    BUTTON_COUNT, NO_BUTTON, HOME_EXIT
} ;

enum class characterV_t {
    V_JUICER, V_HACKER, V_ACROBAT, V_SPOTTER, V_HAWK, V_RAVEN, V_PETERMAN, V_GUARD
} ;

enum class lootV_t {
    V_TIARA, V_KITTY, V_PAINTING, V_MIRROR, V_KEYCARD, V_ISOTOPE, V_GEMSTONE, V_GOBLET, V_CHIHUAHUA, V_GOLD, V_GOLD2, V_NO_LOOT
} ;

enum class tokenV_t {
    V_ALARMTOKEN, V_OPENTOKEN, V_KITTYTOKEN, V_STEALTHTOKEN, V_CRACKEDTOKEN, V_DOWNSTAIRSTOKEN, V_CROWTOKEN, V_HACKTOKEN, V_TOKEN_COUNT
} ;

enum class roomV_t {
    V_ATRIUM, V_CAMERA, V_CR_FINGERPRINT, V_CR_LASER, V_CR_MOTION, V_DEADBOLT, V_DETECTOR, V_FINGERPRINT, V_FOYER, V_KEYPAD,
    V_LABORATORY, V_LASER, V_LAVATORY, V_MOTION, V_SAFE, V_SECRETDOOR, V_SERVICEDUCT, V_STAIRS, V_THERMO, V_WALKWAY, V_ROOMBACK
} ;

enum class locationV_t {
    A1F1, B1F1, C1F1, D1F1, A2F1, B2F1, C2F1, D2F1, A3F1, B3F1, C3F1, D3F1, A4F1, B4F1, C4F1, D4F1,
    A1F2, B1F2, C1F2, D1F2, A2F2, B2F2, C2F2, D2F2, A3F2, B3F2, C3F2, D3F2, A4F2, B4F2, C4F2, D4F2,
    A1F3, B1F3, C1F3, D1F3, A2F3, B2F3, C2F3, D2F3, A3F3, B3F3, C3F3, D3F3, A4F3, B4F3, C4F3, D4F3,
    NO_LOCATION
} ;

enum class patrolV_t {
    V_A1, V_B1, V_C1, V_D1, V_A2, V_B2, V_C2, V_D2, V_A3, V_B3, V_C3, V_D3, V_A4, V_B4, V_C4, V_D4, V_NO_PATROL
} ;

typedef enum {
    V_YOU, V_PARTNER, V_NO_PLAYER
} playerV_t;

typedef struct {
    characterV_t character;
    unsigned stealthTokens;
    unsigned actionsLeft;
    locationV_t location;
} playerInfo_t;

typedef struct {
    unsigned movements;         //moves por turno del guardia, 6 como maximo
    locationV_t location;
    locationV_t guardDie;       //donde esta el dado (a donde va si no suenan alarmas)/puede ser patrol_t tmb?
    patrolV_t patrolDeck;
} guard_t;

typedef struct {
    playerV_t owner;
    lootV_t loot;
    bool isVisible;
} lootInfo_t;

typedef struct {
    roomV_t iAm;                        //e.g. atrium
    bool tokens[(unsigned) tokenV_t::V_TOKEN_COUNT];
    unsigned combinationNumber;         //0 si es la safe, ó 1,2,3,4,5,6
    unsigned howManyHackTokens;         //solo computers room (3 comp rooms)
    bool goldBarOnTheLoose;             //dónde esta la segunda gold bar q debe ser agarrada por alguno de los ladrones
    unsigned howManyStealthTokens;      //solo para lavatory
} tile_t;

typedef struct {
    unsigned x;
    unsigned y;
    unsigned width;
    unsigned height;
} bitmap_t;

typedef struct {
    bool pass;
    bool move;
    bool peek;
    bool addDice;
    bool rollDice;
    bool hackCR;
    bool useHackToken;
    bool offerLoot;
    bool requestLoot;
    bool pickupLoot;
    bool createAlarm;
    bool spyPatrolDeck;
    bool patrolIsTopBottom;
    bool placeCrowToken;
    bool acceptDecline;
} action_t;

typedef struct {
    playerInfo_t players[V_TOTAL_PLAYERS];
    guard_t guards[V_TOTAL_GUARDS];
    tile_t tiles[V_TOTAL_TILES];
    lootInfo_t loots [V_TOTAL_LOOTS];       //para mostrar los loots de c/piso abajo de los floors
    button_t currentCardSelected;           //muestra en upper-right corner toda la informacion
    unsigned crackingDice[V_TOTAL_CRACKINGDICE];
    action_t actions;
    bool gameWon;                           //solo fijarse por gameWon=true
    bool gameLost;   //solo fijarse por gameLost=true
    std::string message;
} graphicsData_t;

class View {
public:
    graphicsData_t* graphicsData;               //deberia ser public para q model la modifique
    unsigned getButtonX(unsigned);              //se le pasa el indice del arreglo de botones
    unsigned getButtonY(unsigned);
    unsigned getButtonH(unsigned);
    unsigned getButtonW(unsigned);
    View();
    virtual ~View();
    void updateGraphics();
    void* getDisplay();

private:
    ALLEGRO_DISPLAY *display;                   //variables de allegro
    ALLEGRO_BITMAP *background;
    ALLEGRO_EVENT_QUEUE* eventQueue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_FONT *titleFont;
    ALLEGRO_FONT *textFont;
    ALLEGRO_FONT* smallTextFont;
    unsigned int backgroundWidth;
    unsigned int backgroundHeight;
    unsigned int width;
    unsigned int height;
    bitmap_t *buttons;
    unsigned getBitmapX(ALLEGRO_BITMAP*);
    unsigned getBitmapY(ALLEGRO_BITMAP*);
    unsigned getBitmapW(ALLEGRO_BITMAP*);
    unsigned getBitmapH(ALLEGRO_BITMAP*);
    ALLEGRO_BITMAP* loadCharacter(characterV_t, bool);          //funciones que cargan el bitmap
    ALLEGRO_BITMAP* loadLoot(lootV_t, bool);
    ALLEGRO_BITMAP* loadToken(tokenV_t, bool);
    ALLEGRO_BITMAP* loadRoom(roomV_t, bool);
    ALLEGRO_BITMAP* loadPatrolCard(patrolV_t);
    ALLEGRO_BITMAP* loadGuardDie(unsigned);
    ALLEGRO_BITMAP* loadSafeDie(unsigned);
    ALLEGRO_BITMAP* loadSafeNumber(unsigned s, bool shrink);

    void writeTitle();
    void drawChatDividers();
    void drawBoard();
    void drawCharactersInfo();
    void drawFloors();
    void drawTiles();
    void drawWalls();
    void writeFloorTexts();
    void writeCoordinates();
    void drawPatrolDecks();
    void drawLoots();
    void drawCharacters();
    void drawGuardDice();
    void drawGuards();
    void drawTokensOnTiles();
    void drawBackground();
    void drawCardInfo();
    void showNoCardSelected();
    void drawTileSelectedInfo();
    void drawSelectedTileTokens();
    void writeSelectedTileInfo();
    void drawLootSelectedInfo();
    void writeActions();
    void writeMessages();
    void drawHorizontalWall(unsigned floor, unsigned row, unsigned col);        //floor =(1,2,3);row=(1,2,3,4);col=(1,2,3,4)
    void drawVerticalWall(unsigned floor, unsigned row, unsigned col);          //floor =(1,2,3);row=(1,2,3,4);col=(1,2,3,4)
    unsigned getColumn(locationV_t);
    unsigned getRow(locationV_t);
    unsigned getFloor(locationV_t);
    bool isCardSelectedLoot(button_t);
    bool isCardSelectedTile(button_t);
    std::string whichChar(characterV_t);
    void initButton(unsigned i, unsigned x, unsigned y, unsigned w, unsigned h);
    void initUtilities();
} ;

#endif /* VIEW_H */


