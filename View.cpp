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
                        this->background = al_load_bitmap("background.jpg");
                        if (this->background != NULL)
                        {
                            this->backgroundWidth = al_get_bitmap_width(this->background);
                            this->backgroundHeight = al_get_bitmap_height(this->background);
                            al_draw_scaled_bitmap(this->background, 0, 0, this->backgroundWidth, this->backgroundHeight, 0, 0, this->width, this->height, 0); //dibujo fondo

                            this->textFont = al_load_ttf_font("Bellota-Bold.otf", 20, 0);
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
                                                this->titleFont = al_load_ttf_font("Bellota-Bold.otf", 80, 0);
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

    this->buttons = new std::vector<bitmap_t>;
    for (unsigned i = 0; i < (int) button::BUTTON_COUNT; ++i)
        buttons.push_back(bitmap_t());

    this->images = new std::vector<ALLEGRO_BITMAP>;
    for (unsigned i = 0; i < (int) image::IMAGE_COUNT; ++i)
        buttons.push_back(ALLEGRO_BITMAP());

    //this->buttons = (bitmap_t*) malloc(sizeof (bitmap_t) * BUTTON_COUNT);

    initUtilities(this->buttons);

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

    images->clear();
    delete images;

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
    al_draw_bitmap(this->buttons[TEST].image, this->buttons[TEST].x, this->buttons[TEST].y, 0); //dibujo boton single player
    al_draw_text(this->titleFont, al_map_rgb(143, 91, 3), 545, 30, ALLEGRO_ALIGN_CENTRE, "Lu esta pelotuda");

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



