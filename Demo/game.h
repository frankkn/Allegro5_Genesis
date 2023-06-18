#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "constants.h"
#include "background.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "menu.h"
#include "game_timer.h"

typedef struct _Game
{
    Background *background;
    Player player;

    int enemy_count;
    Enemy ** enemies;
    int exp_count;
    Explosion ** exps;

    bool gameOver;
    bool gamePass;

    int curLevel;
    ALLEGRO_TIMER *levelTimer;
    ALLEGRO_EVENT_QUEUE *event_queue;

    ALLEGRO_FONT *font;
    ALLEGRO_AUDIO_STREAM *BGM;
    bool levelupMusicFlag;
    ALLEGRO_AUDIO_STREAM *levelPassMusic;
    ALLEGRO_AUDIO_STREAM *endingMusic;

    ALLEGRO_SAMPLE *playerGetHitSound;
    ALLEGRO_SAMPLE *enemyGetHitSound;

    ALLEGRO_SAMPLE_ID playerDeadID;

    ALLEGRO_SAMPLE *playerDeadSound;
    ALLEGRO_SAMPLE *enemyDeadSound;

    ALLEGRO_SAMPLE_ID enemyDeadID;

    ALLEGRO_KEYBOARD_STATE key_state;

    ALLEGRO_BITMAP *endingScene;
} Game;

void Game_init(Game *game);
void Game_update(Game *game);
void Game_handleInput(Game *game);
void Game_draw(Game *game);
void Game_destroy(Game *game);
bool Game_collide(float, float, float, float, float, float);

void update(Game *game);
void draw(Game *game);
void handleInput(Game *game);
void destroy(Game *game);

#endif
