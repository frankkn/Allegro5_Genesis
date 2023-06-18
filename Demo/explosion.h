#ifndef CONSTANTS__H__INCLUDED
#define CONSTANTS__H__INCLUDED

#include "constants.h"

typedef struct GIF GIF;
typedef double (*fptrTime)(GIF*, double) ;
typedef void (*fptrDestroy)(GIF*) ;

typedef struct GIF{
    double start_time;
    ALGIF_ANIMATION *gif;
    fptrTime time;
    fptrDestroy destroy;
}GIF;

typedef struct _Explosion {
    float x;
    float y;
    float radius;
    ALLEGRO_COLOR color;
    float expTimer;
    float expTimerDiff;
    bool stopExp;
}Explosion;



Explosion_init(Explosion*, float, float, float, ALLEGRO_COLOR);
Explosion_update(Explosion*);
Explosion_draw(Explosion*);
Explosion_remove(Explosion*);
Explosion_destroy();

void Explosion_loadGIF();

double get_time(GIF* obj, double time);
void gif_destroy(GIF* obj);
GIF* New_GIF();

#endif
