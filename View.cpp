#include "View.h"
#include <string>

void drawVerticalWall(unsigned floor, unsigned row, unsigned col);
void drawHorizontalWall(unsigned floor, unsigned row, unsigned col); //floor =(1,2,3);row=(1,2,3,4);col=(1,2,3,4)

#define TILE_SIZE                   71
#define CARD_SELECTED_SIZE          162
#define CHARACTERS_BIG_WIDTH        60
#define CHARACTERS_BIG_HEIGHT       75
#define CHARACTERS_SMALL_WIDTH      33
#define CHARACTERS_SMALL_HEIGHT     49
#define TOKENS_BIG_SIZE             22
#define PATROL_CARD_SIZE            60
#define LOOT_CARD_SIZE              60
#define TOKENS_SMALL_SIZE           17

#define SPACE_LEFT_MARGIN           20
#define SPACE_UP_MARGIN             23
#define SPACE_TILE                  10
#define SPACE_FLOOR                 40
#define SPACE_TOKEN_LR              22.5
#define SPACE_TOKEN_UD              5
#define SPACE_DIVIDER_L             1050
#define SPACE_DIVIDER_U             550

#define FONT_HUGE_SIZE              60
#define FONT_BIG_SIZE               18
#define FONT_MEDIUM_SIZE            14
#define FONT_SMALL_SIZE             12

View::View()
{

    this->display = NULL;       //inicializamos variables de allegro
    this->titleFont = NULL;
    this->textFont = NULL;
    this->smallTextFont = NULL;
    //display->timer = NULL;
    this->background = NULL;
    this->width = DISPLAYW;
    this->height = DISPLAYH;

    if (al_init())
    {
        if (al_init_primitives_addon())
        {
            if (al_init_image_addon())
            {
                al_init_font_addon();
                if (al_init_ttf_addon())
                {
                    this->display = al_create_display(this->width, this->height);
                    if (this->display != NULL)
                    {
                        al_set_window_title(this->display, "Pepe&Co");              //titulo
                        this->background = al_load_bitmap("images/background.jpg"); //imagen de fondo
                        if (this->background != NULL)
                        {
                            this->backgroundWidth = al_get_bitmap_width(this->background);
                            this->backgroundHeight = al_get_bitmap_height(this->background);

                            this->textFont = al_load_ttf_font("fonts/Dudu.ttf", 20, 0);         //tipografias
                            this->smallTextFont = al_load_ttf_font("fonts/Dudu.ttf", 16, 0);
                            if (this->textFont != NULL)
                            {
                                this->timer = al_create_timer(1.0 / 60);
                                if (this->timer != NULL)
                                {
                                    if (al_install_mouse())
                                    {
                                        if (al_install_keyboard())
                                        {
                                            this->eventQueue = al_create_event_queue();
                                            if (this->eventQueue != NULL)
                                            {
                                                al_register_event_source(this->eventQueue, al_get_mouse_event_source());
                                                al_register_event_source(this->eventQueue, al_get_keyboard_event_source());
                                                al_register_event_source(this->eventQueue, al_get_display_event_source(this->display));
                                                this->titleFont = al_load_ttf_font("fonts/Whatnot.ttf", 65, 0);     //tipografia de titulo
                                                if (this->titleFont != NULL)
                                                {
                                                    this->graphicsData = new graphicsData_t;
                                                    this->buttons = new bitmap_t[button_t::BUTTON_COUNT];   //estructura de botones
                                                    al_draw_bitmap(this->background, 0, 0, 0);
                                                    al_start_timer(this->timer);
                                                }
                                                else
                                                {
                                                    al_destroy_bitmap(this->background);
                                                    al_destroy_event_queue(this->eventQueue);
                                                    al_destroy_font(this->textFont);
                                                    al_destroy_font(this->smallTextFont);
                                                    al_destroy_font(this->titleFont);
                                                    al_destroy_timer(this->timer);
                                                    al_destroy_display(this->display);
                                                    al_shutdown_ttf_addon();
                                                    al_shutdown_primitives_addon();
                                                    al_shutdown_image_addon();
                                                    al_shutdown_font_addon();
                                                    al_uninstall_mouse();
                                                    al_uninstall_keyboard();
                                                }
                                            }
                                            else
                                            {
                                                al_destroy_bitmap(this->background);
                                                al_destroy_font(this->textFont);
                                                al_destroy_font(this->smallTextFont);
                                                al_destroy_timer(this->timer);
                                                al_destroy_display(this->display);
                                                al_shutdown_ttf_addon();
                                                al_shutdown_primitives_addon();
                                                al_shutdown_image_addon();
                                                al_shutdown_font_addon();
                                                al_uninstall_mouse();
                                                al_uninstall_keyboard();
                                            }
                                        }
                                        else
                                        {
                                            al_destroy_bitmap(this->background);
                                            al_destroy_font(this->textFont);
                                            al_destroy_font(this->smallTextFont);
                                            al_destroy_timer(this->timer);
                                            al_destroy_display(this->display);
                                            al_uninstall_mouse();
                                            al_shutdown_ttf_addon();
                                            al_shutdown_primitives_addon();
                                            al_shutdown_image_addon();
                                            al_shutdown_font_addon();
                                        }
                                    }
                                    else
                                    {
                                        al_destroy_bitmap(this->background);
                                        al_destroy_font(this->textFont);
                                        al_destroy_font(this->smallTextFont);
                                        al_destroy_timer(this->timer);
                                        al_destroy_display(this->display);
                                        al_shutdown_ttf_addon();
                                        al_shutdown_primitives_addon();
                                        al_shutdown_image_addon();
                                        al_shutdown_font_addon();
                                    }
                                }
                                else
                                {
                                    al_destroy_bitmap(this->background);
                                    al_destroy_font(this->textFont);
                                    al_destroy_font(this->smallTextFont);
                                    al_destroy_display(this->display);
                                    al_shutdown_ttf_addon();
                                    al_shutdown_primitives_addon();
                                    al_shutdown_image_addon();
                                    al_shutdown_font_addon();
                                }
                            }
                            else
                            {
                                al_destroy_bitmap(this->background);
                                al_destroy_display(this->display);
                                al_shutdown_ttf_addon();
                                al_shutdown_primitives_addon();
                                al_shutdown_image_addon();
                                al_shutdown_font_addon();
                            }
                        }
                        else
                        {
                            al_destroy_display(this->display);
                            al_shutdown_ttf_addon();
                            al_shutdown_primitives_addon();
                            al_shutdown_image_addon();
                            al_shutdown_font_addon();
                        }
                    }
                    else
                    {
                        al_shutdown_ttf_addon();
                        al_shutdown_primitives_addon();
                        al_shutdown_image_addon();
                        al_shutdown_font_addon();
                    }
                }
                else
                {
                    al_shutdown_primitives_addon();
                    al_shutdown_image_addon();
                    al_shutdown_font_addon();
                }
            }
            else
            {
                al_shutdown_primitives_addon();
                al_shutdown_image_addon();
            }
        }
        else
        {
            al_shutdown_primitives_addon();
        }
    }
    initUtilities();        //inicializamos botones

}

View::~View()
{
    al_destroy_bitmap(this->background);
    al_destroy_event_queue(this->eventQueue);
    al_destroy_font(this->textFont);
    al_destroy_font(this->smallTextFont);
    al_destroy_font(this->titleFont);
    al_destroy_timer(this->timer);
    al_destroy_display(this->display);
    al_shutdown_ttf_addon();
    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_shutdown_font_addon();
    al_uninstall_mouse();
    al_uninstall_keyboard();

    delete this->graphicsData;
    delete this->buttons;

}

void
View::updateGraphics()
{
    if (graphicsData->gameLost)
        drawForfeit();
    else if (graphicsData->gameWon)
        drawVictory();
    else
        drawGame();

    al_flip_display();

}

void View::drawGame()
{
    drawBackground();       //"Pepe & Co. HQ" y el fondo
    writeTitle();
    drawChatDividers();     //dibuja las lineas que separan el chat del tablero
    drawBoard();            //dibuja todo el tablero
    drawCardInfo();         //dibuja descripcion detallada de la carta seleccionada asi como sus tokens

    writeActions();         //dibujo botones de acciones
    writeMessages();        //mensajes del chat
}

void View::drawForfeit()
{
    drawBackground();       //"Pepe & Co. HQ" y el fondo
    ALLEGRO_BITMAP* sadPepe = al_load_bitmap("images/sadpepe.png");
    al_draw_bitmap(sadPepe, 0,  DISPLAYH - al_get_bitmap_height(sadPepe), 0);
    ALLEGRO_BITMAP* bubble = al_load_bitmap("images/bubble.png");
    al_draw_bitmap(bubble, 325, DISPLAYH - al_get_bitmap_height(sadPepe) - al_get_bitmap_height(bubble) - 10, 0);

    al_draw_text(textFont, al_map_rgb(0, 0, 0), 330 + al_get_bitmap_width(bubble) / 2 , DISPLAYH - al_get_bitmap_height(sadPepe) - al_get_bitmap_height(bubble) / 2 - 35, ALLEGRO_ALIGN_CENTRE, "Did we lose the game?");
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 330 + al_get_bitmap_width(bubble) / 2 , DISPLAYH - al_get_bitmap_height(sadPepe) - al_get_bitmap_height(bubble) / 2 - 15, ALLEGRO_ALIGN_CENTRE, "... or did we lose ourselves?");
    al_destroy_bitmap(bubble);
    al_destroy_bitmap(sadPepe);
    writeCredits();
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *18, ALLEGRO_ALIGN_RIGHT, "ACTIONS");
    writePlayAgainActions();
}

void View::drawVictory()
{
    drawBackground();       //"Pepe & Co. HQ" y el fondo
    ALLEGRO_BITMAP* happyPepe = al_load_bitmap("images/pepe4thewin.png");
    al_draw_bitmap(happyPepe, 0, DISPLAYH - al_get_bitmap_height(happyPepe), 0);
    ALLEGRO_BITMAP* bubble = al_load_bitmap("images/bubble.png");
    al_draw_bitmap(bubble, 325, DISPLAYH - al_get_bitmap_height(happyPepe) - al_get_bitmap_height(bubble) / 2, 0);

    al_draw_text(textFont, al_map_rgb(0, 0, 0), 337 + al_get_bitmap_width(bubble) / 2 , DISPLAYH - al_get_bitmap_height(happyPepe) + al_get_bitmap_height(bubble) / 2 - 110, ALLEGRO_ALIGN_CENTRE, "It's finally over!");
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 335 + al_get_bitmap_width(bubble) / 2 , DISPLAYH - al_get_bitmap_height(happyPepe) + al_get_bitmap_height(bubble) / 2 - 90, ALLEGRO_ALIGN_CENTRE, "The evil has been defeated!");
    //al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), 330 + al_get_bitmap_width(bubble) / 2 , DISPLAYH - al_get_bitmap_height(happyPepe) + al_get_bitmap_height(bubble) / 2 - 55, ALLEGRO_ALIGN_CENTRE, "... or has it?");
    al_destroy_bitmap(bubble);
    al_destroy_bitmap(happyPepe);
    writeCredits();
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *18, ALLEGRO_ALIGN_RIGHT, "ACTIONS");
    writePlayAgainActions();
}

void View::writeCredits()
{
    unsigned x = 900;
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 10, ALLEGRO_ALIGN_CENTRE, "CREDITS");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 90, ALLEGRO_ALIGN_CENTRE, "In Memory of Bauti");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 115, ALLEGRO_ALIGN_CENTRE, "(he's not dead, we just miss him)");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 100, ALLEGRO_ALIGN_CENTRE, "This game was created by LuciferTheLightOfOurLives&Co.");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 100 + 30, ALLEGRO_ALIGN_CENTRE, "All rights reserved.");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 70 + 100, ALLEGRO_ALIGN_CENTRE, "We'd like to thank our friends and family, and Pepe, always en el cora.");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 100 + 100, ALLEGRO_ALIGN_CENTRE, "We can't stress this enough. Pepe always en el cora.");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 130 + 100, ALLEGRO_ALIGN_CENTRE, "We mean it Pepe, if you are out there somewhere. En el cora.");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 180 + 100, ALLEGRO_ALIGN_CENTRE, "The members of this amazing crew are:");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 210 + 100, ALLEGRO_ALIGN_CENTRE, "Benjamín Carlos Lin");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 235 + 100, ALLEGRO_ALIGN_CENTRE, "Roberto Santiago Chá");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 260 + 100, ALLEGRO_ALIGN_CENTRE, "Ignacio Grayeb");
    al_draw_text(this->textFont, al_map_rgb(0, 157, 79), x, 100 + 285 + 100, ALLEGRO_ALIGN_CENTRE, "Lucero Guadalupe Fernandez");
}

void
View::drawBoard()
{

    drawCharactersInfo();       //informacion que se muestra arriba de los personajes, como sus vidas
    drawFloors();               //tablero
}

void
View::drawFloors()
{

    drawTiles();                //dibuja las cartas
    drawWalls();                //dibuja paredes

    writeFloorTexts();          //"Floor 1", etc
    writeCoordinates();         //"A, B, C, D" / "1, 2, 3, 4"
    drawPatrolDecks();          //dibuja el mazo del guardia en cada piso
    drawLoots();                //el loot de la safe de cada piso

    drawCharacters();           //dibuja los characters en el tablero
    drawGuardDice();            //el dado del guardia
    drawGuards();               //dibuja a los guardias en cada piso
    drawTokensOnTiles();
}

void
View::drawCardInfo()
{
    if (isCardSelectedLoot(graphicsData->currentCardSelected))          //si fue un loot lo que se selecciono, muestra su info
        drawLootSelectedInfo();
    else if (isCardSelectedTile(graphicsData->currentCardSelected))     //Si se selecciono un room
    {
        if (graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm != roomV_t::V_ROOMBACK)
        {
            drawTileSelectedInfo();                                         //dibuja la carta
            writeSelectedTileInfo();                                        //qué carta es, su ubicacion
            drawSelectedTileTokens();                                       //los tokens que tiene
        }
        else if (graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm == roomV_t::V_ROOMBACK)
        {
            drawTileSelectedInfo();                                         //dibuja la carta
            writeSelectedTileInfo();                                        //qué carta es, su ubicacion
        }
    }
    else
        showNoCardSelected();                                           //muestra que no se selecciono ningun loot/room
}

bool
View::isCardSelectedLoot(button_t button)           //chequea que se haya tocado un loot
{
    bool isLoot = false;
    if (button == button_t::LOOTF1 || button == button_t::LOOTF2 || button == button_t::LOOTF3)
        isLoot = true;

    return isLoot;
}

bool
View::isCardSelectedTile(button_t button)           //chequea que se haya tocado un room
{
    bool isTile = false;
    if ((int) button <= (int) button_t::D4F3)
        isTile = true;

    return isTile;
}

void
View::drawBackground()                              //dibujo fondo
{
    al_draw_bitmap(this->background, 0, 0, 0);
}

void
View::writeTitle()                          //escribo el titulo
{
    al_draw_text(titleFont, al_map_rgb(0, 0, 0), 530, 0, ALLEGRO_ALIGN_CENTER, "Pepe&Co. HQ");
}

void
View::drawChatDividers()                    //lineas que dividen el tablero del chat y la barra lateral
{
    al_draw_line(1050, 0, 1050, 550, al_map_rgb(0, 0, 0), 1);
    al_draw_line(0, 550, 1050, 550, al_map_rgb(0, 0, 0), 1);
}

void
View::drawCharactersInfo()
{
    for (unsigned player = 0; player < V_TOTAL_PLAYERS; player++)
    {
        ALLEGRO_BITMAP * playerBitmap = loadCharacter(graphicsData->players[player].character, false);                       //cargo imagen en grande
        al_draw_bitmap(playerBitmap, 25 + TILE_SIZE + SPACE_TILE + player * 790, 95 - (al_get_bitmap_height(playerBitmap)), 0);    //la dibujo y destruyo el bitmap
        if (graphicsData->players[player].currentChar == true)     //esta jugando este
            al_draw_rectangle(25 + TILE_SIZE + SPACE_TILE + player * 790, 95 - (al_get_bitmap_height(playerBitmap)), 25 + TILE_SIZE + SPACE_TILE + player * 790 + al_get_bitmap_width(playerBitmap), 95 , al_map_rgb(0, 157, 79), 2);
        al_destroy_bitmap(playerBitmap);

        ALLEGRO_BITMAP * stealthBitmap = loadToken(tokenV_t::V_STEALTHTOKEN, false);            //dibujo la cantidad de stealth tokens que tiene el character
        for (unsigned i = 0; i < graphicsData->players[player].stealthTokens; ++i)
            al_draw_bitmap(stealthBitmap, 85 + TILE_SIZE + SPACE_TILE + player * 700, i * (5 + TOKENS_BIG_SIZE) + 5, 0);
        al_destroy_bitmap(stealthBitmap);

        al_draw_textf(smallTextFont, al_map_rgb(0, 0, 0), 180 + 70 + player * 560, 43, ALLEGRO_ALIGN_CENTER, "actions x%d", graphicsData->players[player].actionsLeft);         //la cantidad de actions que le quedan
        std::string character = whichChar(graphicsData->players[player].character);
        if (player == 0)
            al_draw_textf(smallTextFont, al_map_rgb(0, 0, 0), 55 + 1 * (TILE_SIZE + SPACE_TILE), 95, ALLEGRO_ALIGN_CENTER, "you - %s", character.c_str());   //"You" si es P1

        else
            al_draw_textf(smallTextFont, al_map_rgb(0, 0, 0), 300 + 625, 95, ALLEGRO_ALIGN_CENTER, "partner - %s", character.c_str());
    }
}

void
View::drawTiles()

{
    unsigned i = 0, x, y;
    for (unsigned floor = 0; floor < 3; floor++)
        for (unsigned rows = 0; rows < 4; rows++/*, i++*/)
        {
            for (unsigned cols = 0; cols < 4; cols++, i++)
            {
                x = 20 + cols * (TILE_SIZE + SPACE_TILE) + floor * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3);
                y = 135 + rows * (TILE_SIZE + SPACE_TILE);

                if (graphicsData->tiles[i].iAm == roomV_t::V_ROOMBACK)
                {
                    ALLEGRO_BITMAP* tile = loadRoom(roomV_t::V_ROOMBACK, true);        //cargo la iamgen de la carta dada vuelta en tamaño chico, dibujo y destruyo el bitmap
                    al_draw_bitmap(tile, x, y, 0);
                    al_destroy_bitmap(tile);
                }
                else
                {
                    ALLEGRO_BITMAP* tile = loadRoom(graphicsData->tiles[i].iAm, true);  //cargo las cards y las dibujo
                    al_draw_bitmap(tile, x, y, 0);
                    al_destroy_bitmap(tile);
                    if (graphicsData->tiles[i].iAm != roomV_t::V_SAFE)                  //si no es la caja fuerte coloco el safe number
                    {

                        ALLEGRO_BITMAP* number = loadSafeNumber(graphicsData->tiles[i].combinationNumber, true);
                        if (number != NULL)
                        {

                            al_draw_bitmap(number, x, y, 0);
                            al_destroy_bitmap(number);
                        }
                    }
                }
            }
        }
}

void
View::drawWalls()
{
    drawVerticalWall(1, 1, 1);          //dibujo las paredes
    drawVerticalWall(1, 4, 1);
    drawVerticalWall(1, 2, 3);
    drawVerticalWall(1, 4, 2);
    drawVerticalWall(2, 1, 1);
    drawVerticalWall(2, 1, 2);
    drawVerticalWall(2, 1, 3);
    drawVerticalWall(2, 4, 1);
    drawVerticalWall(2, 4, 2);
    drawVerticalWall(2, 4, 3);
    drawVerticalWall(3, 2, 1);
    drawVerticalWall(3, 2, 3);
    drawVerticalWall(3, 3, 1);
    drawVerticalWall(3, 3, 2);
    drawVerticalWall(3, 4, 3);

    drawHorizontalWall(1, 2, 1);
    drawHorizontalWall(1, 2, 2);
    drawHorizontalWall(1, 1, 3);
    drawHorizontalWall(1, 3, 4);
    drawHorizontalWall(2, 2, 2);
    drawHorizontalWall(2, 2, 3);
    drawHorizontalWall(3, 1, 3);
    drawHorizontalWall(3, 2, 3);
    drawHorizontalWall(3, 2, 1);
}

void
View::drawVerticalWall(unsigned floor, unsigned row, unsigned col) //floor =(1,2,3);row=(1,2,3,4);col=(1,2,3,4)
{
    unsigned x1, y1, x2, y2;
    x1 = 20 + TILE_SIZE * col + SPACE_TILE * (col - 1) + (floor - 1) * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3) + 0.5;
    y1 = 135 + TILE_SIZE * (row - 1) + SPACE_TILE * (row - 1) + 8;
    x2 = 20 + TILE_SIZE * col + SPACE_TILE * col + (floor - 1) * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3) - 0.5;
    y2 = 135 + TILE_SIZE * row + SPACE_TILE * (row - 1) - 8;
    al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 3, 3, al_map_rgb(169, 127, 77));
}

void
View::drawHorizontalWall(unsigned floor, unsigned row, unsigned col) //floor =(1,2,3);row=(1,2,3,4);col=(1,2,3,4)
{
    unsigned x1, y1, x2, y2;
    x1 = 20 + TILE_SIZE * (col - 1) + SPACE_TILE * (col - 1) +(floor - 1) * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3) + 8;
    y1 = 135 + TILE_SIZE * row + SPACE_TILE * (row - 1) + 0.5;
    x2 = 20 + TILE_SIZE * col + SPACE_TILE * (col - 1) +(floor - 1) * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3) - 8;
    y2 = 135 + TILE_SIZE * row + SPACE_TILE * row - 0.5;
    al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 3, 3, al_map_rgb(169, 127, 77));
}

void
View::writeFloorTexts()     //"Floor 1", etc
{
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 20 + TILE_SIZE * 2 + SPACE_TILE + SPACE_TILE / 2, 135 + TILE_SIZE * 4 + SPACE_TILE * 3 + SPACE_TILE / 4, ALLEGRO_ALIGN_CENTER, "1st Floor");
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 20 + SPACE_FLOOR + TILE_SIZE * 6 + SPACE_TILE * 4 + SPACE_TILE / 2, 135 + TILE_SIZE * 4 + SPACE_TILE * 3 + SPACE_TILE / 4, ALLEGRO_ALIGN_CENTER, "2nd Floor");
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 20 + SPACE_FLOOR * 2 + TILE_SIZE * 10 + SPACE_TILE * 7 + SPACE_TILE / 2, 135 + TILE_SIZE * 4 + SPACE_TILE * 3 + SPACE_TILE / 4, ALLEGRO_ALIGN_CENTER, "3rd Floor");
}

void
View::writeCoordinates()        //"A, B, C, D" / "1, 2, 3, 4"
{
    unsigned x, y;
    x = 20 + TILE_SIZE / 2;
    y = 135 - 16;
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), x, y, ALLEGRO_ALIGN_CENTER, "A");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), x + 1 * (TILE_SIZE + SPACE_TILE), y, ALLEGRO_ALIGN_CENTER, "B");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), x + 2 * (TILE_SIZE + SPACE_TILE), y, ALLEGRO_ALIGN_CENTER, "C");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), x + 3 * (TILE_SIZE + SPACE_TILE), y, ALLEGRO_ALIGN_CENTER, "D");

    x = 20 - 7.5;
    y = 135 + TILE_SIZE / 2.5;
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), x, y, ALLEGRO_ALIGN_CENTER, "1");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), x, y + 1 * (TILE_SIZE + SPACE_TILE), ALLEGRO_ALIGN_CENTER, "2");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), x, y + 2 * (TILE_SIZE + SPACE_TILE), ALLEGRO_ALIGN_CENTER, "3");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), x, y + 3 * (TILE_SIZE + SPACE_TILE), ALLEGRO_ALIGN_CENTER, "4");
}

void
View::drawPatrolDecks()     //dibuja los mazos del guardia en cada piso
{
    for (unsigned i = 0; i < V_TOTAL_GUARDS; i++)
    {
        ALLEGRO_BITMAP* bitmap = loadPatrolCard(graphicsData->guards[i].patrolDeck);
        al_draw_bitmap(bitmap, 20 + 1 * (TILE_SIZE + SPACE_TILE) + SPACE_FLOOR * i + i * (TILE_SIZE * 4 + SPACE_TILE * 3), 135 + TILE_SIZE * 4 + SPACE_TILE * 6, 0);
        al_destroy_bitmap(bitmap);
    }
}

void
View::drawLoots()           //dibujo el loot de cada piso
{
    unsigned x, y;
    for (unsigned i = 0; i < V_TOTAL_LOOTS; i++)
    {
        x = 20 + 2 * (TILE_SIZE + SPACE_TILE) + SPACE_FLOOR * i + i * (TILE_SIZE * 4 + SPACE_TILE * 3);
        y = 135 + TILE_SIZE * 4 + SPACE_TILE * 6;
        ALLEGRO_BITMAP * bitmap = loadLoot(graphicsData->loots[i].loot, true);
        al_draw_bitmap(bitmap, x, y, 0);
        al_destroy_bitmap(bitmap);
    }
}

void
View::drawCharacters()          //coloco los characters en el tablero
{
    unsigned col, row, floor, x, y;
    for (unsigned i = 0; i < V_TOTAL_PLAYERS; i++)
    {

        ALLEGRO_BITMAP* player = loadCharacter(graphicsData->players[i].character, true);
        col = getColumn(graphicsData->players[i].location);
        row = getRow(graphicsData->players[i].location);
        floor = getFloor(graphicsData->players[i].location);
        x = 20 + (col) * (TILE_SIZE + SPACE_TILE) + (floor) * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3) - 10;
        y = 135 + (row) * (TILE_SIZE + SPACE_TILE)+(TILE_SIZE - al_get_bitmap_height(player));
        al_draw_bitmap(player, x + i * 2, y, 0);
        al_destroy_bitmap(player);
    }
}

unsigned
View::getColumn(locationV_t location)
{
    unsigned floor = getFloor(location);
    unsigned index = (int) location - (floor) * V_ROWS*V_COLUMNS;

    return index % V_COLUMNS;
}

unsigned
View::getRow(locationV_t location)
{
    unsigned floor = getFloor(location);
    unsigned index = (int) location - (floor) * V_ROWS*V_COLUMNS;

    return (int) (index / V_COLUMNS);
}

unsigned
View::getFloor(locationV_t location)
{
    return ((int) location) / (V_ROWS * V_COLUMNS);
}

void
View::drawGuardDice()           //dibujo el dado del guardia
{
    unsigned col, row, floor, x, y;
    for (unsigned i = 0; i < V_TOTAL_GUARDS; i++)
    {
        if (graphicsData->guards[i].location == locationV_t::NO_LOCATION)

            continue;
        ALLEGRO_BITMAP * die = loadGuardDie(graphicsData->guards[i].movements);
        col = getColumn(graphicsData->guards[i].guardDie);
        row = getRow(graphicsData->guards[i].guardDie);
        floor = getFloor(graphicsData->guards[i].guardDie);
        x = 20 + col * (TILE_SIZE + SPACE_TILE) + floor * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3) + TILE_SIZE / 2 - al_get_bitmap_width(die) / 2;
        y = 135 + row * (TILE_SIZE + SPACE_TILE) + TILE_SIZE - TILE_SIZE / 2 - al_get_bitmap_width(die) / 2;
        al_draw_bitmap(die, x, y, 0);
        al_destroy_bitmap(die);
    }
}

void
View::drawGuards()          //dibujo los guardias en el tablero
{
    unsigned col, row, floor, x, y;
    for (unsigned i = 0; i < V_TOTAL_GUARDS; i++)
    {
        if (graphicsData->guards[i].location == locationV_t::NO_LOCATION)

            continue;
        ALLEGRO_BITMAP * guard = loadCharacter(characterV_t::V_GUARD, false);
        col = getColumn(graphicsData->guards[i].location);
        row = getRow(graphicsData->guards[i].location);
        floor = getFloor(graphicsData->guards[i].location);
        x = 20 + col * (TILE_SIZE + SPACE_TILE) + floor * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3) + TILE_SIZE / 2 - al_get_bitmap_width(guard) / 2;
        y = 135 + row * (TILE_SIZE + SPACE_TILE) + TILE_SIZE - TILE_SIZE / 2 - al_get_bitmap_width(guard) / 2;
        al_draw_bitmap(guard, x, y, 0);
        al_destroy_bitmap(guard);
    }
}

void
View::drawTokensOnTiles()
{
    //ver bien

    unsigned col, row, floor, x, y;
    for (unsigned i = 0; i < V_TOTAL_TILES; i++)
    {
        if (graphicsData->tiles[i].goldBarOnTheLoose == true)
        {
            ALLEGRO_BITMAP* extraGold = loadLoot(lootV_t::V_GOLD2, false);
            floor = i / (V_ROWS * V_COLUMNS);
            col = (i - floor * V_ROWS * V_COLUMNS) % V_COLUMNS;
            row = (i - floor * V_ROWS * V_COLUMNS) / V_COLUMNS;
            x = 20 + (col) * (TILE_SIZE + SPACE_TILE) + (floor) * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3) + TILE_SIZE - al_get_bitmap_height(extraGold);
            y = 140 + (row) * (TILE_SIZE + SPACE_TILE)+(TILE_SIZE - al_get_bitmap_height(extraGold));
            al_draw_bitmap(extraGold, x, y, 0);
            al_destroy_bitmap(extraGold);
        }

        else
            continue;
    }
}

void
View::drawTileSelectedInfo()
{
    unsigned index = (int) graphicsData->currentCardSelected;

    ALLEGRO_BITMAP* tile = loadRoom(graphicsData->tiles[index].iAm, false);         //dibujo la carta seleccionada en tamaño grande
    al_draw_bitmap(tile, (DISPLAYW - SPACE_DIVIDER_L - CARD_SELECTED_SIZE) / 2 + SPACE_DIVIDER_L, SPACE_UP_MARGIN, 0);

    al_destroy_bitmap(tile);
    if ((graphicsData->tiles[index].iAm != roomV_t::V_SAFE) && (graphicsData->tiles[index].iAm != roomV_t::V_ROOMBACK))
    {

        ALLEGRO_BITMAP* number = loadSafeNumber(graphicsData->tiles[index].combinationNumber, true);        //su combination number (salteo si es la safe)
        al_draw_bitmap(number, (DISPLAYW - SPACE_DIVIDER_L - CARD_SELECTED_SIZE)*2 + SPACE_DIVIDER_L - 17, SPACE_UP_MARGIN + CARD_SELECTED_SIZE / 2 + 3, 0);
        al_destroy_bitmap(number);
    }
}

void
View::writeSelectedTileInfo()
{
    std::string c, r, f, tile;
    unsigned col, row, floor;
    col = getColumn((locationV_t) graphicsData->currentCardSelected);
    row = getRow((locationV_t) graphicsData->currentCardSelected);
    floor = getFloor((locationV_t) graphicsData->currentCardSelected);
    switch (col)
    {
        case 0: c = "A";                //escribo la ubicacion en el tablero de la Tile seleccionada
            break;
        case 1: c = "B";
            break;
        case 2: c = "C";
            break;
        case 3: c = "D";
            break;
    }
    switch (row)
    {
        case 0: r = "1";
            break;
        case 1: r = "2";
            break;
        case 2: r = "3";
            break;
        case 3: r = "4";
            break;
    }
    switch (floor)
    {
        case 0: f = "F1";
            break;
        case 1: f = "F2";
            break;
        case 2: f = "F3";
            break;
    }
    tile = c + r + f;
    al_draw_textf(textFont, al_map_rgb(0, 0, 0), (DISPLAYW - SPACE_DIVIDER_L) / 2 + SPACE_DIVIDER_L, 3, ALLEGRO_ALIGN_CENTER, "Tile: %s", tile.c_str());
}

void
View::showNoCardSelected() //si no se seleccionó ninguna carta... (cambiar)
{
    al_draw_text(textFont, al_map_rgb(0, 0, 0), (DISPLAYW - SPACE_DIVIDER_L) / 2 + SPACE_DIVIDER_L, 0, ALLEGRO_ALIGN_CENTER, "No Card or Loot Selected");
}

void
View::drawSelectedTileTokens()          //dibujo los tokens que tiene la carta y su cantidad
{
    unsigned tokenCount = 0, x, y;
    for (unsigned j = 0; j < 2; j++)
    {
        for (unsigned i = 0; i < 4; i++)
        {
            x = i * (TOKENS_BIG_SIZE + SPACE_TOKEN_LR) + SPACE_DIVIDER_L + SPACE_TOKEN_LR;
            y = j * (TOKENS_BIG_SIZE + SPACE_TOKEN_UD) + SPACE_UP_MARGIN + CARD_SELECTED_SIZE + SPACE_TOKEN_UD;
            if (graphicsData->tiles[(int) graphicsData->currentCardSelected].tokens[tokenCount])
            {
                if (tokenCount == (int) tokenV_t::V_HACKTOKEN || tokenCount == (int) tokenV_t::V_STEALTHTOKEN)      //dibujo abajo
                {
                    tokenCount++;
                    continue;
                }
                ALLEGRO_BITMAP* token = loadToken((tokenV_t) tokenCount, false);
                al_draw_bitmap(token, x, y, 0);
                al_destroy_bitmap(token);
            }
            tokenCount++;
        }

    }

    if (graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm == roomV_t::V_LAVATORY)    //si es el lavatory coloco la cantidad de stealth tokens q tiene
    {
        x = 3 * (TOKENS_BIG_SIZE + SPACE_TOKEN_LR) + SPACE_DIVIDER_L + SPACE_TOKEN_LR;
        y = SPACE_UP_MARGIN + CARD_SELECTED_SIZE + SPACE_TOKEN_UD;
        ALLEGRO_BITMAP* token = loadToken(tokenV_t::V_STEALTHTOKEN, false);
        al_draw_bitmap(token, x, y, 0);
        al_destroy_bitmap(token);
        al_draw_textf(textFont, al_map_rgb(0, 0, 0), x + TOKENS_BIG_SIZE + 5, y, ALLEGRO_ALIGN_LEFT, "x%d", graphicsData->tiles[(int) graphicsData->currentCardSelected].howManyStealthTokens);
    }

    if (graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm == roomV_t::V_CR_FINGERPRINT           //si es computerRoom, dibujo la cantidad de hack tokens que tiene
            || graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm == roomV_t::V_CR_LASER
            || graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm == roomV_t::V_CR_MOTION)
    {

        x = 3 * (TOKENS_BIG_SIZE + SPACE_TOKEN_LR) + SPACE_DIVIDER_L + SPACE_TOKEN_LR;
        y = 1 * (TOKENS_BIG_SIZE + SPACE_TOKEN_UD) + SPACE_UP_MARGIN + CARD_SELECTED_SIZE + SPACE_TOKEN_UD;
        ALLEGRO_BITMAP* token = loadToken(tokenV_t::V_HACKTOKEN, false);
        al_draw_bitmap(token, x, y, 0);
        al_destroy_bitmap(token);
        al_draw_textf(textFont, al_map_rgb(0, 0, 0), x + TOKENS_BIG_SIZE + 5, y, ALLEGRO_ALIGN_LEFT, "x%d", graphicsData->tiles[(int) graphicsData->currentCardSelected].howManyHackTokens);
    }
}

void
View::drawLootSelectedInfo()            //dibujo el loot seleccionado
{
    ALLEGRO_BITMAP* loot = NULL;
    if (graphicsData->currentCardSelected == button_t::LOOTF1)
    {
        loot = loadLoot(graphicsData->loots[0].loot, false);
        al_draw_text(textFont, al_map_rgb(0, 0, 0), (DISPLAYW - SPACE_DIVIDER_L) / 2 + SPACE_DIVIDER_L, 0, ALLEGRO_ALIGN_CENTER, "1st Floor Loot");
    }
    else if (graphicsData->currentCardSelected == button_t::LOOTF2)
    {
        loot = loadLoot(graphicsData->loots[1].loot, false);
        al_draw_text(textFont, al_map_rgb(0, 0, 0), (DISPLAYW - SPACE_DIVIDER_L) / 2 + SPACE_DIVIDER_L, 0, ALLEGRO_ALIGN_CENTER, "2nd Floor Loot");
    }
    else
    {
        loot = loadLoot(graphicsData->loots[2].loot, false);
        al_draw_text(textFont, al_map_rgb(0, 0, 0), (DISPLAYW - SPACE_DIVIDER_L) / 2 + SPACE_DIVIDER_L, 0, ALLEGRO_ALIGN_CENTER, "3rd Floor Loot");
    }
    al_draw_bitmap(loot, (DISPLAYW - SPACE_DIVIDER_L - CARD_SELECTED_SIZE) / 2 + SPACE_DIVIDER_L, SPACE_UP_MARGIN, 0);
    al_destroy_bitmap(loot);
}

void
View::writeActions()        //escribo las actions en negro o mas claras dependiendo de si estan habilitadas o no
{
    float alpha = 0.5f;
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 10 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 3, ALLEGRO_ALIGN_RIGHT, "ACTIONS");

    //move
    if (graphicsData->actions.move == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), SPACE_DIVIDER_L + 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, ALLEGRO_ALIGN_LEFT, "*Move");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), SPACE_DIVIDER_L + 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, ALLEGRO_ALIGN_LEFT, "*Move");

    //peek
    if (graphicsData->actions.peek == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), SPACE_DIVIDER_L + (DISPLAYW - SPACE_DIVIDER_L) / 2, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, ALLEGRO_ALIGN_CENTER, "*Peek");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), SPACE_DIVIDER_L + (DISPLAYW - SPACE_DIVIDER_L) / 2, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, ALLEGRO_ALIGN_CENTER, "*Peek");

    //pass
    if (graphicsData->actions.pass == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, ALLEGRO_ALIGN_RIGHT, "*Pass");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, ALLEGRO_ALIGN_RIGHT, "*Pass");

    //add dice to safe
    if (graphicsData->actions.addDice == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *5, ALLEGRO_ALIGN_RIGHT, "*Add dice to safe");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *5, ALLEGRO_ALIGN_RIGHT, "*Add dice to safe");

    //roll dice to safe
    if (graphicsData->actions.rollDice == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *6, ALLEGRO_ALIGN_RIGHT, "*Roll dice to safe");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *6, ALLEGRO_ALIGN_RIGHT, "*Roll dice to safe");

    //hack computer room
    if (graphicsData->actions.hackCR == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *8, ALLEGRO_ALIGN_RIGHT, "*Hack computer");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *8, ALLEGRO_ALIGN_RIGHT, "*Hack computer");

    //use hack token
    if (graphicsData->actions.useHackToken == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *9, ALLEGRO_ALIGN_RIGHT, "*Use hack token");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *9, ALLEGRO_ALIGN_RIGHT, "*Use hack token");

    //offer loot
    if (graphicsData->actions.offerLoot == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *10, ALLEGRO_ALIGN_RIGHT, "*Offer loot");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *10, ALLEGRO_ALIGN_RIGHT, "*Offer loot");

    //request loot
    if (graphicsData->actions.requestLoot == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *11, ALLEGRO_ALIGN_RIGHT, "*Request loot");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *11, ALLEGRO_ALIGN_RIGHT, "*Request loot");

    //pick up loot
    if (graphicsData->actions.pickupLoot == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *12, ALLEGRO_ALIGN_RIGHT, "*Pick up loot");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *12, ALLEGRO_ALIGN_RIGHT, "*Pick up loot");

    //create alarm
    if (graphicsData->actions.createAlarm == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *13, ALLEGRO_ALIGN_RIGHT, "*Create Alarm");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *13, ALLEGRO_ALIGN_RIGHT, "*Create Alarm");

    //spy patrol deck
    if (graphicsData->actions.spyPatrolDeck == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *14, ALLEGRO_ALIGN_RIGHT, "*Spy patrol deck");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *14, ALLEGRO_ALIGN_RIGHT, "*Spy patrol deck");

    //patrol top/bottom
    if (graphicsData->actions.patrolIsTopBottom == true)
    {
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *15, ALLEGRO_ALIGN_RIGHT, "*Place patrol card on top");
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *16, ALLEGRO_ALIGN_RIGHT, "*Place patrol card on bottom");
    }
    else
    {
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *15, ALLEGRO_ALIGN_RIGHT, "*Place patrol card on top");
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *16, ALLEGRO_ALIGN_RIGHT, "*Place patrol card on bottom");
    }

    //place crow token
    if (graphicsData->actions.placeCrowToken == true)
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *17, ALLEGRO_ALIGN_RIGHT, "*Place crow token");
    else
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *17, ALLEGRO_ALIGN_RIGHT, "*Place crow token");

    //accept/decline
    if (graphicsData->actions.acceptDecline == true)
    {
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 18, ALLEGRO_ALIGN_LEFT, "Accept");
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 18, ALLEGRO_ALIGN_RIGHT, "Decline");
    }
    else
    {
        al_draw_text(smallTextFont,  al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 18, ALLEGRO_ALIGN_LEFT, "Accept");
        al_draw_text(smallTextFont,  al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 18, ALLEGRO_ALIGN_RIGHT, "Decline");
    }

    writePlayAgainActions();
}

void View::writePlayAgainActions()
{
    //play again
    float alpha = 0.5f;
    if (graphicsData->gameLost == true || graphicsData->gameWon == true)
    {
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 19, ALLEGRO_ALIGN_LEFT, "Play again?");
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0),  SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 20, ALLEGRO_ALIGN_LEFT, "*Yes");
        al_draw_text(smallTextFont, al_map_rgb(0, 0, 0),  DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 20, ALLEGRO_ALIGN_RIGHT, "*No");
    }
    //    else
    //    {
    //        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 19, ALLEGRO_ALIGN_LEFT, "Play again?");
    //        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha),  SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 20, ALLEGRO_ALIGN_LEFT, "*Yes");
    //        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha),  DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 20, ALLEGRO_ALIGN_RIGHT, "*No");
    //    }
}

void
View::initUtilities()           //cargo el x,y, width y height de cada boton
{
    //tiles
    unsigned i = 0, x, y, height = 15;
    for (unsigned floor = 0; floor < 3; floor++)
        for (unsigned rows = 0; rows < 4; rows++, i++)
        {
            for (unsigned cols = 0; cols < 4; cols++, i++)
            {
                x = 20 + cols * (TILE_SIZE + SPACE_TILE) + floor * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3);
                y = 135 + rows * (TILE_SIZE + SPACE_TILE);
                initButton(i, x, y, TILE_SIZE, TILE_SIZE);
            }
            i--;
        }
    //loots
    for (unsigned i = 0; i < V_TOTAL_LOOTS; i++)
    {
        x = 20 + 2 * (TILE_SIZE + SPACE_TILE) + SPACE_FLOOR * i + i * (TILE_SIZE * 4 + SPACE_TILE * 3);
        y = 135 + TILE_SIZE * 4 + SPACE_TILE * 6;
        initButton(V_TOTAL_TILES + i, x, y, LOOT_CARD_SIZE, LOOT_CARD_SIZE);
    }

    //patrol decks

    for (unsigned i = 0; i < V_TOTAL_FLOORS; i++)
        initButton(V_TOTAL_TILES + V_TOTAL_LOOTS + i, 20 + 1 * (TILE_SIZE + SPACE_TILE) + SPACE_FLOOR * i + i * (TILE_SIZE * 4 + SPACE_TILE * 3), 135 + TILE_SIZE * 4 + SPACE_TILE * 6, PATROL_CARD_SIZE, PATROL_CARD_SIZE);

    //actions
    initButton((int) button_t::MOVE, SPACE_DIVIDER_L + 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, 50, height);
    initButton((int) button_t::PEEK, SPACE_DIVIDER_L + (DISPLAYW - SPACE_DIVIDER_L) / 2 - 20, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, 50, height);
    initButton((int) button_t::PASS, DISPLAYW - 50, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, 50, height);
    initButton((int) button_t::ADD_DICE_TO_SAFE, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 5, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::ROLL_DICE_FOR_SAFE, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *6, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::SPEND_ACTIONS_TO_ENTER, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 7, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::HACK_COMPUTER, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 8, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::USE_HACK_TOKEN, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 9, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::OFFER_LOOT, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 10, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::REQUEST_LOOT, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 11, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::PICK_UP_LOOT, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 12, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::CREATE_ALARM, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 13, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::SPY_PATROL_DECK, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *14, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::PATROL_IS_TOP, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 15, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::PATROL_IS_BOTTOM, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *16, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::PLACE_CROW_TOKEN, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) *17, DISPLAYW - SPACE_DIVIDER_L, height);
    initButton((int) button_t::ACCEPT, SPACE_DIVIDER_L, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 18, (DISPLAYW - SPACE_DIVIDER_L) / 2, height);
    initButton((int) button_t::DECLINE, SPACE_DIVIDER_L + (DISPLAYW - SPACE_DIVIDER_L) / 2, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 18, (DISPLAYW - SPACE_DIVIDER_L) / 2, height);
    initButton((int) button_t::PLAY_AGAIN_YES, SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 20, (DISPLAYW - SPACE_DIVIDER_L) / 2, height);
    initButton((int) button_t::PLAY_AGAIN_NO, SPACE_DIVIDER_L + (DISPLAYW - SPACE_DIVIDER_L) / 2, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 20, (DISPLAYW - SPACE_DIVIDER_L) / 2, height);

}

void
View::initButton(unsigned i, unsigned x, unsigned y, unsigned w, unsigned h)
{
    buttons[i].x = x;
    buttons[i].y = y;
    buttons[i].width = w;
    buttons[i].height = h;
}

void
View::writeMessages()           //mensajes del chat
{
    unsigned x1 = 25;
    unsigned y1 = 575;
    ALLEGRO_BITMAP* pepe = al_load_bitmap("images/pepe.jpg");
    al_draw_bitmap(pepe, x1, y1, 0);
    al_draw_rectangle(x1, y1, x1 + al_get_bitmap_width(pepe), y1 + al_get_bitmap_height(pepe), al_map_rgb(0, 0, 0), 1);
    al_draw_textf(smallTextFont, al_map_rgb(0, 0, 0), 6 * x1, y1, ALLEGRO_ALIGN_LEFT, "%s", graphicsData->message.c_str());
}

ALLEGRO_BITMAP *
View::loadCharacter(characterV_t c, bool shrink) //Cargo bitmaps, si shrink=true, se cargan en tamaño chico, si no, en grande
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (c)
    {
        case characterV_t::V_JUICER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/juicersmall.png");
            else
                bitmap = al_load_bitmap("images/character/juicer.png");
            break;

        case characterV_t::V_HACKER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/hackersmall.png");
            else
                bitmap = al_load_bitmap("images/character/hacker.png");
            break;

        case characterV_t::V_ACROBAT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/acrobatsmall.png");
            else
                bitmap = al_load_bitmap("images/character/acrobat.png");
            break;

        case characterV_t::V_SPOTTER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/spottersmall.png");
            else
                bitmap = al_load_bitmap("images/character/spotter.png");
            break;

        case characterV_t::V_HAWK:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/hawksmall.png");
            else
                bitmap = al_load_bitmap("images/character/hawk.png");
            break;

        case characterV_t::V_RAVEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/ravensmall.png");
            else
                bitmap = al_load_bitmap("images/character/raven.png");
            break;

        case characterV_t::V_PETERMAN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/petermansmall.png");
            else
                bitmap = al_load_bitmap("images/character/peterman.png");
            break;

        case characterV_t::V_GUARD:
            bitmap = al_load_bitmap("images/character/guard.png");

            break;
    }

    return bitmap;

}

ALLEGRO_BITMAP *
View::loadLoot(lootV_t l, bool shrink)      //Cargo bitmaps, si shrink=true, se cargan en tamaño chico, si no, en grande
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (l)
    {
        case lootV_t::V_TIARA:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/tiarasmall.png");
            else
                bitmap = al_load_bitmap("images/loots/tiara.png");
            break;

        case lootV_t::V_KITTY:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/kittysmall.png");
            else
                bitmap = al_load_bitmap("images/loots/kitty.png");
            break;

        case lootV_t::V_PAINTING:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/paintingsmall.png");
            else
                bitmap = al_load_bitmap("images/loots/painting.png");
            break;

        case lootV_t::V_MIRROR:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/mirrorsmall.png");
            else
                bitmap = al_load_bitmap("images/loots/mirror.png");
            break;

        case lootV_t::V_KEYCARD:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/keycardsmall.png");
            else
                bitmap = al_load_bitmap("images/loots/keycard.png");
            break;

        case lootV_t::V_ISOTOPE:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/isotopesmall.png");
            else
                bitmap = al_load_bitmap("images/loots/isotope.png");
            break;

        case lootV_t::V_GEMSTONE:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/gemstonesmall.png");
            else
                bitmap = al_load_bitmap("images/loots/gemstone.png");
            break;

        case lootV_t::V_GOBLET:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/gobletsmall.png");
            else
                bitmap = al_load_bitmap("images/loots/goblet.png");
            break;

        case lootV_t::V_CHIHUAHUA:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/chihuahuasmall.png");
            else
                bitmap = al_load_bitmap("images/loots/chihuahua.png");
            break;

        case lootV_t::V_GOLD:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/goldsmall.png");
            else
                bitmap = al_load_bitmap("images/loots/gold.png");
            break;

        case lootV_t::V_GOLD2:
            bitmap = al_load_bitmap("images/loots/gold2.png");
            break;

        case lootV_t::V_NO_LOOT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/lootBacksmall.png");
            else
                bitmap = al_load_bitmap("images/loots/lootBack.png");

            break;
    }

    return bitmap;
}

ALLEGRO_BITMAP *
View::loadToken(tokenV_t t, bool shrink)        //Cargo bitmaps, si shrink=true, se cargan en tamaño chico, si no, en grande
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (t)
    {
        case tokenV_t::V_ALARMTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/alarmsmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/alarm.png");
            break;

        case tokenV_t::V_CROWTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/crowsmall.png");
            else

                bitmap = al_load_bitmap("images/tokens/crow.png");
            break;

        case tokenV_t::V_HACKTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/hacksmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/hack.png");
            break;

        case tokenV_t::V_KITTYTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/kittysmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/kitty.png");
            break;

        case tokenV_t::V_OPENTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/opensmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/open.png");
            break;

        case tokenV_t::V_CRACKEDTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/safesmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/safe.png");
            break;

        case tokenV_t::V_DOWNSTAIRSTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/stairssmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/stairs.png");
            break;

        case tokenV_t::V_STEALTHTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/stealthsmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/stealth.png");

            break;
    }
    return bitmap;
}

ALLEGRO_BITMAP *
View::loadRoom(roomV_t r, bool shrink)      //Cargo bitmaps, si shrink=true, se cargan en tamaño chico, si no, en grande
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (r)
    {
        case roomV_t::V_ATRIUM:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/atriumsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/atrium.png");
            break;

        case roomV_t::V_CAMERA:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/camerasmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/camera.png");
            break;

        case roomV_t::V_CR_FINGERPRINT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/CRFingerprintsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/CRFingerprint.png");
            break;

        case roomV_t::V_CR_LASER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/CRLasersmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/CRLaser.png");
            break;

        case roomV_t::V_CR_MOTION:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/CRMotionsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/CRMotion.png");
            break;

        case roomV_t::V_DEADBOLT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/deadboltsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/deadbolt.png");
            break;

        case roomV_t::V_DETECTOR:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/detectorsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/detector.png");
            break;

        case roomV_t::V_FINGERPRINT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/fingerprintsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/fingerprint.png");
            break;

        case roomV_t::V_FOYER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/foyersmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/foyer.png");
            break;

        case roomV_t::V_KEYPAD:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/keypadsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/keypad.png");
            break;

        case roomV_t::V_LABORATORY:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/laboratorysmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/laboratory.png");
            break;

        case roomV_t::V_LASER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/lasersmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/laser.png");
            break;

        case roomV_t::V_LAVATORY:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/lavatorysmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/lavatory.png");
            break;

        case roomV_t::V_MOTION:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/motionsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/motion.png");
            break;

        case roomV_t::V_ROOMBACK:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/roomBacksmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/roomBack.png");
            break;

        case roomV_t::V_SAFE:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/safesmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/safe.png");
            break;

        case roomV_t::V_SECRETDOOR:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/secretDoorsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/secretDoor.png");
            break;

        case roomV_t::V_SERVICEDUCT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/serviceDuctsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/serviceDuct.png");
            break;

        case roomV_t::V_STAIRS:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/stairssmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/stairs.png");
            break;

        case roomV_t::V_THERMO:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/thermosmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/thermo.png");
            break;

        case roomV_t::V_WALKWAY:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/walkwaysmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/walkway.png");

            break;
    }
    return bitmap;

}

ALLEGRO_BITMAP *
View::loadPatrolCard(patrolV_t p)       //Cargo bitmaps
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (p)
    {
        case patrolV_t::V_A1:
            bitmap = al_load_bitmap("images/patrol/A1.png");
            break;

        case patrolV_t::V_A2:
            bitmap = al_load_bitmap("images/patrol/A2.png");
            break;

        case patrolV_t::V_A3:
            bitmap = al_load_bitmap("images/patrol/A3.png");
            break;

        case patrolV_t::V_A4:
            bitmap = al_load_bitmap("images/patrol/A4.png");
            break;

        case patrolV_t::V_B1:
            bitmap = al_load_bitmap("images/patrol/B1.png");
            break;

        case patrolV_t::V_B2:
            bitmap = al_load_bitmap("images/patrol/B2.png");
            break;

        case patrolV_t::V_B3:
            bitmap = al_load_bitmap("images/patrol/B3.png");
            break;

        case patrolV_t::V_B4:
            bitmap = al_load_bitmap("images/patrol/B4.png");
            break;

        case patrolV_t::V_C1:
            bitmap = al_load_bitmap("images/patrol/C1.png");
            break;

        case patrolV_t::V_C2:
            bitmap = al_load_bitmap("images/patrol/C2.png");
            break;

        case patrolV_t::V_C3:
            bitmap = al_load_bitmap("images/patrol/C3.png");
            break;

        case patrolV_t::V_C4:
            bitmap = al_load_bitmap("images/patrol/C4.png");
            break;

        case patrolV_t::V_D1:
            bitmap = al_load_bitmap("images/patrol/D1.png");
            break;

        case patrolV_t::V_D2:
            bitmap = al_load_bitmap("images/patrol/D2.png");
            break;

        case patrolV_t::V_D3:
            bitmap = al_load_bitmap("images/patrol/D3.png");
            break;

        case patrolV_t::V_D4:
            bitmap = al_load_bitmap("images/patrol/D4.png");
            break;

        case patrolV_t::V_NO_PATROL:
            bitmap = al_load_bitmap("images/patrol/patrolBack.png");

            break;
    }
    return bitmap;
}

ALLEGRO_BITMAP *
View::loadGuardDie(unsigned number)     //Cargo bitmaps
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (number)
    {
        case 1:
            bitmap = al_load_bitmap("images/dices/red1.png");
            break;

        case 2:
            bitmap = al_load_bitmap("images/dices/red2.png");
            break;

        case 3:
            bitmap = al_load_bitmap("images/dices/red3.png");
            break;

        case 4:
            bitmap = al_load_bitmap("images/dices/red4.png");
            break;

        case 5:
            bitmap = al_load_bitmap("images/dices/red5.png");
            break;

        case 6:
            bitmap = al_load_bitmap("images/dices/red6.png");

            break;
    }
    return bitmap;
}

ALLEGRO_BITMAP *
View::loadSafeDie(unsigned number)      //Cargo bitmaps
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (number)
    {
        case 1:
            bitmap = al_load_bitmap("images/dices/dark1.png");
            break;

        case 2:
            bitmap = al_load_bitmap("images/dices/dark2.png");
            break;

        case 3:
            bitmap = al_load_bitmap("images/dices/dark3.png");
            break;

        case 4:
            bitmap = al_load_bitmap("images/dices/dark4.png");
            break;

        case 5:
            bitmap = al_load_bitmap("images/dices/dark5.png");
            break;

        case 6:
            bitmap = al_load_bitmap("images/dices/dark6.png");

            break;
    }
    return bitmap;
}

ALLEGRO_BITMAP *
View::loadSafeNumber(unsigned s, bool shrink)       //Cargo bitmaps, si shrink=true, se cargan en tamaño chico, si no, en grande
{

    ALLEGRO_BITMAP* bitmap = NULL;
    switch (s)
    {
        case 1:
            bitmap = al_load_bitmap("images/tiles/1.png");
            break;

        case 2:
            bitmap = al_load_bitmap("images/tiles/2.png");
            break;

        case 3:
            bitmap = al_load_bitmap("images/tiles/3.png");
            break;

        case 4:

            bitmap = al_load_bitmap("images/tiles/4.png");
            break;

        case 5:

            bitmap = al_load_bitmap("images/tiles/5.png");
            break;

        case 6:

            bitmap = al_load_bitmap("images/tiles/6.png");
            break;
        default: bitmap = NULL;

            break;
    }
    return bitmap;
}

std::string View::whichChar(characterV_t character)
{
    std::string charString;
    switch (character)
    {
        case characterV_t::V_ACROBAT:
            charString = "Acrobat";
            break;
        case characterV_t::V_HACKER:
            charString = "Hacker";
            break;
        case characterV_t::V_HAWK:
            charString = "Hawk";
            break;
        case characterV_t::V_JUICER:
            charString = "Juicer";
            break;
        case characterV_t::V_PETERMAN:
            charString = "Peterman";
            break;
        case characterV_t::V_RAVEN:
            charString = "Raven";
            break;
        case characterV_t::V_SPOTTER:
            charString = "Spotter";

            break;
        default:
            break;
    }
    return charString;
}

void*
View::getDisplay()
{
    return (void*) this->display;
}

unsigned
View::getButtonX(unsigned i)        //Devuelve posicion en x del boton
{
    return buttons[i].x;
}

unsigned
View::getButtonY(unsigned i)        //Devuelve posicion en y del boton
{
    return buttons[i].y;
}

unsigned
View::getButtonW(unsigned i)        //Devuelve width del boton
{
    return buttons[i].width;
}

unsigned
View::getButtonH(unsigned i)        //Devuelve height del boton
{
    return buttons[i].height;
}