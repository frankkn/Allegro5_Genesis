#include "bullet.h"
#include "constants.h"
#include "explosion.h"

typedef struct _Enemy{
    int level;
    float x;
    float y;
    float radius;

    float speed;
    float dx;
    float dy;
    float angle;

    int hp;
    bool isOnScreen;

    ALLEGRO_COLOR color;
    ALLEGRO_COLOR recColor;

    int bullet_count;
    Bullet **bullets;

    ALLEGRO_TIMER *recTimer;
    ALLEGRO_EVENT_QUEUE *event_queue;
}Enemy;

void Enemy_init(Enemy*, int);
void Enemy_update(Enemy*, float, float);
void Enemy_draw(Enemy*);
void Enemy_destroy(Enemy*);

float Enemy_getX(Enemy*);
float Enemy_getY(Enemy*);
float Enemy_getRadius(Enemy*);

void Enemy_isHit(Enemy*);
bool Enemy_isDead(Enemy*);
bool Enemy_isRecovering(Enemy *);

ALLEGRO_COLOR Enemy_getColor(Enemy*);
