#include "explosion.h"

GIF *obj;
ALLEGRO_BITMAP *frame;

Explosion_init(Explosion* exp, float _x, float _y, float _r, ALLEGRO_COLOR _color){
    exp->x = _x;
    exp->y = _y;
    exp->radius = _r;
    exp->color = _color;
    exp->stopExp = false;
    exp->expTimer = al_get_time(); // initialized time
    exp->expTimerDiff = 1; // Boom for 1 sec
}

Explosion_update(Explosion* exp){
    exp->radius += 0.5;
    if(al_get_time() - exp->expTimer >= exp->expTimerDiff){
        exp->stopExp = true;
    }
}

Explosion_draw(Explosion* exp){
    frame = algif_get_bitmap( obj->gif, obj->time(obj, al_get_time()) );
    al_draw_scaled_bitmap(frame, 0, 0,
                          al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame),
                          exp->x, exp->y,
                          exp->radius,
                          exp->radius, 0);

    //al_draw_circle(exp->x, exp->y, exp->radius, exp->color, 2);
}

Explosion_remove(Explosion* exp){
    return exp->stopExp;
}

Explosion_destroy(){
    //algif_destroy_animation(obj->gif);
}

void Explosion_loadGIF(){
    obj = New_GIF();
    obj->gif = algif_load_animation("image/explosion1.gif");
}

double get_time(GIF* obj, double time) {
    if(obj->start_time == 0) obj->start_time = time;
    return time - obj->start_time;
}

void gif_destroy(GIF* obj) {
    algif_destroy_animation(obj->gif);
}

GIF* New_GIF(){
    GIF* obj = (GIF*)malloc(sizeof(GIF));
    obj->start_time = 0;
    obj->time = get_time;
    obj->destroy = gif_destroy;
    return obj;
}
