#include "constants.h"

const int GAME_WIDTH = 1915;
const int GAME_HEIGHT = 1000;
const int FPS = 60;
const int MAXNO_BULLETS = 1000;
const int MAXNO_ENEMIES = 1000;
const int MAXNO_EXPS = 100;
const int MAXNO_BULLET_IMGS = 10;
ALLEGRO_TIMER *loading_timer = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_DISPLAY *display = NULL;
bool TEST_MODE = false;

const int menu_FPS = 15;
int window = 1;
int status = 1;
ALLEGRO_TIMER *menu_timer = NULL;
ALLEGRO_TIMER *game_timer = NULL;
ALLEGRO_TIMER *buff_timer = NULL;
bool running = true;
bool judge_next_window = false;
bool redraw = false;
bool generatebuff = false;
bool buff_show = false;

int buffX = 0;
int buffY = 0;
int buffRadius = 75;
int buffType = 0;

bool key_state[ALLEGRO_KEY_MAX] = {false};
