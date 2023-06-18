#include "background.h"

Background *New_Background(const char *filename)
{
    Background *obj = (Background *)malloc(sizeof(Background));
    obj->x = 0; // If x/y are not initialized will trigger bug of undefined behavior.
    obj->y = 0;
    obj->backgroundImage = al_load_bitmap(filename);
    if (!obj->backgroundImage)
    {
        printf("Fail to load image.\n");
    }
    return obj;
}

void background_update(Background *obj)
{
    obj->y += 2;
    if (obj->y >= GAME_HEIGHT){
        obj->y = 0;
    }
}

void background_draw(Background *obj)
{   /*
    void al_draw_scaled_bitmap(ALLGEGRO_BITMAP *bitmap,float sx, float sy,
                               float sw, float sh, float dx, float dy, float dh, int flags)
    */

    al_draw_scaled_bitmap(obj->backgroundImage, 0, 0,
                          al_get_bitmap_width(obj->backgroundImage),
                          al_get_bitmap_height(obj->backgroundImage),
                          obj->x, obj->y, GAME_WIDTH, GAME_HEIGHT, 0);
    al_draw_scaled_bitmap(obj->backgroundImage, 0, 0,
                          al_get_bitmap_width(obj->backgroundImage),
                          al_get_bitmap_height(obj->backgroundImage),
                          obj->x, obj->y - GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT, 0);
}

void background_destroy(Background *obj)
{
    al_destroy_bitmap(obj->backgroundImage);
    free(obj);
}
