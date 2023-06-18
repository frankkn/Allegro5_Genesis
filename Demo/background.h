#include "constants.h"

typedef struct _Background
{
    int x;
    int y;
    ALLEGRO_BITMAP *backgroundImage;
} Background;

Background *New_Background(const char *filename);
void background_update(Background *obj);
void background_draw(Background *obj);
void background_destroy(Background *obj);
