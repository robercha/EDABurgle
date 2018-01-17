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
#define TOKENS_SMALL_SIZE           17   //capaz no hace falta

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

    this->display = NULL; //cargamos datos en la estructura display
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
                        al_set_window_title(this->display, "Pepe&Co"); //titulo
                        this->background = al_load_bitmap("images/background.jpg");
                        if (this->background != NULL)
                        {
                            this->backgroundWidth = al_get_bitmap_width(this->background);
                            this->backgroundHeight = al_get_bitmap_height(this->background);

                            this->textFont = al_load_ttf_font("fonts/Dudu.ttf", 20, 0);
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
                                                this->titleFont = al_load_ttf_font("fonts/Whatnot.ttf", 65, 0);
                                                if (this->titleFont != NULL)
                                                {
                                                    this->graphicsData = (graphicsData_t*) malloc(sizeof (graphicsData_t));
                                                    this->buttons = (bitmap_t*) malloc(sizeof (bitmap_t) * (int) button_t::BUTTON_COUNT);
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

    free(this->graphicsData);
    free(this->buttons);

}

unsigned
View::getButtonX(unsigned i)
{
    return buttons[i].x;
}

unsigned
View::getButtonY(unsigned i)
{
    return buttons[i].y;
}

unsigned
View::getButtonW(unsigned i)
{
    return buttons[i].width;
}

unsigned
View::getButtonH(unsigned i)
{
    return buttons[i].height;
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
    return true;
}

void
View::drawBoard()
{
    drawCharactersInfo();
    drawFloors();
    return;
}

void
View::drawFloors()
{
    drawTiles();
    drawWalls();

    writeFloorTexts();
    writeCoordinates();
    drawPatrolDecks();
    drawLoots();

    drawCharacters();
    drawGuardDice();
    drawGuards();
    drawTokensOnTiles(); //ver bien
    return;
}

void
View::drawCardInfo()
{
    if (isCardSelectedLoot(graphicsData->currentCardSelected))
        drawLootSelectedInfo();
    else if (isCardSelectedTile(graphicsData->currentCardSelected))
    {
        drawTileSelectedInfo();
        writeSelectedTileInfo();
        drawSelectedTileTokens();
    }
    else
        showNoCardSelected();
    al_flip_display();
    return;
}

bool
View::isCardSelectedLoot(button_t button)
{
    bool isLoot = false;
    if (button == button_t::LOOTF1 || button == button_t::LOOTF2 || button == button_t::LOOTF3)
        isLoot = true;
    return isLoot;
}

bool
View::isCardSelectedTile(button_t button)
{
    bool isTile = false;
    if ((int) button <= (int) button_t::D4F3)
        isTile = true;
    return isTile;
}

void
View::drawBackground()
{
    al_draw_bitmap(this->background, 0, 0, 0); //dibujo fondo
    return;
}

void
View::writeTitle()
{
    al_draw_text(titleFont, al_map_rgb(0, 0, 0), 530, 0, ALLEGRO_ALIGN_CENTER, "Pepe&Co. HQ");
    return;
}

void
View::drawChatDividers()
{
    al_draw_line(1050, 0, 1050, 550, al_map_rgb(0, 0, 0), 1);
    al_draw_line(0, 550, 1050, 550, al_map_rgb(0, 0, 0), 1);
    return;
}

void
View::drawCharactersInfo()
{//player one
    ALLEGRO_BITMAP* playerOne = loadCharacter(graphicsData->players[0].character, false);
    al_draw_bitmap(playerOne, 25 + 1 * (TILE_SIZE + SPACE_TILE), 95 - (al_get_bitmap_height(playerOne)), 0);
    al_destroy_bitmap(playerOne);

    ALLEGRO_BITMAP* stealthOne = loadToken(token_t::STEALTHTOKEN, false);
    for (unsigned i = 0; i < graphicsData->players[0].stealthTokens; ++i)
        al_draw_bitmap(stealthOne, 85 + 1 * (TILE_SIZE + SPACE_TILE), i * (5 + TOKENS_BIG_SIZE) + 5, 0);
    al_destroy_bitmap(stealthOne);

    al_draw_textf(smallTextFont, al_map_rgb(0, 0, 0), 180 + 70, 43, ALLEGRO_ALIGN_CENTER, "actions x%d", graphicsData->players[0].actionsLeft);
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), 55 + 1 * (TILE_SIZE + SPACE_TILE), 90, ALLEGRO_ALIGN_CENTER, "you");

    //player two
    ALLEGRO_BITMAP * playerTwo = loadCharacter(graphicsData->players[1].character, false);
    al_draw_bitmap(playerTwo, 270 + 625, 95 - (al_get_bitmap_height(playerTwo)), 0);
    al_destroy_bitmap(playerTwo);

    ALLEGRO_BITMAP * stealthTwo = loadToken(token_t::STEALTHTOKEN, false);
    for (unsigned i = 0; i < graphicsData->players[1].stealthTokens; ++i)
        al_draw_bitmap(stealthTwo, 240 + 625, i * (5 + TOKENS_BIG_SIZE) + 5, 0);
    al_destroy_bitmap(stealthTwo);

    al_draw_textf(smallTextFont, al_map_rgb(0, 0, 0), 300 + 510, 43, ALLEGRO_ALIGN_CENTER, "actions x%d", graphicsData->players[0].actionsLeft);
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), 300 + 625, 90, ALLEGRO_ALIGN_CENTER, "partner");

    return;
}

void
View::drawTiles()
{
    unsigned i = 0, x, y;
    for (unsigned floor = 0; floor < 3; floor++)
        for (unsigned rows = 0; rows < 4; rows++, i++)
        {
            for (unsigned cols = 0; cols < 4; cols++, i++)
            {
                x = 20 + cols * (TILE_SIZE + SPACE_TILE) + floor * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3);
                y = 135 + rows * (TILE_SIZE + SPACE_TILE);
                if (graphicsData->tiles[i].iAm == room_t::ROOMBACK)
                {
                    ALLEGRO_BITMAP* tile = loadRoom(room_t::ROOMBACK, false);
                    al_draw_bitmap(tile, x, y, 0);
                    al_destroy_bitmap(tile);
                }
                else
                {
                    ALLEGRO_BITMAP* tile = loadRoom(graphicsData->tiles[i].iAm, true);
                    al_draw_bitmap(tile, x, y, 0);
                    //al_draw_scaled_bitmap(tile, x, y, al_get_bitmap_width(tile), al_get_bitmap_height(tile), x, y, TILE_SIZE, TILE_SIZE, 0);
                    al_destroy_bitmap(tile);
                    if (graphicsData->tiles[i].iAm != room_t::SAFE)
                    {

                        ALLEGRO_BITMAP* number = loadSafeNumber(graphicsData->tiles[i].combinationNumber, true);
                        al_draw_bitmap(number, x, y, 0);
                        al_destroy_bitmap(number);
                    }
                }
            }
            i--;
        }
    return;
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
    return;
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
    return;
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
    return;
}

void
View::writeFloorTexts()
{
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 20 + TILE_SIZE * 2 + SPACE_TILE + SPACE_TILE / 2, 135 + TILE_SIZE * 4 + SPACE_TILE * 3 + SPACE_TILE / 4, ALLEGRO_ALIGN_CENTER, "1st Floor");
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 20 + SPACE_FLOOR + TILE_SIZE * 6 + SPACE_TILE * 4 + SPACE_TILE / 2, 135 + TILE_SIZE * 4 + SPACE_TILE * 3 + SPACE_TILE / 4, ALLEGRO_ALIGN_CENTER, "2nd Floor");
    al_draw_text(textFont, al_map_rgb(0, 0, 0), 20 + SPACE_FLOOR * 2 + TILE_SIZE * 10 + SPACE_TILE * 7 + SPACE_TILE / 2, 135 + TILE_SIZE * 4 + SPACE_TILE * 3 + SPACE_TILE / 4, ALLEGRO_ALIGN_CENTER, "3rd Floor");
    return;
}

void
View::writeCoordinates()
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
    return;
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
    return;
}

void
View::drawLoots()
{
    unsigned x, y;
    for (unsigned i = 0; i < V_TOTAL_LOOTS; i++)
    {
        x = 20 + 2 * (TILE_SIZE + SPACE_TILE) + SPACE_FLOOR * i + i * (TILE_SIZE * 4 + SPACE_TILE * 3);
        y = 135 + TILE_SIZE * 4 + SPACE_TILE * 6;
        ALLEGRO_BITMAP* bitmap = loadLoot(graphicsData->loots[i], true);
        al_draw_bitmap(bitmap, x, y, 0);
        al_destroy_bitmap(bitmap);
    }
    return;
}

void
View::drawCharacters()
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
    return;
}

unsigned
View::getColumn(location_t location)
{
    unsigned floor = getFloor(location);
    unsigned index = (int) location - (floor) * V_ROWS*V_COLUMNS;

    return index % V_COLUMNS;
}

unsigned
View::getRow(location_t location)
{
    unsigned floor = getFloor(location);
    unsigned index = (int) location - (floor) * V_ROWS*V_COLUMNS;

    return (int) (index / V_COLUMNS);
}

unsigned
View::getFloor(location_t location)
{
    return ((int) location) / (V_ROWS * V_COLUMNS);
}

void
View::drawGuardDice()
{
    unsigned col, row, floor, x, y;
    for (unsigned i = 0; i < V_TOTAL_GUARDS; i++)
    {
        if (graphicsData->guards[i].location == location_t::NO_LOCATION)
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
    return;
}

void
View::drawGuards()
{
    unsigned col, row, floor, x, y;
    for (unsigned i = 0; i < V_TOTAL_GUARDS; i++)
    {
        if (graphicsData->guards[i].location == location_t::NO_LOCATION)
            continue;
        ALLEGRO_BITMAP * guard = loadCharacter(character_t::GUARD, false);
        col = getColumn(graphicsData->guards[i].location);
        row = getRow(graphicsData->guards[i].location);
        floor = getFloor(graphicsData->guards[i].location);
        x = 20 + col * (TILE_SIZE + SPACE_TILE) + floor * (SPACE_FLOOR + TILE_SIZE * 4 + SPACE_TILE * 3) + TILE_SIZE / 2 - al_get_bitmap_width(guard) / 2;
        y = 135 + row * (TILE_SIZE + SPACE_TILE) + TILE_SIZE - TILE_SIZE / 2 - al_get_bitmap_width(guard) / 2;
        al_draw_bitmap(guard, x, y, 0);
        al_destroy_bitmap(guard);
    }
    return;
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
            ALLEGRO_BITMAP* extraGold = loadLoot(loot_t::GOLD2, false);
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
    return;

}

void
View::drawTileSelectedInfo()
{
    al_flip_display();
    unsigned index = (int) graphicsData->currentCardSelected;
    printf("selected%d\n", index);
    printf("room selected%d\n", (int) graphicsData->tiles[index].iAm);

    if (graphicsData->tiles[index].iAm != room_t::ROOMBACK)
    {
        ALLEGRO_BITMAP* tile = loadRoom(graphicsData->tiles[index].iAm, false);
        al_draw_bitmap(tile, (DISPLAYW - SPACE_DIVIDER_L - CARD_SELECTED_SIZE) / 2 + SPACE_DIVIDER_L, SPACE_UP_MARGIN, 0);

        al_flip_display();
        al_destroy_bitmap(tile);
        if (graphicsData->tiles[index].iAm != room_t::SAFE)
        {
            ALLEGRO_BITMAP* number = loadSafeNumber(graphicsData->tiles[index].combinationNumber, true);
            al_draw_bitmap(number, (DISPLAYW - SPACE_DIVIDER_L - CARD_SELECTED_SIZE)*2 + SPACE_DIVIDER_L - 17, SPACE_UP_MARGIN + CARD_SELECTED_SIZE / 2 + 3, 0);
            al_destroy_bitmap(number);
        }
    }
    return;
}

void
View::writeSelectedTileInfo()
{
    std::string c, r, f, tile;
    unsigned col, row, floor;
    col = getColumn((location_t) graphicsData->currentCardSelected);
    row = getRow((location_t) graphicsData->currentCardSelected);
    floor = getFloor((location_t) graphicsData->currentCardSelected);
    switch (col)
    {
        case 0: c = "A";
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

    return;
}

void
View::showNoCardSelected() //cambiar
{
    al_draw_text(textFont, al_map_rgb(0, 0, 0), (DISPLAYW - SPACE_DIVIDER_L) / 2 + SPACE_DIVIDER_L, 0, ALLEGRO_ALIGN_CENTER, "No Card or Loot Selected");
    return;
}

void
View::drawSelectedTileTokens()
{
    unsigned tokenCount = 0, x, y;
    for (unsigned j = 0; j < 2; j++)
    {
        for (unsigned i = 0; i < 4; i++)
        {
            al_flip_display();
            x = i * (TOKENS_BIG_SIZE + SPACE_TOKEN_LR) + SPACE_DIVIDER_L + SPACE_TOKEN_LR;
            y = j * (TOKENS_BIG_SIZE + SPACE_TOKEN_UD) + SPACE_UP_MARGIN + CARD_SELECTED_SIZE + SPACE_TOKEN_UD;
            if (graphicsData->tiles[(int) graphicsData->currentCardSelected].tokens[tokenCount])
            {
                if (tokenCount == (int) token_t::HACKTOKEN || tokenCount == (int) token_t::STEALTHTOKEN)
                {
                    tokenCount++;
                    continue;
                }
                ALLEGRO_BITMAP* token = loadToken((token_t) tokenCount, false);
                al_draw_bitmap(token, x, y, 0);
                al_destroy_bitmap(token);
            }
            tokenCount++;
        }

    }

    if (graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm == room_t::LAVATORY)
    {
        x = 3 * (TOKENS_BIG_SIZE + SPACE_TOKEN_LR) + SPACE_DIVIDER_L + SPACE_TOKEN_LR;
        y = SPACE_UP_MARGIN + CARD_SELECTED_SIZE + SPACE_TOKEN_UD;
        ALLEGRO_BITMAP* token = loadToken(token_t::STEALTHTOKEN, false);
        al_draw_bitmap(token, x, y, 0);
        al_destroy_bitmap(token);
        al_draw_textf(textFont, al_map_rgb(0, 0, 0), x + TOKENS_BIG_SIZE + 5, y, ALLEGRO_ALIGN_LEFT, "x%d", graphicsData->tiles[(int) graphicsData->currentCardSelected].howManyStealthTokens);
    }

    if (graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm == room_t::CR_FINGERPRINT
            || graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm == room_t::CR_LASER
            || graphicsData->tiles[(int) graphicsData->currentCardSelected].iAm == room_t::CR_MOTION)
    {
        x = 3 * (TOKENS_BIG_SIZE + SPACE_TOKEN_LR) + SPACE_DIVIDER_L + SPACE_TOKEN_LR;
        y = 1 * (TOKENS_BIG_SIZE + SPACE_TOKEN_UD) + SPACE_UP_MARGIN + CARD_SELECTED_SIZE + SPACE_TOKEN_UD;
        ALLEGRO_BITMAP* token = loadToken(token_t::HACKTOKEN, false);
        al_draw_bitmap(token, x, y, 0);
        al_destroy_bitmap(token);
        al_draw_textf(textFont, al_map_rgb(0, 0, 0), x + TOKENS_BIG_SIZE + 5, y, ALLEGRO_ALIGN_LEFT, "x%d", graphicsData->tiles[(int) graphicsData->currentCardSelected].howManyHackTokens);
    }
    return;
}

void
View::drawLootSelectedInfo()
{
    ALLEGRO_BITMAP* loot = NULL;
    if (graphicsData->currentCardSelected == button_t::LOOTF1)
    {
        loot = loadLoot(graphicsData->loots[0], false);
        al_draw_text(textFont, al_map_rgb(0, 0, 0), (DISPLAYW - SPACE_DIVIDER_L) / 2 + SPACE_DIVIDER_L, 0, ALLEGRO_ALIGN_CENTER, "1st Floor Loot");
    }
    else if (graphicsData->currentCardSelected == button_t::LOOTF2)
    {
        loot = loadLoot(graphicsData->loots[1], false);
        al_draw_text(textFont, al_map_rgb(0, 0, 0), (DISPLAYW - SPACE_DIVIDER_L) / 2 + SPACE_DIVIDER_L, 0, ALLEGRO_ALIGN_CENTER, "2nd Floor Loot");
    }
    else
    {
        loot = loadLoot(graphicsData->loots[2], false);
        al_draw_text(textFont, al_map_rgb(0, 0, 0), (DISPLAYW - SPACE_DIVIDER_L) / 2 + SPACE_DIVIDER_L, 0, ALLEGRO_ALIGN_CENTER, "3rd Floor Loot");
    }
    al_draw_bitmap(loot, (DISPLAYW - SPACE_DIVIDER_L - CARD_SELECTED_SIZE) / 2 + SPACE_DIVIDER_L, SPACE_UP_MARGIN, 0);
    al_destroy_bitmap(loot);
    return;
}

void
View::writeActions()
{
    std::string actions[] = {"*Add dice to safe", "*Spend actions to enter tile", "*Hack computer",
        "*Use hack token", "*Offer loot", "*Request loot", "*Pick up loot", "*Create Alarm", "*Spy patrol deck",
        "*Place patrol card on top", "*Place patrol card on bottom", "*Place crow token"};
    float alpha = 0.5f;
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 10 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 3, ALLEGRO_ALIGN_RIGHT, "ACTIONS");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), SPACE_DIVIDER_L + 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, ALLEGRO_ALIGN_LEFT, "*Move");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), SPACE_DIVIDER_L + (DISPLAYW - SPACE_DIVIDER_L) / 2, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, ALLEGRO_ALIGN_CENTER, "*Peek");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 4, ALLEGRO_ALIGN_RIGHT, "*Pass");
    for (unsigned i = 0; i < ((int) action_t::ACTION_COUNT - 8); i++)
    {
        if (actions[i] == actions[(int) action_t::PLACE_CROW_TOKEN - 4] && graphicsData->players[0].character != character_t::RAVEN) //si player one no es Raven, escribo transparente "place crow token"
            al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * (i + 5), ALLEGRO_ALIGN_RIGHT, actions[i].c_str());

        else if (actions[i] == actions[(int) action_t::CREATE_ALARM - 4] && graphicsData->players[0].character != character_t::JUICER) //si player one no es juicer, escribo transparente "create alarm"
            al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * (i + 5), ALLEGRO_ALIGN_RIGHT, actions[i].c_str());

        else if (actions[i] == actions[(int) action_t::SPY_PATROL_DECK - 4] && graphicsData->players[0].character != character_t::SPOTTER) //si player one no es spotter, escribo transparente "spy patrol deck"
            al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * (i + 5), ALLEGRO_ALIGN_RIGHT, actions[i].c_str());

        else if (actions[i] == actions[(int) action_t::PATROL_IS_TOP - 4] && graphicsData->players[0].character != character_t::SPOTTER) //si player one no es spotter, escribo transparente "send patrol to top"
            al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * (i + 5), ALLEGRO_ALIGN_RIGHT, actions[i].c_str());

        else if (actions[i] == actions[(int) action_t::PATROL_IS_BOTTOM - 4] && graphicsData->players[0].character != character_t::SPOTTER) //si player one no es spotter, escribo transparente "send patrol to bottom"
            al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 15 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * (i + 5), ALLEGRO_ALIGN_RIGHT, actions[i].c_str());

        else
            al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * (i + 5), ALLEGRO_ALIGN_RIGHT, actions[i].c_str());
    }

    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 18, ALLEGRO_ALIGN_LEFT, "Accept");
    al_draw_text(smallTextFont, al_map_rgb(0, 0, 0), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 18, ALLEGRO_ALIGN_RIGHT, "Decline");
    if (graphicsData->gameLost == true || graphicsData->gameWon == true)
    {
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 19, ALLEGRO_ALIGN_LEFT, "Play again?");
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), SPACE_DIVIDER_L + 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 20, ALLEGRO_ALIGN_LEFT, "*Yes");
        al_draw_text(smallTextFont, al_map_rgba_f(0.0 * alpha, 0.0 * alpha, 0.0 * alpha, alpha), DISPLAYW - 5, 13 + CARD_SELECTED_SIZE + SPACE_TOKEN_UD * 4 + (TOKENS_BIG_SIZE - 5) * 20, ALLEGRO_ALIGN_RIGHT, "*No");
    }
    return;

}

void
View::writeMessages()
{

    return;
}

ALLEGRO_BITMAP*
View::loadCharacter(character_t c, bool shrink)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (c)
    {
        case character_t::JUICER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/juicersmall.png");
            else
                bitmap = al_load_bitmap("images/character/juicer.png");
            break;

        case character_t::HACKER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/hackersmall.png");
            else
                bitmap = al_load_bitmap("images/character/hacker.png");
            break;

        case character_t::ACROBAT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/acrobatsmall.png");
            else
                bitmap = al_load_bitmap("images/character/acrobat.png");
            break;

        case character_t::SPOTTER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/spottersmall.png");
            else
                bitmap = al_load_bitmap("images/character/spotter.png");
            break;

        case character_t::HAWK:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/hawksmall.png");
            else
                bitmap = al_load_bitmap("images/character/hawk.png");
            break;

        case character_t::RAVEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/ravensmall.png");
            else
                bitmap = al_load_bitmap("images/character/raven.png");
            break;

        case character_t::PETERMAN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/character/petermansmall.png");
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
                bitmap = al_load_bitmap("images/loots/tiarasmall.png");
            else
                bitmap = al_load_bitmap("images/loots/tiara.png");
            break;

        case loot_t::KITTY:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/kittysmall.png");
            else
                bitmap = al_load_bitmap("images/loots/kitty.png");
            break;

        case loot_t::PAINTING:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/paintingsmall.png");
            else
                bitmap = al_load_bitmap("images/loots/painting.png");
            break;

        case loot_t::MIRROR:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/mirrorsmall.png");
            else
                bitmap = al_load_bitmap("images/loots/mirror.png");
            break;

        case loot_t::KEYCARD:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/keycardsmall.png");
            else
                bitmap = al_load_bitmap("images/loots/keycard.png");
            break;

        case loot_t::ISOTOPE:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/isotopesmall.png");
            else
                bitmap = al_load_bitmap("images/loots/isotope.png");
            break;

        case loot_t::GEMSTONE:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/gemstonesmall.png");
            else
                bitmap = al_load_bitmap("images/loots/gemstone.png");
            break;

        case loot_t::GOBLET:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/gobletsmall.png");
            else
                bitmap = al_load_bitmap("images/loots/goblet.png");
            break;

        case loot_t::CHIHUAHUA:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/chihuahuasmall.png");
            else
                bitmap = al_load_bitmap("images/loots/chihuahua.png");
            break;

        case loot_t::GOLD:
            if (shrink == true)
                bitmap = al_load_bitmap("images/loots/goldsmall.png");
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
                bitmap = al_load_bitmap("images/tokens/alarmsmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/alarm.png");
            break;

        case token_t::CROWTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/crowsmall.png");
            else

                bitmap = al_load_bitmap("images/tokens/crow.png");
            break;

        case token_t::HACKTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/hacksmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/hack.png");
            break;

        case token_t::KITTYTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/kittysmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/kitty.png");
            break;

        case token_t::OPENTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/opensmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/open.png");
            break;

        case token_t::CRACKEDTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/safesmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/safe.png");
            break;

        case token_t::DOWNSTAIRSTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/stairssmall.png");
            else
                bitmap = al_load_bitmap("images/tokens/stairs.png");
            break;

        case token_t::STEALTHTOKEN:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tokens/stealthsmall.png");
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
                bitmap = al_load_bitmap("images/tiles/atriumsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/atrium.png");
            break;

        case room_t::CAMERA:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/camerasmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/camera.png");
            break;

        case room_t::CR_FINGERPRINT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/CRFingerprintsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/CRFingerprint.png");
            break;

        case room_t::CR_LASER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/CRLasersmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/CRLaser.png");
            break;

        case room_t::CR_MOTION:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/CRMotionsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/CRMotion.png");
            break;

        case room_t::DEADBOLT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/deadboltsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/deadbolt.png");
            break;

        case room_t::DETECTOR:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/detectorsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/detector.png");
            break;

        case room_t::FINGERPRINT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/fingerprintsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/fingerprint.png");
            break;

        case room_t::FOYER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/foyersmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/foyer.png");
            break;

        case room_t::KEYPAD:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/keypadsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/keypad.png");
            break;

        case room_t::LABORATORY:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/laboratorysmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/laboratory.png");
            break;

        case room_t::LASER:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/lasersmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/laser.png");
            break;

        case room_t::LAVATORY:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/lavatorysmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/lavatory.png");
            break;

        case room_t::MOTION:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/motionsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/motion.png");
            break;

        case room_t::ROOMBACK:
            bitmap = al_load_bitmap("images/tiles/roomBack.png");
            break;

        case room_t::SAFE:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/safesmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/safe.png");
            break;

        case room_t::SECRETDOOR:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/secretDoorsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/secretDoor.png");
            break;

        case room_t::SERVICEDUCT:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/serviceDuctsmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/serviceDuct.png");
            break;

        case room_t::STAIRS:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/stairssmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/stairs.png");
            break;

        case room_t::THERMO:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/thermosmall.png");
            else
                bitmap = al_load_bitmap("images/tiles/thermo.png");
            break;

        case room_t::WALKWAY:
            if (shrink == true)
                bitmap = al_load_bitmap("images/tiles/walkwaysmall.png");
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
View::loadGuardDie(unsigned number)
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

ALLEGRO_BITMAP*
View::loadSafeDie(unsigned number)
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

ALLEGRO_BITMAP*
View::loadSafeNumber(unsigned s, bool shrink)
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




