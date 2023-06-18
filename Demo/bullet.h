#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "constants.h"

typedef struct _Bullet
{
    float x;
    float y;
    float radius;

    float angle;
    float dx;
    float dy;
    float speed;

    bool isExist;

    int owner; // 1:player 2-6: enemy's level

    ALLEGRO_COLOR color;
} Bullet;

Bullet* Bullet_create(float, float, float, int);
void Bullet_init(Bullet*);
void Bullet_update(Bullet*);
void Bullet_draw(Bullet*);
int Bullet_remove(Bullet*);

float Bullet_getX(Bullet*);
float Bullet_getY(Bullet*);
float Bullet_getRadius(Bullet*);

bool Bullet_checkExist(Bullet*);
void Bullet_kill(Bullet*);

void Bullet_setColor(Bullet*, ALLEGRO_COLOR);
void Bullet_setSpeed(Bullet*, int);

#endif
