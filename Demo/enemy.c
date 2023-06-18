#include "enemy.h"

ALLEGRO_BITMAP *e1, *e2, *e3, *e4, *e5, *e6, *eh1, *eh2, *eh3, *eh4, *eh5, *eh6;
int enemy4angle = 0, enemy5angle = 0;

void Enemy_init(Enemy *enemy, int level){
    enemy->level = level;
    switch (level){
        case 1:
            enemy->speed = 2;
            enemy->hp = 2;
            enemy->color = al_map_rgb_f(1, 0, 0);
            break;
        case 2:
            enemy->speed = 4;
            enemy->hp = 4;
            enemy->color = al_map_rgb_f(0, 1, 0);
            break;
        case 3:
            enemy->speed = 6;
            enemy->hp = 6;
            enemy->color = al_map_rgb_f(0, 0, 1);
            break;
        case 4:
            enemy->speed = 8;
            enemy->hp = 8;
            enemy->color = al_map_rgb_f(1, 0, 1);
            break;
        case 5:
            enemy->speed = 8;
            enemy->hp = 8;
            enemy->color = al_map_rgb_f(0, 1, 1);
            break;
        case 6:
            enemy->speed = 8;
            enemy->hp = 20;
            enemy->color = al_map_rgb_f(0, 1, 1);
            break;
    }
    enemy->radius = 40;
    enemy->x = GAME_WIDTH / 2;
    enemy->y = 100;
    enemy->angle = rand() % 181;
    enemy->dx = cos(enemy->angle) * enemy->speed;
    enemy->dy = sin(enemy->angle) * enemy->speed;
    //enemy->dx = enemy->dy = 0;
    enemy->isOnScreen = false;
    enemy->bullet_count = 0;
    enemy->bullets = (Bullet**)malloc(MAXNO_BULLETS * sizeof(Bullet*));

    enemy->recTimer = al_create_timer(2);
    enemy->event_queue = al_create_event_queue();
    al_register_event_source(enemy->event_queue, al_get_timer_event_source(enemy->recTimer));
}

void Enemy_update(Enemy *enemy, float playerX, float playerY){

    // [BUG(X)Feature(O)] will generate only 1 level-3 enemy
    if(enemy->level == 3){
        enemy->angle = atan2(playerY - enemy->y, playerX - enemy->x);
        enemy->dx = cos(enemy->angle) * enemy->speed;
        enemy->dy = sin(enemy->angle) * enemy->speed;
    }

    enemy->x += enemy->dx;
    enemy->y += enemy->dy;

    if(enemy->x > 0 && enemy->x < GAME_WIDTH) enemy->isOnScreen = true;

    // Check boundary
    if (enemy->x < enemy->radius) // Left boundary
        enemy->dx = -enemy->dx;
    if (enemy->y < enemy->radius) // Top boundary
        enemy->dy = -enemy->dy;
    if (enemy->x + enemy->radius *5 > GAME_WIDTH)
        enemy->dx = -enemy->dx;
    if (enemy->y + enemy->radius *5> GAME_HEIGHT)
        enemy->dy = -enemy->dy;

    ALLEGRO_EVENT event;
    if(al_get_next_event(enemy->event_queue, &event)){
        al_stop_timer(enemy->recTimer);
    }

    if(enemy->level == 4){
        int randomProb = rand() % 100;
        if(randomProb <= 1 && enemy->bullet_count < MAXNO_BULLETS){
            float angle = 30;
            Bullet *bullet = Bullet_create(angle*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet1 = Bullet_create(angle*2*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet2 = Bullet_create(angle*3*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet3 = Bullet_create(angle*4*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet4 = Bullet_create(angle*5*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet5 = Bullet_create(angle*6*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet6 = Bullet_create(angle*7*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet7 = Bullet_create(angle*8*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet8 = Bullet_create(angle*9*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet9 = Bullet_create(angle*10*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet10 = Bullet_create(angle*11*3.1415/180, enemy->x, enemy->y, enemy->level);
            Bullet *bullet11 = Bullet_create(angle*12*3.1415/180, enemy->x, enemy->y, enemy->level);
            enemy->bullets[enemy->bullet_count++] = bullet;
            enemy->bullets[enemy->bullet_count++] = bullet1;
            enemy->bullets[enemy->bullet_count++] = bullet2;
            enemy->bullets[enemy->bullet_count++] = bullet3;
            enemy->bullets[enemy->bullet_count++] = bullet4;
            enemy->bullets[enemy->bullet_count++] = bullet5;
            enemy->bullets[enemy->bullet_count++] = bullet6;
            enemy->bullets[enemy->bullet_count++] = bullet7;
            enemy->bullets[enemy->bullet_count++] = bullet8;
            enemy->bullets[enemy->bullet_count++] = bullet9;
            enemy->bullets[enemy->bullet_count++] = bullet10;
            enemy->bullets[enemy->bullet_count++] = bullet11;
        }
    }

    // Very beautiful bullets from level 5 enemy
    if(enemy->level == 5){
        float angle = 90 + enemy5angle;
        enemy5angle += 10;
        Bullet *bullet = Bullet_create(angle*3.14/180, enemy->x, enemy->y, enemy->level);
        enemy->bullets[enemy->bullet_count++] = bullet;
    }

    // Boss will shoot homing missile
    if(enemy->level == 6){
        int randomProb = rand() % 100;
        if(randomProb <= 5 && enemy->bullet_count < MAXNO_BULLETS){
            float angle = atan2(playerY - enemy->y, playerX - enemy->x);
            //float angle = atan2(playerX - enemy->x, playerY - enemy->y);
            //float angle = rand() % 181;
            Bullet *bullet = Bullet_create(angle, enemy->x, enemy->y, enemy->level);
            //bullet->dx = 0;
            //bullet->dy = 90;
            //Bullet_setSpeed(bullet, enemy->level); [Not working]
            Bullet_setColor(bullet, al_map_rgb_f(1, 0, 0));
            enemy->bullets[enemy->bullet_count++] = bullet;
        }
    }

    for(int i = 0; i < enemy->bullet_count; ++i){
        Bullet_update(enemy->bullets[i]);
    }

    // Remove bullets
    int bullet_index = 0;
    for (int i = 0; i < enemy->bullet_count; ++i) {
        Bullet* bullet = enemy->bullets[i];
        if (Bullet_remove(bullet)) {
            free(bullet);
        } else {
            enemy->bullets[bullet_index++] = bullet;
        }
    }
    enemy->bullet_count = bullet_index;
}

void Enemy_draw(Enemy *enemy){
    if(al_get_timer_started(enemy->recTimer)){
        switch(enemy->level){
        case 1:
            al_draw_scaled_bitmap(eh1, 0, 0, al_get_bitmap_width(eh1), al_get_bitmap_height(eh1), enemy->x, enemy->y, 80, 80, 0);
            break;
        case 2:
            al_draw_scaled_bitmap(eh2, 0, 0, al_get_bitmap_width(eh2), al_get_bitmap_height(eh2), enemy->x, enemy->y, 80, 80, 0);
            break;
        case 3:
            al_draw_scaled_bitmap(eh3, 0, 0, al_get_bitmap_width(eh3), al_get_bitmap_height(eh3), enemy->x, enemy->y, 80, 80, 0);
            break;
        case 4:
            al_draw_scaled_bitmap(eh4, 0, 0, al_get_bitmap_width(eh4), al_get_bitmap_height(eh4), enemy->x, enemy->y, 150, 150, 0);
            break;
        case 5:
            al_draw_scaled_bitmap(eh5, 0, 0, al_get_bitmap_width(eh5), al_get_bitmap_height(eh5), enemy->x, enemy->y, 200, 200, 0);
            break;
        case 6:
            al_draw_scaled_bitmap(eh6, 0, 0, al_get_bitmap_width(eh6), al_get_bitmap_height(eh6), enemy->x, enemy->y, 300, 300, 0);
            break;
        }
        //ALLEGRO_BITMAP *tmp = game->enemyHitImages[enemy->level];
        //al_draw_scaled_bitmap(tmp,0, 0, al_get_bitmap_width(tmp), al_get_bitmap_height(tmp),
        //                      enemy->x, enemy->y, 50, 50, 0);
    }else{
        switch(enemy->level){
            case 1:
                al_draw_scaled_bitmap(e1, 0, 0, al_get_bitmap_width(e1), al_get_bitmap_height(e1), enemy->x, enemy->y, 80, 80, 0);
                break;
            case 2:
                al_draw_scaled_bitmap(e2, 0, 0, al_get_bitmap_width(e2), al_get_bitmap_height(e2), enemy->x, enemy->y, 80, 80, 0);
                break;
            case 3:
                al_draw_scaled_bitmap(e3, 0, 0, al_get_bitmap_width(e3), al_get_bitmap_height(e3), enemy->x, enemy->y, 80, 80, 0);
                break;
            case 4:
                al_draw_scaled_bitmap(e4, 0, 0, al_get_bitmap_width(e4), al_get_bitmap_height(e4), enemy->x, enemy->y, 150, 150, 0);
                break;
            case 5:
                al_draw_scaled_bitmap(e5, 0, 0, al_get_bitmap_width(e5), al_get_bitmap_height(e5), enemy->x, enemy->y, 200, 200, 0);
                break;
            case 6:
                al_draw_scaled_bitmap(e6, 0, 0, al_get_bitmap_width(e6), al_get_bitmap_height(e6), enemy->x, enemy->y, 300, 300, 0);
                break;
        }
        //ALLEGRO_BITMAP *tmp = game->enemyImages[enemy->level];
        //al_draw_scaled_bitmap(tmp, 0, 0, al_get_bitmap_width(tmp), al_get_bitmap_height(tmp), enemy->x, enemy->y,
        //    50, 50, 0);
    }
    /*
    if(al_get_timer_started(enemy->recTimer)){
        enemy->recColor = al_map_rgb(255, 255, 255);
        al_draw_filled_circle(enemy->x, enemy->y, enemy->radius, enemy->recColor);
    }else{
        al_draw_filled_circle(enemy->x, enemy->y, enemy->radius, enemy->color);
    }*/

    for(int i = 0; i < enemy->bullet_count; ++i){
        Bullet_draw(enemy->bullets[i]);
    }
}

void Enemy_destroy(Enemy *enemy){
    /*
    for(int i = 1; i <= 6; ++i){
        char a[30], b[30];
        sprintf(a, "e%d", i);
        sprintf(b, "eh%d", i);
        al_destroy_bitmap(a);
        al_destroy_bitmap(b);
    }*/

    for(int i = 0; i < enemy->bullet_count; ++i){
        Bullet *bullet = enemy->bullets[i];
        free(bullet);
    }
    free(enemy->bullets);

    al_destroy_timer(enemy->recTimer);
    al_destroy_event_queue(enemy->event_queue);
}

float Enemy_getX(Enemy *enemy) { return enemy->x; }
float Enemy_getY(Enemy *enemy) { return enemy->y; }
float Enemy_getRadius(Enemy *enemy) { return enemy->radius; }

void Enemy_isHit(Enemy *enemy){
    --enemy->hp;
    al_start_timer(enemy->recTimer);
}

bool Enemy_isDead(Enemy *enemy){
    return enemy->hp <= 0;
}

bool Enemy_isRecovering(Enemy *enemy){
    return al_get_timer_started(enemy->recTimer);
}

ALLEGRO_COLOR Enemy_getColor(Enemy *enemy){
    return enemy->color;
}

void Enemy_loadImages(){
    e1 = al_load_bitmap("image/enemy1.png");
    e2 = al_load_bitmap("image/enemy2.png");
    e3 = al_load_bitmap("image/enemy3.png");
    e4 = al_load_bitmap("image/enemy4.png");
    e5 = al_load_bitmap("image/enemy5.png");
    e6 = al_load_bitmap("image/enemy6.png");
    eh1 = al_load_bitmap("image/enemyHit1.png");
    eh2 = al_load_bitmap("image/enemyHit2.png");
    eh3 = al_load_bitmap("image/enemyHit3.png");
    eh4 = al_load_bitmap("image/enemyHit4.png");
    eh5 = al_load_bitmap("image/enemyHit5.png");
    eh6 = al_load_bitmap("image/enemyHit6.png");
}

void Enemy_destroyImages(){
    al_destroy_bitmap("image/enemy1.png");
    al_destroy_bitmap("image/enemy2.png");
    al_destroy_bitmap("image/enemy3.png");
    al_destroy_bitmap("image/enemy4.png");
    al_destroy_bitmap("image/enemy5.png");
    al_destroy_bitmap("image/enemy6.png");
    al_destroy_bitmap("image/enemyHit1.png");
    al_destroy_bitmap("image/enemyHit2.png");
    al_destroy_bitmap("image/enemyHit3.png");
    al_destroy_bitmap("image/enemyHit4.png");
    al_destroy_bitmap("image/enemyHit5.png");
    al_destroy_bitmap("image/enemyHit6.png");
}
