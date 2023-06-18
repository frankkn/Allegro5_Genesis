#include "about.h"

ALLEGRO_FONT *about_font = NULL;
ALLEGRO_BITMAP *about1, *about2, *about3, *about4, *aboutImage;
int aboutStatus;

void about_init()
{
    aboutStatus = 0;
    about_font = al_load_ttf_font("./font/pirulen.ttf", 40,0);
    about1 = al_load_bitmap("./image/about1.jpg");
    about2 = al_load_bitmap("./image/about2.jpg");
    about3 = al_load_bitmap("./image/about3.jpg");
    about4 = al_load_bitmap("./image/about4.jpg");
}

void about_draw()
{
    al_draw_scaled_bitmap(aboutImage, 0, 0,
                          al_get_bitmap_width(aboutImage),
                          al_get_bitmap_height(aboutImage),
                          0, 0, GAME_WIDTH, GAME_HEIGHT, 0);
    al_draw_text(about_font, al_map_rgb(255,255,255), GAME_WIDTH/2, GAME_HEIGHT - 100, ALLEGRO_ALIGN_CENTRE,
                 "Press backspace to return to the menu.");
}

void about_update()
{
    if( key_state[ALLEGRO_KEY_UP] ){
        aboutStatus = (aboutStatus-1+4) % 4;
    }else if( key_state[ALLEGRO_KEY_DOWN] ){
        aboutStatus = (aboutStatus+1) % 4;
    }
    if( key_state[ALLEGRO_KEY_BACKSPACE] ){
        judge_next_window = true;
        status = 1;
    }
    switch(aboutStatus)
    {
    case 0:
        aboutImage = about1;
        break;
    case 1:
        aboutImage = about2;
        break;
    case 2:
        aboutImage = about3;
        break;
    case 3:
        aboutImage = about4;
        break;
    }
}

void about_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
    /*if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE ){
            judge_next_window = true;
            status = 1;
        }*/
}

void about_destroy()
{
    al_destroy_font(about_font);
    al_destroy_bitmap(about1);
    al_destroy_bitmap(about2);
    al_destroy_bitmap(about3);
    al_destroy_bitmap(about4);
    //al_destroy_bitmap(aboutImage);
}
