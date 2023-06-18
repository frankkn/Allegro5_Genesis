#include "bullet.h"

ALLEGRO_BITMAP *bone, *eb4, *eb5, *eb6;

Bullet* Bullet_create(float angle, float x, float y, int owner) {
    Bullet* bullet = malloc(sizeof(Bullet));
    bullet->angle = angle;
    bullet->x = x;
    bullet->y = y;
    bullet->owner = owner;
    Bullet_init(bullet);
    return bullet;
}

void Bullet_init(Bullet *bullet)
{
    bullet->radius = 20;
    bullet->speed = 5; // [BUG]?
    bullet->dx = cos(bullet->angle) * bullet->speed; // angle*pi/180?
    bullet->dy = sin(bullet->angle) * bullet->speed;
    bullet->isExist = true;
    bullet->color = al_map_rgb_f(0.3, 0.7, 0);
}

void Bullet_update(Bullet *bullet)
{
    bullet->x += bullet->dx;
    bullet->y += bullet->dy;
}

void Bullet_draw(Bullet *bullet)
{
    if(bullet->owner == 1){
        al_draw_scaled_bitmap(bone, 0, 0, al_get_bitmap_width(bone), al_get_bitmap_height(bone), Bullet_getX(bullet), Bullet_getY(bullet), bullet->radius, bullet->radius, 0);
    }else{
        switch (bullet->owner){
            case 4:
                al_draw_scaled_bitmap(eb4, 0, 0, al_get_bitmap_width(eb4), al_get_bitmap_height(eb4), Bullet_getX(bullet), Bullet_getY(bullet), 35, 35, 0);
                break;
            case 5:
                al_draw_scaled_bitmap(eb5, 0, 0, al_get_bitmap_width(eb5), al_get_bitmap_height(eb5), Bullet_getX(bullet), Bullet_getY(bullet), 35, 35, 0);
                break;
            case 6:
                al_draw_scaled_bitmap(eb6, 0, 0, al_get_bitmap_width(eb6), al_get_bitmap_height(eb6), Bullet_getX(bullet), Bullet_getY(bullet), 35, 35, 0);
                break;
            default:
                break;
        }
    }

    //al_draw_filled_circle(bullet->x, bullet->y, bullet->radius, al_map_rgb_f(1, 1, 1));
    //al_draw_circle(bullet->x, bullet->y, bullet->radius, bullet->color, 4);
}

int Bullet_remove(Bullet *bullet)
{
    int display_width = al_get_display_width(al_get_current_display());
    int display_height = al_get_display_height(al_get_current_display());

    return (bullet->x >= display_width ||
            bullet->y >= display_height ||
            bullet->x < 0 || bullet->y < 0 || !bullet->isExist);
}

float Bullet_getX(Bullet *bullet) { return bullet->x; }
float Bullet_getY(Bullet *bullet) { return bullet->y; }
float Bullet_getRadius(Bullet *bullet) { return bullet->radius; }

bool Bullet_checkExist(Bullet *bullet) { return bullet->isExist;}
void Bullet_kill(Bullet *bullet){
    bullet->isExist = false;
}


void Bullet_setColor(Bullet *bullet, ALLEGRO_COLOR _color){
    bullet->color = _color;
}

void Bullet_setSpeed(Bullet *bullet, int val){
    bullet->speed = val;
}

void Bullet_loadImages(){
    bone = al_load_bitmap("image/bone.png");
    eb4 = al_load_bitmap("image/bullet4.png");
    eb5 = al_load_bitmap("image/bullet5.png");
    eb6 = al_load_bitmap("image/bullet6.png");
}

void Bullet_destroyImages(){
    al_destroy_bitmap("image/bone.png");
    al_destroy_bitmap("image/bullet4.png");
    al_destroy_bitmap("image/bullet5.png");
    al_destroy_bitmap("image/bullet6.png");
}
