#include "game.h"

void Game_init(Game *game)
{
    game->background = New_Background("./image/stars.jpg");
    Player_init(&(game->player));

    game->enemy_count = 0;
    game->enemies = (Enemy**)malloc(MAXNO_ENEMIES * sizeof(Enemy*));

    game->exp_count = 0;
    game->exps = (Explosion**)malloc(MAXNO_EXPS * sizeof(Explosion*));

    game->curLevel = 1;
    game->levelTimer = al_create_timer(3); // level delay for 3 secs
    al_start_timer(game->levelTimer);
    game->event_queue = al_create_event_queue();
    al_register_event_source(game->event_queue, al_get_timer_event_source(game->levelTimer));

    //game->font = al_create_builtin_font();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    game->font = al_load_ttf_font("font/pirulen.ttf", 50, 0);

    game->BGM = al_load_audio_stream("music/bgm2.mp3", 2, 2048);
    al_set_audio_stream_playmode(game->BGM, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playing(game->BGM, true);
    al_attach_audio_stream_to_mixer(game->BGM, al_get_default_mixer());

    game->levelPassMusic = al_load_audio_stream("music/level-pass.mp3", 2, 2048);
    game->endingMusic = al_load_audio_stream("music/ending.mp3", 2, 2048);
    //al_set_audio_stream_playmode(game->levelPassMusic, ALLEGRO_PLAYMODE_ONCE);
    //al_set_audio_stream_playing(game->levelPassMusic, true);
    //al_attach_audio_stream_to_mixer(game->levelPassMusic, al_get_default_mixer());

    game->playerGetHitSound = al_load_sample("music/playerGetHitSound.mp3");
    game->enemyGetHitSound = al_load_sample("music/enemyGetHitSound.mp3");
    game->playerDeadSound = al_load_sample("music/playerDeadSound.mp3");
    game->enemyDeadSound = al_load_sample("music/enemyDeadSound.mp3");

    game->gameOver = false;
    game->gamePass = false;

    game_timer_init();
    buff_init();

    Enemy_loadImages();
    Bullet_loadImages();
    // Explosion_loadGIF();

    game->endingScene = al_load_bitmap("image/ending.jpg");
}

void Game_update(Game *game)
{
    if(game->gameOver || game->gamePass){
        return;
    }

    // Funny effect after kill the last enemy
    for(int i = 0; i < game->exp_count; i++){
        Explosion *exp = game->exps[i];
        Explosion_update(exp);
    }

    Player_update(&(game->player));
    if(al_get_timer_started(game->levelTimer)){
        // Show current level
        ALLEGRO_EVENT event;
        if(al_get_next_event(game->event_queue, &event)){
            al_stop_timer(game->levelTimer);
            if(game->enemy_count == 0) {
                switch(game->curLevel){
                    case 1:
                        for(int i = 0; i < 5; ++i){
                            //if (game->enemy_count < MAXNO_ENEMIES) {
                                Enemy* enemy = malloc(sizeof(Enemy));
                                Enemy_init(enemy, 1);

                                game->enemies[game->enemy_count++] = enemy;
                            //}
                        }
                        for(int i = 0; i < 5; ++i){
                            Enemy* enemy = malloc(sizeof(Enemy));
                            Enemy_init(enemy, 2);
                            game->enemies[game->enemy_count++] = enemy;
                        }
                        break;
                    case 2:
                        for(int i = 0; i < 10; ++i){
                            Enemy* enemy = malloc(sizeof(Enemy));
                            Enemy_init(enemy, 2);
                            game->enemies[game->enemy_count++] = enemy;

                        }
                        for(int i = 0; i < 5; ++i){
                            Enemy* enemy = malloc(sizeof(Enemy));
                            Enemy_init(enemy, 3);
                            game->enemies[game->enemy_count++] = enemy;
                        }
                        break;
                    case 3:
                        for(int i = 0; i < 3; ++i){
                            Enemy* enemy = malloc(sizeof(Enemy));
                            Enemy_init(enemy, 3);
                            game->enemies[game->enemy_count++] = enemy;
                        }
                        for(int i = 0; i < 5; ++i){
                            Enemy* enemy = malloc(sizeof(Enemy));
                            Enemy_init(enemy, 4);
                            enemy->radius = 75;
                            game->enemies[game->enemy_count++] = enemy;
                        }
                        break;
                    case 4:
                        for(int i = 0; i < 1; ++i){
                            Enemy* enemy = malloc(sizeof(Enemy));
                            Enemy_init(enemy, 4);
                            enemy->radius = 70;
                            game->enemies[game->enemy_count++] = enemy;
                        }
                        for(int i = 0; i < 1; ++i){
                            Enemy* enemy = malloc(sizeof(Enemy));
                            Enemy_init(enemy, 5);
                            enemy->radius = 70;
                            game->enemies[game->enemy_count++] = enemy;
                        }
                        break;
                    case 5:
                        for(int i = 0; i < 2; ++i){
                            Enemy* enemy = malloc(sizeof(Enemy));
                            Enemy_init(enemy, 6);
                            enemy->radius = 70;
                            game->enemies[game->enemy_count++] = enemy;
                        }
                        break;
                    default:
                        break;
                }
                game->curLevel++;
                if(game->curLevel == 7){
                    game->gamePass = true;
                }

                if(game->curLevel > 1){
                    game->levelupMusicFlag = true;
                }

            }
        }
    }

    background_update(game->background);

    for(int i = 0; i < game->enemy_count; i++){
        Enemy *enemy = game->enemies[i];
        Enemy_update(enemy, Player_getX(&(game->player)), Player_getY(&(game->player)));
    }

    // Detect collision between bullets and enemies
    for(int i = 0; i < (game->player).bullet_count; i++){
        Bullet *bullet = game->player.bullets[i];
        float bx = Bullet_getX(bullet);
        float by = Bullet_getY(bullet);
        float br = Bullet_getRadius(bullet);
        for(int j = 0; j < game->enemy_count; j++){
            Enemy *enemy = game->enemies[j];
            float ex = Enemy_getX(enemy);
            float ey = Enemy_getY(enemy);
            float er = Enemy_getRadius(enemy);
            if(Game_collide(bx, by, br, ex, ey, er)){
                // Decrease enemy's hp
                Enemy_isHit(enemy);
                al_play_sample(Enemy_isDead(enemy)? game->enemyDeadSound: game->enemyGetHitSound,
                               1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &game->enemyDeadID);
                // kill the bullet (from exist to non-exist)
                Bullet_kill(bullet);
            }
        }
    }

    // Detect collision between player and enemies
    if(!Player_isRecovering(&(game->player))){
        for(int i = 0; i < game->enemy_count; i++){
            Enemy *enemy = game->enemies[i];
            float ex = Enemy_getX(enemy);
            float ey = Enemy_getY(enemy);
            float er = Enemy_getRadius(enemy);
            float px = Player_getX(&(game->player));
            float py = Player_getY(&(game->player));
            float pr = Player_getRadius(&(game->player));
            if(!Enemy_isRecovering(enemy)){
                if(Game_collide(ex, ey, er, px, py, pr)){
                    // Decrease player's enemy's hp
                    Player_isHit(&(game->player));

                    al_play_sample(Player_getHp(&game->player)==0 && !TEST_MODE ?
                                   game->playerDeadSound:game->playerGetHitSound,
                                   1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &game->playerDeadID);
                    Enemy_isHit(enemy);

                    if(Player_getHp(&(game->player)) == 0 && !TEST_MODE){
                        game->gameOver = true;
                    }
                }
            }
        }
    }

    // Detect collision between player and bullets
    if(!Player_isRecovering(&(game->player))){
        for(int i = 0; i < game->enemy_count; i++){
            Enemy *enemy = game->enemies[i];
            for(int j = 0; j < enemy->bullet_count; ++j){
                float bx = Bullet_getX(enemy->bullets[j]);
                float by = Bullet_getY(enemy->bullets[j]);
                float br = Bullet_getRadius(enemy->bullets[j]);
                float px = Player_getX(&(game->player));
                float py = Player_getY(&(game->player));
                float pr = Player_getRadius(&(game->player));
                if(Game_collide(bx, by, br, px, py, pr)){
                    // Decrease player's enemy's hp
                    Player_isHit(&(game->player));
                    al_play_sample(Player_getHp(&game->player)==0 && !TEST_MODE?game->playerDeadSound:game->playerGetHitSound,
                                   1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &game->playerDeadID);
                    Bullet_kill(enemy->bullets[j]);
                    if(Player_getHp(&(game->player)) == 0 && !TEST_MODE){
                        game->gameOver = true;
                    }
                }
            }
        }
    }

    // Detection between players and buffs
    float bx = buffX;
    float by = buffY;
    float br = buffRadius;
    float px = Player_getX(&(game->player));
    float py = Player_getY(&(game->player));
    float pr = Player_getRadius(&(game->player));
    if(Game_collide(bx, by, br, px, py, pr)){
        buff_update();
        switch( buffType )
        {
        case 0:
            //bulletspeedUp += 10;
            Player_onFire(&(game->player));
            break;
        case 1:
            Player_speedUp(&(game->player));
            break;
        case 2:
            Player_hpAdd(&(game->player));
            break;
        case 3:
            Player_hpMinus(&(game->player));
            if(Player_getHp(&(game->player)) == 0 && !TEST_MODE){
                    game->gameOver = true;
            }
            break;
        case 4:
            Player_bigger(&(game->player));
            break;
        }
    }

    // Remove dead enemies
    int enemy_index = 0;
    for (int i = 0; i < game->enemy_count; ++i) {
        Enemy *enemy = game->enemies[i];
        if (Enemy_isDead(enemy)) {
            Explosion *exp = malloc(sizeof(Explosion));
            Explosion_init(exp, Enemy_getX(enemy), Enemy_getY(enemy), Enemy_getRadius(enemy), Enemy_getColor(enemy));
            game->exps[game->exp_count++] = exp;
            free(enemy);
        } else {
            game->enemies[enemy_index++] = enemy;
        }
    }
    game->enemy_count = enemy_index;

    // Remove dead explosion
    int exp_index = 0;
    for(int i = 0; i < game->exp_count; ++i){
        Explosion *exp = game->exps[i];
        if(Explosion_remove(exp)){
            free(exp);
        }else{
            game->exps[exp_index++] = exp;
        }
    }
    game->exp_count = exp_index;

    if(game->enemy_count == 0) al_start_timer(game->levelTimer);

}

void Game_handleInput(Game *game)
{
    if(game->gameOver || game->gamePass){
        // Wait for input
        al_get_keyboard_state(&(game->key_state));
        // Back to menu
        if(al_key_down(&(game->key_state), ALLEGRO_KEY_Z)){
            game->gameOver = false;
            game->gamePass = false;
            Player_destroy(&(game->player));
            //Player_init(&(game->player));
            al_set_audio_stream_playing(game->endingMusic, false);
            menu_init();
            window = 1; status = 1;
            game->curLevel = 1;

            for(int i = 0; i < game->enemy_count; ++i){
                Enemy *enemy = game->enemies[i];
                Enemy_destroy(enemy);
                free(enemy);
            }
            free(game->enemies);
            /*
            for(int i = 0; i < game->exp_count; ++i){
                Explosion *exp = game->exps[i];
                Explosion_destroy(exp);
                free(exp);
            }
            free(game->exps);
            */
            al_flush_event_queue(game->event_queue);
        }
    }
    Player_handleInput(&(game->player));
}

void Game_draw(Game *game)
{
    if(game->gameOver){
        buff_show = false;
        al_set_audio_stream_playing(game->BGM, false);
        // Draw game over text
        al_draw_textf(game->font, al_map_rgb(255, 255, 255), GAME_WIDTH/2, GAME_HEIGHT/2,
              ALLEGRO_ALIGN_CENTER, "%s", "Game Over! Press Z to menu.");
        return;
    }

    if(game->gamePass) {

        al_set_audio_stream_playmode(game->endingMusic, ALLEGRO_PLAYMODE_LOOP);
        al_set_audio_stream_playing(game->endingMusic, true);
        al_attach_audio_stream_to_mixer(game->endingMusic, al_get_default_mixer());
        game->levelupMusicFlag = false;

        buff_show = false;
        al_set_audio_stream_playing(game->BGM, false);
        // Draw ending scene
        al_draw_scaled_bitmap(game->endingScene, 0, 0,al_get_bitmap_width(game->endingScene),
                      al_get_bitmap_height(game->endingScene),0, 0, GAME_WIDTH, GAME_HEIGHT, 0);
        al_draw_textf(game->font, al_map_rgb(255, 255, 255), GAME_WIDTH/2, GAME_HEIGHT/2,
              ALLEGRO_ALIGN_CENTER, "%s", "You win! Frank finally found his carer^_^");
        al_draw_textf(game->font, al_map_rgb(255, 255, 255), GAME_WIDTH/2, GAME_HEIGHT/2+150,
              ALLEGRO_ALIGN_CENTER, "%s", "Press Z to menu.");

        return;
    }


    background_draw(game->background);
    Player_draw(&(game->player));

    for(int i = 0; i < game->enemy_count; i++){
        Enemy *enemy = game->enemies[i];
        Enemy_draw(enemy);
    }

    for(int i = 0; i < game->exp_count; ++i){
        Explosion *exp = game->exps[i];
        Explosion_draw(exp);
    }

    // Draw the level banner
    if(al_get_timer_started(game->levelTimer)){
        if(game->curLevel < 6){
            al_draw_textf(game->font, al_map_rgb(255, 255, 255), GAME_WIDTH/2, GAME_HEIGHT/2,
                          ALLEGRO_ALIGN_CENTER, "Level %i", game->curLevel);
        }
        if(game->curLevel > 1 && game->curLevel < 7 && game->levelupMusicFlag){
            al_set_audio_stream_playmode(game->levelPassMusic, ALLEGRO_PLAYMODE_ONCE);
            al_set_audio_stream_playing(game->levelPassMusic, true);
            al_attach_audio_stream_to_mixer(game->levelPassMusic, al_get_default_mixer());
            al_set_audio_stream_gain(game->levelPassMusic, 0.3); // Range: 0.0 (min) to 1.0 (max)
            game->levelupMusicFlag = false;
         }
    }

    // Draw game timer
    game_timer_draw();

}

void Game_destroy(Game *game)
{
    background_destroy(game->background);
    Player_destroy(&(game->player));
    al_destroy_audio_stream(game->BGM);
    al_destroy_audio_stream(game->levelPassMusic);
    al_destroy_audio_stream(game->endingMusic);

    game_timer_destroy();
    buff_destroy();

    for(int i = 0; i < game->enemy_count; i++){
        Enemy *enemy = game->enemies[i];
        Enemy_destroy(enemy);
        free(enemy);
    }
    free(game->enemies);

    for(int i = 0; i < game->exp_count; ++i){
        Explosion *exp = game->exps[i];
        Explosion_destroy(exp);
        free(exp);
    }
    free(game->exps);

    al_destroy_timer(game->levelTimer);
    al_destroy_font(game->font);

    al_destroy_sample(game->playerGetHitSound);
    al_destroy_sample(game->playerDeadSound);
    al_destroy_sample(game->enemyGetHitSound);
    al_destroy_sample(game->enemyDeadSound);

    Enemy_destroyImages();
    Bullet_destroyImages();

    al_destroy_bitmap(game->endingScene);
}

bool Game_collide(float x1, float y1, float r1, float x2, float y2, float r2){
    float distX = x1 - x2;
    float distY = y1 - y2;
    float dist = sqrt(distX * distX + distY * distY);

    if(dist <= r1 + r2){
        return true;
    }else{
        return false;
    }
}
