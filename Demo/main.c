#include "constants.h"
#include "game.h"

int main(){
    srand(time(0));

    if (!al_init())
        return -1;

    display = al_create_display(GAME_WIDTH, GAME_HEIGHT);
    al_set_window_position(display, 0, 0);

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));

    loading_timer = al_create_timer(3);
    timer = al_create_timer(1.0 / FPS);
    menu_timer = al_create_timer(1.0 / menu_FPS);
    game_timer = al_create_timer(1.0 / 60); // time
    buff_timer = al_create_timer(7.0); // Randomly generate a buff every 7 secs

    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();

    al_register_event_source(event_queue, al_get_timer_event_source(loading_timer));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(menu_timer));
    al_register_event_source(event_queue, al_get_timer_event_source(game_timer));
    al_register_event_source(event_queue, al_get_timer_event_source(buff_timer));

    ALLEGRO_FONT* font = al_load_ttf_font("font/pirulen.ttf", 50, 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), GAME_WIDTH/2-180, GAME_HEIGHT/2,
                  0, "Loading");
    al_flip_display();

    al_reserve_samples(10);

    //bool running = true;
    //bool redraw = true;

    Game game;
    //Game_init(&game);
    menu_init();

    al_start_timer(timer);
    al_start_timer(menu_timer);

    Explosion_loadGIF();

    while (running){
        if( redraw ){
            if( window == 1 ){
                menu_draw();
            }else if( window == 2 ){
                draw(&game);
                buff_draw();
            }else if( window == 3 ){
                about_draw();
            }
            al_flip_display();
            redraw = false;
        }
        if( !al_is_event_queue_empty(event_queue) ){
            ALLEGRO_EVENT event;
            al_wait_for_event(event_queue, &event);

            if( window == 1 ){
                menu_process(event);
            }else if( window == 2 ){
                handleInput(&game);
            }else if( window == 3 ){
                about_process(event);
            }

            switch (event.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;

            case ALLEGRO_EVENT_TIMER:
                if( (window == 1 || window == 3)  && event.timer.source == menu_timer )
                    redraw = true;
                else if( window == 2 && event.timer.source == timer)
                    redraw = true;
                else if( event.timer.source == buff_timer ){
                    generatebuff = true;
                    buff_show = true;
                }
                break;
            }

            if(redraw){
                if( judge_next_window ){
                    switch( status ){
                    case 1:
                        about_destroy();
                        menu_init();
                        window = 1;
                        break;
                    case 2:
                        menu_destroy();
                        Game_init(&game);
                        window = 2;
                        break;
                    case 3:
                        menu_destroy();
                        about_init();
                        window = 3;
                        break;
                    }
                    judge_next_window = false;
                }
                if( window == 1 ){
                    choose_update();
                }else if( window == 2 ){
                    update(&game);
                }else if( window == 3 ){
                    about_update();
                }
            }
        }
    }
    /*
    while (running){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        switch (event.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;

            case ALLEGRO_EVENT_TIMER:
                handleInput(&game);
                update(&game);
                redraw = true;
                break;
        }
        if (redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            draw(&game);
        }
    }
    */

    destroy(&game);
    return 0;
}

void update(Game *game){
    Game_update(game);
}

void draw(Game *game){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Game_draw(game);
    //al_flip_display();
}

void handleInput(Game *game){
    Game_handleInput(game);
}

void destroy(Game *game){
    Game_destroy(game);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    al_destroy_timer(menu_timer);
    al_destroy_timer(buff_timer);
    menu_destroy();
    about_destroy();
}
