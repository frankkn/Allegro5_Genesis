#include "player.h"

ALLEGRO_BITMAP *dog, *crydog, *hp;

void Player_init(Player *player)
{
    player->x = GAME_WIDTH / 2;
    player->y = GAME_HEIGHT - 100;
    player->radius = 20;
    player->dx = 0;
    player->dy = 0;
    player->speed = 8;
    player->left = player->right = player->up = player->down = player->shooting = 0;
    player->bullet_count = 0;
    player->bullets = (Bullet**)malloc(MAXNO_BULLETS * sizeof(Bullet*));

    player->hp = 3;

    player->timer = al_create_timer(1.0/5); // 5 bullets per sec
    player->recTimer = al_create_timer(1.5); // Immune for 1.5 secs after get hit
    player->event_queue = al_create_event_queue();
    al_register_event_source(player->event_queue, al_get_timer_event_source(player->timer));
    al_register_event_source(player->event_queue, al_get_timer_event_source(player->recTimer));

    player->shootSound = al_load_sample("music/dog-barking1.mp3");

    dog = al_load_bitmap("./image/dog.png");
    crydog = al_load_bitmap("./image/dogHit.png");
    hp = al_load_bitmap("./image/hp.png");

    player->width = 80;
    player->height = 80;

    player->onFire = 0;
}

void Player_update(Player *player)
{
    if (player->left)
    {
        player->dx = -player->speed;
    }
    else if (player->right)
    {
        player->dx = player->speed;
    }
    else
    {
        player->dx = 0;
    }
    if (player->up)
    {
        player->dy = -player->speed;
    }
    else if (player->down)
    {
        player->dy = player->speed;
    }
    else
    {
        player->dy = 0;
    }

    player->x += player->dx;
    player->y += player->dy;

    if (player->x < player->radius) // Left boundary
        player->x = player->radius;
    if (player->y < player->radius) // Top boundary
        player->y = player->radius;
    if (player->x + player->radius *5 > GAME_WIDTH)
        player->x = GAME_WIDTH - player->radius *5;
    if (player->y + player->radius *5> GAME_HEIGHT)
        player->y = GAME_HEIGHT - player->radius *5;

    ALLEGRO_EVENT event;
    if(al_get_next_event(player->event_queue, &event) &&
       event.timer.source == player->recTimer){
        al_stop_timer(player->recTimer);
    }
    if(player->shooting){
        if(!al_get_timer_started(player->timer)){
            al_start_timer(player->timer);
            Player_shootBullet(player);
        }
        if(event.timer.source == player->timer) { Player_shootBullet(player); }
        // ALLEGRO_EVENT event;
        if(al_get_next_event(player->event_queue, &event)){
            Player_shootBullet(player);
        }
    }else{ // not firing
        al_stop_timer(player->timer);
    }

    for (int i = 0; i < player->bullet_count; i++) {
        Bullet* bullet = player->bullets[i];
        Bullet_update(bullet);
    }

    // Remove bullets
    int bullet_index = 0;
    for (int i = 0; i < player->bullet_count; ++i) {
        Bullet* bullet = player->bullets[i];
        if (Bullet_remove(bullet)) {
            free(bullet);
        } else {
            player->bullets[bullet_index++] = bullet;
        }
    }
    player->bullet_count = bullet_index;
}

void Player_shootBullet(Player *player){

  if (player->bullet_count < MAXNO_BULLETS) {
    if(player->onFire == 0){
        Bullet* bullet1 = Bullet_create(-90, player->x, player->y, 1);
        bullet1->speed = 20;
        bullet1->dx = cos(bullet1->angle*3.1415/180) * bullet1->speed;
        bullet1->dy = sin(bullet1->angle*3.1415/180) * bullet1->speed;
        player->bullets[player->bullet_count++] = bullet1;
    }else if(player-> onFire == 1){
        Bullet* bullet1 = Bullet_create(-80, player->x, player->y, 1);
        bullet1->speed = 20;
        bullet1->dx = cos(bullet1->angle*3.1415/180) * bullet1->speed;
        bullet1->dy = sin(bullet1->angle*3.1415/180) * bullet1->speed;
        player->bullets[player->bullet_count++] = bullet1;

        Bullet* bullet2 = Bullet_create(-100, player->x, player->y, 1);
        bullet2->speed = 20;
        bullet2->dx = cos(bullet2->angle*3.1415/180) * bullet2->speed;
        bullet2->dy = sin(bullet2->angle*3.1415/180) * bullet2->speed;
        player->bullets[player->bullet_count++] = bullet2;
    }else{
        Bullet* bullet1 = Bullet_create(-60, player->x, player->y, 1);
        bullet1->speed = 20;
        bullet1->dx = cos(bullet1->angle*3.1415/180) * bullet1->speed;
        bullet1->dy = sin(bullet1->angle*3.1415/180) * bullet1->speed;
        player->bullets[player->bullet_count++] = bullet1;

        Bullet* bullet2 = Bullet_create(-90, player->x, player->y, 1);
        bullet2->speed = 20;
        bullet2->dx = cos(bullet2->angle*3.1415/180) * bullet2->speed;
        bullet2->dy = sin(bullet2->angle*3.1415/180) * bullet2->speed;
        player->bullets[player->bullet_count++] = bullet2;

        Bullet* bullet3 = Bullet_create(-120, player->x, player->y, 1);
        bullet3->speed = 20;
        bullet3->dx = cos(bullet3->angle*3.1415/180) * bullet3->speed;
        bullet3->dy = sin(bullet3->angle*3.1415/180) * bullet3->speed;
        player->bullets[player->bullet_count++] = bullet3;

    }
    //player->bullets[player->bullet_count++] = bullet2;
    //player->bullets[player->bullet_count++] = bullet3;
    //printf("%d ", bullet1->speed);
  }

  al_play_sample(player->shootSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &player->shootID);
}

void Player_handleInput(Player *player)
{
    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);
    player->left = al_key_down(&key_state, ALLEGRO_KEY_LEFT);
    player->right = al_key_down(&key_state, ALLEGRO_KEY_RIGHT);
    player->up = al_key_down(&key_state, ALLEGRO_KEY_UP);
    player->down = al_key_down(&key_state, ALLEGRO_KEY_DOWN);
    player->shooting = al_key_down(&key_state, ALLEGRO_KEY_SPACE);
}

void Player_draw(Player *player)
{
    if(al_get_timer_started(player->recTimer)){
        al_draw_scaled_bitmap(crydog, 0, 0, al_get_bitmap_width(crydog),al_get_bitmap_height(crydog),
                              player->x, player->y, player->width, player->height, 0);
        //player->color = al_map_rgb(255, 255, 255);
    }else{
        al_draw_scaled_bitmap(dog, 0, 0, al_get_bitmap_width(dog),al_get_bitmap_height(dog),
                              player->x, player->y, player->width, player->height, 0);
        //player->color = al_map_rgb(0, 0, 255);
    }

    //img = al_load_bitmap("./image/dog.png");
    //al_draw_bitmap(img, player->x, player->y, 0);
    //al_draw_filled_circle(player->x, player->y, player->radius, player->color);
    //al_draw_circle(player->x, player->y, player->radius, al_map_rgb(255, 255, 255), 3);

    for(int i = 0; i < player->bullet_count; ++i){
        Bullet *bullet = player->bullets[i];
        Bullet_draw(bullet);
    }

    // Draw hp
    for(int i = 0; i < player->hp; ++i){
    /*void al_draw_scaled_bitmap(ALLGEGRO_BITMAP *bitmap, float sx, float sy,
        float sw, float sh, float dx, float dy, float dw, float dh, int flags)*/
        al_draw_scaled_bitmap(hp, 0, 0,
                              al_get_bitmap_width(hp), al_get_bitmap_height(hp),
                              30, 30 + i*80,
                              80, 80, 0);

        // al_draw_bitmap(hp, 50+i*30, 50, 0);

        // al_draw_filled_circle(50+i*30, 50, player->radius, al_map_rgb_f(0, 0, 1));
        // al_draw_circle(50+i*30, 50, player->radius, al_map_rgb_f(1, 1, 1), 3);
    }
}

void Player_destroy(Player *player) {
    al_destroy_bitmap(dog);
    al_destroy_bitmap(crydog);
    al_destroy_bitmap(hp);

    for(int i = 0; i < player->bullet_count; ++i){
        Bullet *bullet = player->bullets[i];
        free(bullet);
    }
    free(player->bullets);

    al_destroy_event_queue(player->event_queue);
    al_destroy_timer(player->timer);
    al_destroy_timer(player->recTimer);
    al_destroy_sample(player->shootSound);
}

float Player_getX(Player *player) { return player->x; }
float Player_getY(Player *player) { return player->y; }
float Player_getRadius(Player *player) { return player->radius; }

// Use bullet_count to avoid using this function
Bullet*** Player_getBullets(Player *player){
    return &(player->bullets);
}

void Player_isHit(Player *player){
    --player->hp;
    al_start_timer(player->recTimer);
}

int Player_getHp(Player *player){
    return player->hp;
}

bool Player_isRecovering(Player *player){
    return al_get_timer_started(player->recTimer);
}

void Player_speedUp(Player *player){ player->speed += 3; }

void Player_hpAdd(Player *player){ ++player->hp; }

void Player_hpMinus(Player *player){ --player->hp; }

void Player_bigger(Player *player){ player->width += 20; player->height += 20; player->radius += 10;}

void Player_onFire(Player *player){
    player->onFire += 1;
}
