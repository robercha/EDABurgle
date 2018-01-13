#include "View.h"

//typedef enum
//{
//    HOMESCREEN, SETTINGSSCREEN, HELPSCREEN, PLAYINGSCREEN, CREDITSSCREEN, SCREENCOUNT
//} screen_t;

//carga botones
static void initUtilities(bitmap_t*);
void drawVerticalWall(unsigned floor, unsigned row, unsigned col);
void drawHorizontalWall(unsigned floor, unsigned row, unsigned col); //floor =(1,2,3);row=(1,2,3,4);col=(1,2,3,4)

/*Créditos a user: Matthew de stackoverflow:
 https://stackoverflow.com/questions/15048136/loading-a-bitmap-image-to-a-certain-size*/
ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h);

#define TILE_SIZE                   71
#define CARD_SELECTED_SIZE          162
#define CHARACTERS_BIG_WIDTH        60
#define CHARACTERS_BIG_HEIGHT       75
#define CHARACTERS_SMALL_WIDTH      33
#define CHARACTERS_SMALL_HEIGHT     49
#define STEALTH_TOKENS_SIZE         27
#define TOKENS_BIG_SIZE             22
#define GUARD_WIDTH                 22
#define GUARD_HEIGHT                24
#define DICE_SIZE                   24
#define GOLD2_WIDTH                 28
#define GOLD2_HEIGHT                23
#define PATROL_CARD_SIZE            60
#define LOOT_CARD_SIZE              60
#define TOKENS_SMALL_SIZE           17   //capaz no hace falta

#define SPACE_LEFT_MARGIN           20
#define SPACE_UP_MARGIN             10
#define SPACE_TILE                  10
#define SPACE_FLOOR                 40
#define SPACE_TOKEN_LR              20
#define SPACE_TOKEN_UD              7
#define SPACE_DIVIDER_L             1050
#define SPACE_DIVIDER_U             550

#define FONT_HUGE_SIZE              60
#define FONT_BIG_SIZE               18
#define FONT_MEDIUM_SIZE            14
#define FONT_SMALL_SIZE             12


//#   start x     start y     an      al
//1   23          8           50      76    //character you
//2   79          14          27      27    //stealth you
//3   78          61          24      15    //x3 you
//4   252         14          27      27    //stealth partner
//5   256         61                        //x3 partner
//6   288         12          55      72    //character partner
//7   22          134         71      71      //tile
//8
//9
//10
//
//pepe&co a x=473; y=60
//PEPE&CO FONT=60
//
//cracking dice font 12
//tile: 12
//tile selected 14
//3rd floor: 18
//abcd1234 font:18
//marron de pared= #a9814c (169,127,77)

View::View()
{

    this->display = NULL; //cargamos datos en la estructura display
    this->titleFont = NULL;
    this->textFont = NULL;
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
                        al_set_window_title(this->display, "Pepe&Co"); //titulo
                        this->background = al_load_bitmap("images/background.jpg");
                        if (this->background != NULL)
                        {
                            this->backgroundWidth = al_get_bitmap_width(this->background);
                            this->backgroundHeight = al_get_bitmap_height(this->background);

                            this->textFont = al_load_ttf_font("fonts/Dudu.ttf", 20, 0);
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
                                                this->titleFont = al_load_ttf_font("fonts/Whatnot.ttf", 80, 0);
                                                if (this->titleFont != NULL)
                                                {
                                                    al_draw_bitmap(this->background, 0, 0, 0);
                                                    al_start_timer(this->timer);
                                                }
                                                else
                                                {
                                                    al_destroy_bitmap(this->background);
                                                    al_destroy_event_queue(this->eventQueue);
                                                    al_destroy_font(this->textFont);
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

    this->buttons = new std::vector<bitmap_t>; //inicializo en 0 vector
    for (unsigned i = 0; i < (int) button::BUTTON_COUNT; ++i)
        buttons->push_back(bitmap_t());


    this->graphicsData = (graphicsData_t*) malloc(sizeof (graphicsData_t));


    //    this->buttons = (bitmap_t*) malloc(sizeof (bitmap_t) * BUTTON_COUNT);

    //initUtilities(this->buttons);

}

View::~View()
{
    al_destroy_bitmap(this->background);
    al_destroy_event_queue(this->eventQueue);
    al_destroy_font(this->textFont);
    al_destroy_font(this->titleFont);
    al_destroy_timer(this->timer);
    al_destroy_display(this->display);
    al_shutdown_ttf_addon();
    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_shutdown_font_addon();
    al_uninstall_mouse();
    al_uninstall_keyboard();


    buttons->clear();
    delete buttons;

    free(this->graphicsData);

    //    unsigned i;
    //    for (i = 0; i < BUTTON_COUNT; i++)
    //    {
    //        al_destroy_bitmap(this->buttons[i].image);
    //    }
    //
    //    free(this->buttons);
}

void
View::menuDisplay(void)
{
    //al_set_target_backbuffer(->display); //Vuelve al display
    //al_draw_scaled_bitmap(this->background, 0, 0, this->backgroundWidth, this->backgroundHeight, 0, 0, this->width, this->height, 0); //dibujo fondo
    al_draw_bitmap(this->background, 0, 0, 0); //dibujo fondo
    //al_draw_bitmap(this->buttons[TEST].image, this->buttons[TEST].x, this->buttons[TEST].y, 0); //dibujo boton single player
    //al_draw_text(this->titleFont, al_map_rgb(143, 91, 3), 545, 30, ALLEGRO_ALIGN_CENTRE, "Lu esta pelotuda");

    al_flip_display();
}

unsigned
View::getButtonX(unsigned i)
{
    return buttons->at(i).x;
}

unsigned
View::getButtonY(unsigned i)
{
    return buttons->at(i).y;
}

unsigned
View::getButtonW(unsigned i)
{
    return buttons->at(i).width;
}

unsigned
View::getButtonH(unsigned i)
{
    return buttons->at(i).height;
}

bool
View::updateGraphics()
{
    drawBackground();
    writeTitle();
    drawChatDividers();
    drawBoard();
    drawCardInfo();

    writeActions();
    writeMessages();

    al_flip_display();
    al_rest(5);
}

void
View::drawBoard()
{
    drawCharactersInfo();
    drawFloors();
}

void
View::drawFloors()
{
    drawTiles();
    drawWalls();

    writeFloorTexts();
    drawPatrolDecks();
    drawLoots();

    drawCharacters();
    drawGuardDice();
    drawGuards();
    drawTokensOnTiles(); //ver bien
}

void
View::drawCardInfo()
{
    //una de estas
    showNoCardSelected();
    drawTileSelectedInfo();
    drawLootSelectedInfo();
}

void
View::drawTileSelectedInfo()
{
    drawSelectedTileTokens();
}

void
View::drawBackground()
{
    al_draw_bitmap(this->background, 0, 0, 0); //dibujo fondo
}

void
View::writeTitle()
{
    ALLEGRO_BITMAP* title = al_load_bitmap("images/texts/pepeycq.png");
    //al_draw_text(titleFont, al_map_rgb(0, 0, 0), 550, 0, ALLEGRO_ALIGN_CENTER, "Pepe&Co. HQ");
    al_draw_bitmap(title, 400, 0, 0);
    al_destroy_bitmap(title);
}

void
View::drawChatDividers()
{
    al_draw_line(1050, 0, 1050, 550, al_map_rgb(0, 0, 0), 1);
    al_draw_line(0, 550, 1050, 550, al_map_rgb(0, 0, 0), 1);
}

void
View::drawCharactersInfo()
{
    ALLEGRO_BITMAP* playerOne = loadCharacter(graphicsData->players[0].character);
    al_draw_bitmap(playerOne, 20, 100 - (al_get_bitmap_height(playerOne)), 0);
    al_destroy_bitmap(playerOne);

    ALLEGRO_BITMAP* stealthOne = loadToken(token_t::STEALTHTOKEN);
    for (unsigned i = 0; i < graphicsData->players[0].stealthTokens; ++i)
        al_draw_bitmap(stealthOne, 80, i * (5 + STEALTH_TOKENS_SIZE) + 10, 0);
    al_destroy_bitmap(stealthOne);

    ALLEGRO_BITMAP* playerTwo = loadCharacter(graphicsData->players[1].character);
    al_draw_bitmap(playerTwo, 270, 100 - (al_get_bitmap_height(playerTwo)), 0);
    al_destroy_bitmap(playerTwo);

    ALLEGRO_BITMAP* stealthTwo = loadToken(token_t::STEALTHTOKEN);
    for (unsigned i = 0; i < graphicsData->players[1].stealthTokens; ++i)
        al_draw_bitmap(stealthTwo, 240, i * (5 + STEALTH_TOKENS_SIZE) + 10, 0);
    al_destroy_bitmap(stealthTwo);

    al_draw_text(textFont, al_map_rgb(0, 0, 0), 50, 95, ALLEGRO_ALIGN_CENTER, "you");
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 300, 95, ALLEGRO_ALIGN_CENTER, "partner");
}

void
View::drawTiles()
{
    unsigned i = 0, x1, y1, x2, y2;
    for (unsigned floor = 0; floor < 3; floor++)
        for (unsigned rows = 0; rows < 4; rows++, i++)
        {
            for (unsigned cols = 0; cols < 4; cols++, i++)
            {
                x1 = 20 + cols * (TILE_SIZE + SPACE_TILE) + floor * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3);
                y1 = 135 + rows * (TILE_SIZE + SPACE_TILE);
                if (graphicsData->tiles[i].iAm == room_t::ROOMBACK)
                {
                    ALLEGRO_BITMAP* tile = loadRoom(room_t::ROOMBACK);
                    al_draw_bitmap(tile, x1, y1, 0);
                    al_destroy_bitmap(tile);
                }
                else
                {
                    ALLEGRO_BITMAP* tile = loadRoom(graphicsData->tiles[i].iAm);
                    al_draw_bitmap(tile, 20 + cols * (TILE_SIZE + SPACE_TILE) + SPACE_FLOOR * floor + floor * (TILE_SIZE * 4 + SPACE_TILE * 3), 135 + rows * (TILE_SIZE + SPACE_TILE), 0);
                    al_draw_scaled_bitmap(tile, x1, y1, al_get_bitmap_width(tile), al_get_bitmap_height(tile), x1, y1, TILE_SIZE, TILE_SIZE, 0);
                    al_destroy_bitmap(tile);
                    if (graphicsData->tiles[i].iAm != room_t::SAFE)
                    {
                        ALLEGRO_BITMAP* number = loadSafeNumber(graphicsData->tiles[i].combinationNumber);
                        al_draw_bitmap(number, 20 + cols * (TILE_SIZE + SPACE_TILE) + floor * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3), 135 + rows * (TILE_SIZE + SPACE_TILE), 0);
                        al_destroy_bitmap(number);
                    }
                }
            }
            i--;
        }
}

void
View::drawWalls()
{
    drawVerticalWall(1, 1, 1);
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
View::writeFloorTexts()
{
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 20 + TILE_SIZE * 2 + SPACE_TILE + SPACE_TILE / 2, 135 + TILE_SIZE * 4 + SPACE_TILE * 3 + SPACE_TILE / 4, ALLEGRO_ALIGN_CENTER, "1st Floor");
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 20 + SPACE_FLOOR + TILE_SIZE * 6 + SPACE_TILE * 4 + SPACE_TILE / 2, 135 + TILE_SIZE * 4 + SPACE_TILE * 3 + SPACE_TILE / 4, ALLEGRO_ALIGN_CENTER, "2nd Floor");
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 20 + SPACE_FLOOR * 2 + TILE_SIZE * 10 + SPACE_TILE * 7 + SPACE_TILE / 2, 135 + TILE_SIZE * 4 + SPACE_TILE * 3 + SPACE_TILE / 4, ALLEGRO_ALIGN_CENTER, "3rd Floor");
}

void
View::drawPatrolDecks()
{
    for (unsigned i = 0; i < V_TOTAL_GUARDS; i++)
    {
        ALLEGRO_BITMAP* bitmap = loadPatrolCard(graphicsData->guards[i].patrolDeck);
        al_draw_bitmap(bitmap, 20 + 1 * (TILE_SIZE + SPACE_TILE) + SPACE_FLOOR * i + i * (TILE_SIZE * 4 + SPACE_TILE * 3), 135 + TILE_SIZE * 4 + SPACE_TILE * 6, 0);
        al_destroy_bitmap(bitmap);
    }
}

void
View::drawLoots()
{
    unsigned x, y;
    for (unsigned i = 0; i < V_TOTAL_LOOTS; i++)
    {
        x = 20 + 2 * (TILE_SIZE + SPACE_TILE) + SPACE_FLOOR * i + i * (TILE_SIZE * 4 + SPACE_TILE * 3);
        y = 135 + TILE_SIZE * 4 + SPACE_TILE * 6;
        ALLEGRO_BITMAP* bitmap = loadLoot(graphicsData->loots[i]);
        al_draw_bitmap(bitmap, x, y, 0);
        //al_draw_scaled_bitmap(bitmap, x, y, (float) al_get_bitmap_width(bitmap), (float) al_get_bitmap_height(bitmap), x, y, 60.0, 60.0, 0);
        al_destroy_bitmap(bitmap);
    }
}

void
View::drawCharacters()
{

}

void
View::drawGuardDice()
{

}

void
View::drawGuards()
{

}

void
View::drawTokensOnTiles()
{ //ver bien

}

void
View::showNoCardSelected()
{

}

void
View::drawSelectedTileTokens()
{

}

void
View::drawLootSelectedInfo()
{

}

void
View::writeActions()
{

}

void
View::writeMessages()
{

}

ALLEGRO_BITMAP*
View::loadCharacter(character_t c, bool shrink)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (c)
    {
        case character_t::JUICER:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/character/juicer.png", CHARACTERS_SMALL_WIDTH, CHARACTERS_SMALL_HEIGHT);
            else
                bitmap = al_load_bitmap("images/character/juicer.png");
            break;

        case character_t::HACKER:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/character/hacker.png", CHARACTERS_SMALL_WIDTH, CHARACTERS_SMALL_HEIGHT);
            else
                bitmap = al_load_bitmap("images/character/hacker.png");
            break;

        case character_t::ACROBAT:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/character/acrobat.png", CHARACTERS_SMALL_WIDTH, CHARACTERS_SMALL_HEIGHT);
            else
                bitmap = al_load_bitmap("images/character/acrobat.png");
            break;

        case character_t::SPOTTER:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/character/spotter.png", CHARACTERS_SMALL_WIDTH, CHARACTERS_SMALL_HEIGHT);
            else
                bitmap = al_load_bitmap("images/character/spotter.png");
            break;

        case character_t::HAWK:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/character/hawk.png", CHARACTERS_SMALL_WIDTH, CHARACTERS_SMALL_HEIGHT);
            else
                bitmap = al_load_bitmap("images/character/hawk.png");
            break;

        case character_t::RAVEN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/character/raven.png", CHARACTERS_SMALL_WIDTH, CHARACTERS_SMALL_HEIGHT);
            else
                bitmap = al_load_bitmap("images/character/raven.png");
            break;

        case character_t::PETERMAN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/character/peterman.png", CHARACTERS_SMALL_WIDTH, CHARACTERS_SMALL_HEIGHT);
            else
                bitmap = al_load_bitmap("images/character/peterman.png");
            break;

        case character_t::GUARD:
            bitmap = al_load_bitmap("images/character/guard.png");

            break;
    }

    return bitmap;

}

ALLEGRO_BITMAP*
View::loadLoot(loot_t l, bool shrink)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (l)
    {
        case loot_t::TIARA:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/tiara.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/tiara.png");
            break;

        case loot_t::KITTY:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/kitty.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/kitty.png");
            break;

        case loot_t::PAINTING:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/painting.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/painting.png");
            break;

        case loot_t::MIRROR:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/mirror.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/mirror.png");
            break;

        case loot_t::KEYCARD:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/keycard.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/keycard.png");
            break;

        case loot_t::ISOTOPE:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/isotope.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/isotope.png");
            break;

        case loot_t::GEMSTONE:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/gemstone.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/gemstone.png");
            break;

        case loot_t::GOBLET:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/goblet.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/goblet.png");
            break;

        case loot_t::CHIHUAHUA:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/chihuahua.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/chihuahua.png");
            break;

        case loot_t::GOLD:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/loots/gold.png", LOOT_CARD_SIZE, LOOT_CARD_SIZE);
            else
                bitmap = al_load_bitmap("images/loots/gold.png");
            break;

        case loot_t::GOLD2:
            bitmap = al_load_bitmap("images/loots/gold2.png");
            break;

        case loot_t::NO_LOOT:
            bitmap = al_load_bitmap("images/loots/lootBack.png");

            break;
    }

    return bitmap;
}

ALLEGRO_BITMAP*
View::loadToken(token_t t, bool shrink)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (t)
    {
        case token_t::ALARMTOKEN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tokens/alarm.png", TOKENS_SMALL_SIZE, TOKENS_SMALL_SIZE);
            else
                bitmap = al_load_bitmap("images/tokens/alarm.png");
            break;

        case token_t::CROWTOKEN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tokens/crow.png", TOKENS_SMALL_SIZE, TOKENS_SMALL_SIZE);
            else

                bitmap = al_load_bitmap("images/tokens/crow.png");
            break;

        case token_t::HACKTOKEN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tokens/hack.png", TOKENS_SMALL_SIZE, TOKENS_SMALL_SIZE);
            else
                bitmap = al_load_bitmap("images/tokens/hack.png");
            break;

        case token_t::KITTYTOKEN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tokens/kitty.png", TOKENS_SMALL_SIZE, TOKENS_SMALL_SIZE);
            else
                bitmap = al_load_bitmap("images/tokens/kitty.png");
            break;

        case token_t::OPENTOKEN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tokens/open.png", TOKENS_SMALL_SIZE, TOKENS_SMALL_SIZE);
            else
                bitmap = al_load_bitmap("images/tokens/open.png");
            break;

        case token_t::CRACKEDTOKEN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tokens/safe.png", TOKENS_SMALL_SIZE, TOKENS_SMALL_SIZE);
            else
                bitmap = al_load_bitmap("images/tokens/safe.png");
            break;

        case token_t::DOWNSTAIRSTOKEN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tokens/stairs.png", TOKENS_SMALL_SIZE, TOKENS_SMALL_SIZE);
            else
                bitmap = al_load_bitmap("images/tokens/stairs.png");
            break;

        case token_t::STEALTHTOKEN:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tokens/stealth.png", TOKENS_SMALL_SIZE, TOKENS_SMALL_SIZE);
            else
                bitmap = al_load_bitmap("images/tokens/stealth.png");

            break;
    }
    return bitmap;
}

ALLEGRO_BITMAP*
View::loadRoom(room_t r, bool shrink)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (r)
    {
        case room_t::ATRIUM:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/atrium.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/atrium.png");
            break;

        case room_t::CAMERA:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/camera.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/camera.png");
            break;

        case room_t::CR_FINGERPRINT:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/CRFingerprint.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/CRFingerprint.png");
            break;

        case room_t::CR_LASER:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/CRLaser.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/CRLaser.png");
            break;

        case room_t::CR_MOTION:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/CRMotion.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/CRMotion.png");
            break;

        case room_t::DEADBOLT:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/deadbolt.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/deadbolt.png");
            break;

        case room_t::DETECTOR:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/detector.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/detector.png");
            break;

        case room_t::FINGERPRINT:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/fingerprint.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/fingerprint.png");
            break;

        case room_t::FOYER:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/foyer.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/foyer.png");
            break;

        case room_t::KEYPAD:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/keypad.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/keypad.png");
            break;

        case room_t::LABORATORY:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/laboratory.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/laboratory.png");
            break;

        case room_t::LASER:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/laser.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/laser.png");
            break;

        case room_t::LAVATORY:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/lavatory.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/lavatory.png");
            break;

        case room_t::MOTION:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/motion.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/motion.png");
            break;

        case room_t::ROOMBACK:
            bitmap = al_load_bitmap("images/tiles/roomBack.png");
            break;

        case room_t::SAFE:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/safe.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/safe.png");
            break;

        case room_t::SECRETDOOR:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/secretDoor.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/secretDoor.png");
            break;

        case room_t::SERVICEDUCT:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/serviceDuct.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/serviceDuct.png");
            break;

        case room_t::STAIRS:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/stairs.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/stairs.png");
            break;

        case room_t::THERMO:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/thermo.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/thermo.png");
            break;

        case room_t::WALKWAY:
            if (shrink == true)
                bitmap = load_bitmap_at_size("images/tiles/walkway.png", TILE_SIZE, TILE_SIZE);
            else
                bitmap = al_load_bitmap("images/tiles/walkway.png");

            break;
    }
    return bitmap;

}

ALLEGRO_BITMAP*
View::loadPatrolCard(patrol_t p)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (p)
    {
        case patrol_t::A1:
            bitmap = al_load_bitmap("images/patrol/A1.png");
            break;

        case patrol_t::A2:
            bitmap = al_load_bitmap("images/patrol/A2.png");
            break;

        case patrol_t::A3:
            bitmap = al_load_bitmap("images/patrol/A3.png");
            break;

        case patrol_t::A4:
            bitmap = al_load_bitmap("images/patrol/A4.png");
            break;

        case patrol_t::B1:
            bitmap = al_load_bitmap("images/patrol/B1.png");
            break;

        case patrol_t::B2:
            bitmap = al_load_bitmap("images/patrol/B2.png");
            break;

        case patrol_t::B3:
            bitmap = al_load_bitmap("images/patrol/B3.png");
            break;

        case patrol_t::B4:
            bitmap = al_load_bitmap("images/patrol/B4.png");
            break;

        case patrol_t::C1:
            bitmap = al_load_bitmap("images/patrol/C1.png");
            break;

        case patrol_t::C2:
            bitmap = al_load_bitmap("images/patrol/C2.png");
            break;

        case patrol_t::C3:
            bitmap = al_load_bitmap("images/patrol/C3.png");
            break;

        case patrol_t::C4:
            bitmap = al_load_bitmap("images/patrol/C4.png");
            break;

        case patrol_t::D1:
            bitmap = al_load_bitmap("images/patrol/D1.png");
            break;

        case patrol_t::D2:
            bitmap = al_load_bitmap("images/patrol/D2.png");
            break;

        case patrol_t::D3:
            bitmap = al_load_bitmap("images/patrol/D3.png");
            break;

        case patrol_t::D4:
            bitmap = al_load_bitmap("images/patrol/D4.png");
            break;

        case patrol_t::NO_PATROL:
            bitmap = al_load_bitmap("images/patrol/patrolBack.png");

            break;
    }
    return bitmap;
}

ALLEGRO_BITMAP*
View::loadDie(dice_t d)
{

    ALLEGRO_BITMAP* bitmap = NULL;
    switch (d)
    {
        case dice_t::GUARD_DIE1:
            bitmap = al_load_bitmap("images/dices/dark1.png");
            break;

        case dice_t::GUARD_DIE2:
            bitmap = al_load_bitmap("images/dices/dark2.png");
            break;

        case dice_t::GUARD_DIE3:
            bitmap = al_load_bitmap("images/dices/dark3.png");
            break;

        case dice_t::GUARD_DIE4:
            bitmap = al_load_bitmap("images/dices/dark4.png");
            break;

        case dice_t::GUARD_DIE5:
            bitmap = al_load_bitmap("images/dices/dark5.png");
            break;

        case dice_t::GUARD_DIE6:
            bitmap = al_load_bitmap("images/dices/dark6.png");
            break;

        case dice_t::SAFE_DIE1:
            bitmap = al_load_bitmap("images/dices/red1.png");
            break;

        case dice_t::SAFE_DIE2:
            bitmap = al_load_bitmap("images/dices/red2.png");
            break;

        case dice_t::SAFE_DIE3:
            bitmap = al_load_bitmap("images/dices/red3.png");
            break;

        case dice_t::SAFE_DIE4:
            bitmap = al_load_bitmap("images/dices/red4.png");
            break;

        case dice_t::SAFE_DIE5:
            bitmap = al_load_bitmap("images/dices/red5.png");
            break;

        case dice_t::SAFE_DIE6:
            bitmap = al_load_bitmap("images/dices/red6.png");

            break;
    }
    return bitmap;
}

ALLEGRO_BITMAP*
View::loadSafeNumber(unsigned s)
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
    }
    return bitmap;
}

ALLEGRO_BITMAP *
load_bitmap_at_size(const char *filename, int w, int h)
{
    ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;

    // 1. create a temporary bitmap of size we want
    resized_bmp = al_create_bitmap(w, h);
    if (!resized_bmp) return NULL;

    // 2. load the bitmap at the original size
    loaded_bmp = al_load_bitmap(filename);
    if (!loaded_bmp)
    {
        al_destroy_bitmap(resized_bmp);
        return NULL;
    }

    // 3. set the target bitmap to the resized bmp
    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(resized_bmp);

    // 4. copy the loaded bitmap to the resized bmp
    al_draw_scaled_bitmap(loaded_bmp,
            0, 0, // source origin
            al_get_bitmap_width(loaded_bmp), // source width
            al_get_bitmap_height(loaded_bmp), // source height
            0, 0, // target origin
            w, h, // target dimensions
            0 // flags
            );

    // 5. restore the previous target and clean up
    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    return resized_bmp;
}

void
initUtilities(bitmap_t * bitmapArray)
{
    //    bitmapArray[TEST].image = al_load_bitmap("test.jpg"); //fondo
    //    bitmapArray[TEST].screen = PLAYINGSCREEN;
    //    bitmapArray[TEST].width = al_get_bitmap_width(bitmapArray[TEST].image);
    //    bitmapArray[TEST].height = al_get_bitmap_height(bitmapArray[TEST].image);
    //    bitmapArray[TEST].x = DISPLAYW / 2;
    //    bitmapArray[TEST].y = DISPLAYH / 2;

}

//void
//gameOverDisplay(display_t* displayData)
//{
//    al_draw_filled_rectangle(DISPLAYW / 2 - 280, DISPLAYH / 2 - 180, DISPLAYW / 2 + 280, DISPLAYH / 2 + 140, al_map_rgb(233, 219, 123));
//    al_draw_rectangle(DISPLAYW / 2 - 280, DISPLAYH / 2 - 180, DISPLAYW / 2 + 280, DISPLAYH / 2 + 140, al_map_rgb(97, 86, 33), 6);
//
//    al_draw_text(displayData->titleFont, al_map_rgb(0, 0, 0), DISPLAYW / 2, DISPLAYH / 2 - 155, ALLEGRO_ALIGN_CENTRE, "EXPERIMENT");
//    al_draw_text(displayData->titleFont, al_map_rgb(0, 0, 0), DISPLAYW / 2, DISPLAYH / 2 - 70, ALLEGRO_ALIGN_CENTRE, "FINISHED");
//    al_flip_display();
//}



