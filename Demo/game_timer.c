#include "game_timer.h"

ALLEGRO_FONT *timer_font = NULL;
float gt;

void game_timer_init()
{
    gt = 0.0f;
    timer_font = al_load_ttf_font("./font/pirulen.ttf",50,0);
    al_start_timer(game_timer);
}

void game_timer_draw()
{
    gt += 1.0f / 60;
    //al_draw_filled_rectangle(0, 0, 250, 125, al_map_rgb(0,0,0));
    al_draw_textf(timer_font, al_map_rgb(255, 255, 255), GAME_WIDTH-425, 40, 0, "Time: %.2f", gt);
}

void game_timer_destroy()
{
    al_destroy_timer(game_timer);
    al_destroy_display(timer_font);
}
