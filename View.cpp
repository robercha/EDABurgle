#include "View.h"

//typedef enum
//{
//    HOMESCREEN, SETTINGSSCREEN, HELPSCREEN, PLAYINGSCREEN, CREDITSSCREEN, SCREENCOUNT
//} screen_t;

//carga botones
static void initUtilities(bitmap_t*);

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
                            al_draw_scaled_bitmap(this->background, 0, 0, this->backgroundWidth, this->backgroundHeight, 0, 0, this->width, this->height, 0); //dibujo fondo

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

ALLEGRO_BITMAP*
View::loadCharacter(character_t c)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (c)
    {
        case character_t::JUICER:
            bitmap = al_load_bitmap("images/character/juicer.png");
            break;

        case character_t::HACKER:
            bitmap = al_load_bitmap("images/character/hacker.png");
            break;

        case character_t::ACROBAT:
            bitmap = al_load_bitmap("images/character/acrobat.png");
            break;

        case character_t::SPOTTER:
            bitmap = al_load_bitmap("images/character/spotter.png");
            break;

        case character_t::HAWK:
            bitmap = al_load_bitmap("images/character/hawk.png");
            break;

        case character_t::RAVEN:
            bitmap = al_load_bitmap("images/character/raven.png");
            break;

        case character_t::PETERMAN:
            bitmap = al_load_bitmap("images/character/peterman.png");
            break;

        case character_t::GUARD:
            bitmap = al_load_bitmap("images/character/guard.png");
            break;
    }

    return bitmap;

}

ALLEGRO_BITMAP*
View::loadLoot(loot_t l)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (l)
    {
        case loot_t::TIARA:
            bitmap = al_load_bitmap("images/loots/tiara.png");
            break;

        case loot_t::KITTY:
            bitmap = al_load_bitmap("images/loots/kitty.png");
            break;

        case loot_t::PAINTING:
            bitmap = al_load_bitmap("images/loots/painting.png");
            break;

        case loot_t::MIRROR:
            bitmap = al_load_bitmap("images/loots/mirror.png");
            break;

        case loot_t::KEYCARD:
            bitmap = al_load_bitmap("images/loots/keycard.png");
            break;

        case loot_t::ISOTOPE:
            bitmap = al_load_bitmap("images/loots/isotope.png");
            break;

        case loot_t::GEMSTONE:
            bitmap = al_load_bitmap("images/loots/gemstone.png");
            break;

        case loot_t::GOBLET:
            bitmap = al_load_bitmap("images/loots/goblet.png");
            break;

        case loot_t::CHIHUAHUA:
            bitmap = al_load_bitmap("images/loots/chihuahua.png");
            break;

        case loot_t::GOLD:
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
View::loadToken(token_t t)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (t)
    {
        case token_t::ALARMTOKEN:
            bitmap = al_load_bitmap("images/tokens/alarm.png");
            break;

        case token_t::CROWTOKEN:
            bitmap = al_load_bitmap("images/tokens/crow.png");
            break;

        case token_t::HACKTOKEN:
            bitmap = al_load_bitmap("images/tokens/hack.png");
            break;

        case token_t::KITTYTOKEN:
            bitmap = al_load_bitmap("images/tokens/kitty.png");
            break;

        case token_t::OPENTOKEN:
            bitmap = al_load_bitmap("images/tokens/open.png");
            break;

        case token_t::CRACKEDTOKEN:
            bitmap = al_load_bitmap("images/tokens/safe.png");
            break;

        case token_t::DOWNSTAIRSTOKEN:
            bitmap = al_load_bitmap("images/tokens/stairs.png");
            break;

        case token_t::STEALTHTOKEN:
            bitmap = al_load_bitmap("images/tokens/stealth.png");
            break;
    }
    return bitmap;
}

ALLEGRO_BITMAP*
View::loadRoom(room_t r)
{
    ALLEGRO_BITMAP* bitmap = NULL;
    switch (r)
    {
        case room_t::ATRIUM:
            bitmap = al_load_bitmap("images/tiles/atrium.png");
            break;

        case room_t::CAMERA:
            bitmap = al_load_bitmap("images/tiles/camera.png");
            break;

        case room_t::CR_FINGERPRINT:
            bitmap = al_load_bitmap("images/tiles/CRFingerprint.png");
            break;

        case room_t::CR_LASER:
            bitmap = al_load_bitmap("images/tiles/CRLaser.png");
            break;

        case room_t::CR_MOTION:
            bitmap = al_load_bitmap("images/tiles/CRMotion.png");
            break;

        case room_t::DEADBOLT:
            bitmap = al_load_bitmap("images/tiles/deadbolt.png");
            break;

        case room_t::DETECTOR:
            bitmap = al_load_bitmap("images/tiles/detector.png");
            break;

        case room_t::FINGERPRINT:
            bitmap = al_load_bitmap("images/tiles/fingerprint.png");
            break;

        case room_t::FOYER:
            bitmap = al_load_bitmap("images/tiles/foyer.png");
            break;

        case room_t::KEYPAD:
            bitmap = al_load_bitmap("images/tiles/keypad.png");
            break;

        case room_t::LABORATORY:
            bitmap = al_load_bitmap("images/tiles/laboratory.png");
            break;

        case room_t::LASER:
            bitmap = al_load_bitmap("images/tiles/laser.png");
            break;

        case room_t::LAVATORY:
            bitmap = al_load_bitmap("images/tiles/lavatory.png");
            break;

        case room_t::MOTION:
            bitmap = al_load_bitmap("images/tiles/motion.png");
            break;

        case room_t::ROOMBACK:
            bitmap = al_load_bitmap("images/tiles/roomBack.png");
            break;

        case room_t::SAFE:
            bitmap = al_load_bitmap("images/tiles/safe.png");
            break;

        case room_t::SECRETDOOR:
            bitmap = al_load_bitmap("images/tiles/secretDoor.png");
            break;

        case room_t::SERVICEDUCT:
            bitmap = al_load_bitmap("images/tiles/serviceDuct.png");
            break;

        case room_t::STAIRS:
            bitmap = al_load_bitmap("images/tiles/stairs.png");
            break;

        case room_t::THERMO:
            bitmap = al_load_bitmap("images/tiles/thermo.png");
            break;

        case room_t::WALKWAY:
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
View::loadSafeNumber(safe_t s)
{

    ALLEGRO_BITMAP* bitmap = NULL;
    switch (s)
    {
        case safe_t::NUMBER1:
            bitmap = al_load_bitmap("images/tiles/1.png");
            break;

        case safe_t::NUMBER2:
            bitmap = al_load_bitmap("images/tiles/2.png");
            break;

        case safe_t::NUMBER3:
            bitmap = al_load_bitmap("images/tiles/3.png");
            break;

        case safe_t::NUMBER4:
            bitmap = al_load_bitmap("images/tiles/4.png");
            break;

        case safe_t::NUMBER5:
            bitmap = al_load_bitmap("images/tiles/5.png");
            break;

        case safe_t::NUMBER6:
            bitmap = al_load_bitmap("images/tiles/6.png");
            break;
    }
    return bitmap;
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



