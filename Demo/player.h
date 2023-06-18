#include "bullet.h"
#include "constants.h"

typedef struct _Player
{
    // Player's position
    float x;
    float y;
    float radius;
    int width;
    int height;

    // Player's movement info
    float dx; // delta_x
    float dy;
    float speed;

    int left;
    int right;
    int up;
    int down;

    bool shooting;
    int onFire;

    int hp;

    int bullet_count;
    Bullet ** bullets;

    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;

    ALLEGRO_TIMER *recTimer;
    //ALLEGRO_COLOR color;

    ALLEGRO_SAMPLE *shootSound;
    ALLEGRO_SAMPLE_ID shootID;
} Player;

void Player_init(Player*);
void Player_update(Player*);
void Player_handleInput(Player*);
void Player_draw(Player*);
void Player_destroy(Player*);

void Player_shootBullet(Player*);
void Player_isHit(Player *);
int Player_getHp(Player *);
bool Player_isRecovering(Player *);

float Player_getX(Player*);
float Player_getY(Player*);
float Player_getRadius(Player*);

Bullet*** Player_getBullets(Player*);

void Player_speedUp(Player*);
void Player_hpAdd(Player*);
void Player_hpMinus(Player*);
void Player_bigger(Player*);
