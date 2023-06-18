#include "buff.h"

ALLEGRO_BITMAP *buff1, *buff2, *buff3, *debuff1, *debuff2, *buffImage;

void buff_init()
{
    buff_show = false;
    buff1 = al_load_bitmap("./image/buff1.png");
    buff2 = al_load_bitmap("./image/buff2.png");
    buff3 = al_load_bitmap("./image/buff3.png");
    debuff1 = al_load_bitmap("./image/debuff1.png");
    debuff2 = al_load_bitmap("./image/debuff2.png");
    al_start_timer(buff_timer);
}

void buff_update()
{
    buff_show = false;
    buffX = -10;
    buffY = -10;
}

void buff_draw()
{
    if (generatebuff) {
        buffType = rand() % 5;
        buffX = rand() % (GAME_WIDTH - 180) + 80;
        buffY = rand() % (GAME_HEIGHT - 200) + 80;
        generatebuff = false;
    }
    if(buff_show){
        switch (buffType)
        {
            case 0:
                buffImage = buff1;
                break;
            case 1:
                buffImage = buff2;
                break;
            case 2:
                buffImage = buff3;
                break;
            case 3:
                buffImage = debuff1;
                break;
            case 4:
                buffImage = debuff2;
                break;
        }
        al_draw_scaled_bitmap(buffImage, 0, 0,
                          al_get_bitmap_width(buffImage),
                          al_get_bitmap_height(buffImage),
                          buffX, buffY, 100, 120, 0);
    }
}

void buff_destroy()
{
    al_destroy_bitmap(buff1);
    al_destroy_bitmap(buff2);
    al_destroy_bitmap(buff3);
    al_destroy_bitmap(debuff1);
    al_destroy_bitmap(debuff2);
    al_destroy_bitmap(buffImage);
    al_destroy_timer(buff_timer);
}
