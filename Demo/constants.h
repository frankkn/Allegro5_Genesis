#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define debug(x) if(x){printf("check at line number %d in file %s\n", __LINE__, __FILE__);}
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include "algif5/algif.h"

extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;
extern const int FPS;
extern const int MAXNO_BULLETS;
extern const int MAXNO_ENEMIES;
extern const int MAXNO_EXPS;
extern const int MAXNO_BULLET_IMGS;

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_TIMER *loading_timer ;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT_QUEUE *event_queue;

extern bool TEST_MODE;

extern const int menu_FPS;
extern int window;
extern int status;
extern ALLEGRO_TIMER *menu_timer;
extern ALLEGRO_TIMER *game_timer;
extern ALLEGRO_TIMER *buff_timer;
extern bool running;
extern bool redraw;
extern bool judge_next_window;
extern bool generatebuff;
extern bool buff_show;

extern int buffX;
extern int buffY;
extern int buffRadius;
extern int buffType;

extern bool key_state[ALLEGRO_KEY_MAX];

#endif
