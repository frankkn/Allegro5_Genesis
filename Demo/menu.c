#include "menu.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *menu_background = NULL, *choose = NULL;
int choose_x, choose_y;

ALLEGRO_AUDIO_STREAM *menuMusic;

void menu_init()
{
    font = al_load_ttf_font("./font/pirulen.ttf",24,0);
    menu_background = al_load_bitmap("./image/background.png");
    choose_init();

    menuMusic = al_load_audio_stream("music/menuMusic.mp3", 2, 2048);
    al_set_audio_stream_playmode(menuMusic, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playing(menuMusic, true);
    al_attach_audio_stream_to_mixer(menuMusic, al_get_default_mixer());
}


void menu_process(ALLEGRO_EVENT event)
{
    // menu -> 1, game scene -> 2, about -> 3;
    choose_process(event);
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            switch(status)
            {
            case 1:
                judge_next_window = true;
                status++; // from menu to game scene
                break;
            case 2:
                judge_next_window = true;
                status++; // from menu to about
                break;
            case 3:
                running = false; // quit
                break;
            }
        // [Cheat code] Only can be turned on/off in menu!
        // Press T to be immortal
        if( event.keyboard.keycode == ALLEGRO_KEY_T ){
            TEST_MODE = !TEST_MODE;
        }
}

void menu_draw()
{
    al_draw_scaled_bitmap(menu_background, 0, 0,
                          al_get_bitmap_width(menu_background),
                          al_get_bitmap_height(menu_background),
                          0, 0, GAME_WIDTH, GAME_HEIGHT, 0);
    al_draw_text(font, al_map_rgb(255,255,255), GAME_WIDTH/2, GAME_HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "start");
    al_draw_text(font, al_map_rgb(255,255,255), GAME_WIDTH/2, GAME_HEIGHT/2+260 , ALLEGRO_ALIGN_CENTRE, "about");
    al_draw_text(font, al_map_rgb(255,255,255), GAME_WIDTH/2, GAME_HEIGHT/2+300 , ALLEGRO_ALIGN_CENTRE, "quit");
    choose_draw();
    if(TEST_MODE) al_draw_filled_circle(GAME_WIDTH/2, GAME_HEIGHT/2, 200, al_map_rgb(255,0,0));
}


void menu_destroy()
{
    al_destroy_font(font);
    al_destroy_bitmap(menu_background);
    choose_destroy();

    al_set_audio_stream_playing(menuMusic, false);
    al_destroy_audio_stream(menuMusic);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void choose_init(){
    choose = al_load_bitmap("./image/choose.png");
    choose_x = GAME_WIDTH/2-100;
    choose_y = GAME_HEIGHT/2+220;
}

void choose_draw(){
    al_draw_scaled_bitmap(choose, 0, 0,
                          al_get_bitmap_width(choose),
                          al_get_bitmap_height(choose),
                          choose_x, choose_y, 30, 30, 0);
}

void choose_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}

void choose_update(){
    if( key_state[ALLEGRO_KEY_UP] ){
        switch(status)
        {
        case 1:
            choose_x = GAME_WIDTH/2-100;
            choose_y = GAME_HEIGHT/2+220;
            break;
        case 2:
            choose_x = GAME_WIDTH/2-100;
            choose_y = GAME_HEIGHT/2+220;
            status--;
            break;
        case 3:
            choose_x = GAME_WIDTH/2-100;
            choose_y = GAME_HEIGHT/2+260;
            status--;
            break;
        }
    }else if( key_state[ALLEGRO_KEY_DOWN] ){
        switch(status)
        {
        case 1:
            choose_x = GAME_WIDTH/2-100;
            choose_y = GAME_HEIGHT/2+260;
            status++;
            break;
        case 2:
            choose_x = GAME_WIDTH/2-100;
            choose_y = GAME_HEIGHT/2+300;
            status++;
            break;
        case 3:
            choose_x = GAME_WIDTH/2-100;
            choose_y = GAME_HEIGHT/2+300;
            break;
        }
    }
}

void choose_destroy(){
    al_destroy_bitmap(choose);
    //al_destroy_timer(menu_FPS);
}
