#include <stdio.h>
#include <stdlib.h>
#include "rolesdef.h"

//////////////////////////////////////
//         ■   ■      (x-2,y-2) (x-1,y-2) (x,y-2) (x+1,y-2) (x+2,y-2)
//          ■■■       (x-2,y-1) (x-1,y-1) (x,y-1) (x+1,y-1) (x+2,y-1)
//         ■■■■■      (x-2,y  ) (x-1,y  ) (x,y  ) (x+1,y  ) (x+2,y  )
//          ■■■       (x-2,y+1) (x-1,y+1) (x,y+1) (x+1,y+1) (x+2,y+1)
//                    (x-2,y+2) (x-1,y+2) (x,y+2) (x+1,y+2) (x+2,y+2)
//         ■   ■
/////////////////////////////////////

//int index = 0;
int view[8] =
{
    0x00023880,
    0x00050140,
    0x00051140,
    0x01151151,
    0x01104415
};

int body[50] =
{
    -2,-2,/**/-1,-2,/**/0,-2,/**/1,-2,/**/2,-2,
    -2,-1,/**/-1,-1,/**/0,-1,/**/1,-1,/**/2,-1,
    -2, 0,/**/-1, 0,/**/0, 0,/**/1, 0,/**/2, 0,
    -2, 1,/**/-1, 1,/**/0, 1,/**/1, 1,/**/2, 1,
    -2, 2,/**/-1, 2,/**/0, 2,/**/1, 2,/**/2, 2
};

BOOM* createBoom(int x, int y, PCCOLOR color, int body_view_index)
{
    BOOM* temp = (BOOM*)malloc( sizeof(BOOM) );
    temp->live = 10;
    temp->size = body_view_index;
    temp->x = x;
    temp->y = y;
    temp->color = color;
    ///////////////
    // 0 0 0 0 0 // (1) 0 0000 0010 0011 1000 1000 0000
    // 0 0 0 0 0 // (2) 0 0000 0101 0000 0001 0100 0000
    // 0 0 0 0 0 // (3) 0 0000 0101 0001 0001 0100 0000
    // 0 0 0 0 0 // (4) 1 0001 0101 0001 0001 0101 0001
    // 0 0 0 0 0 // (5) 1 0001 0000 0100 0100 0001 0101
    ///////////////
    // 0x00 05 01 40
    // 0x00 05 11 40
    // 0x01 15 11 51
    // 0x01 10 44 15


    temp->body = view[body_view_index];
    return temp;
}

void drawBoom(BOOM* boom)
{
    int i = 0;
    for(; i<25; i++)
    {
        if( boom->body & (0x01000000>>i) ){
            drawBlock( boom->x + body[i<<1],
                      boom->y + body[(i<<1)+1],
                      boom->color,
                      9);
        } else {
            drawBlock( boom->x + body[i<<1],
                      boom->y + body[(i<<1)+1],
                      BLACK,
                      0);

        }
    }
    boom->size++;
    (boom->size) %= 7;
    boom->body = view[boom->size];
}

void draw_Booms(BOOM* boom, int count)
{
    int i = 0;
    for(; i < count; i++)
    {
        if( 0 >= boom[i].live ){
            continue;
        }
        drawBoom(boom+i);
        boom[i].live--;
    }
}

void addBoom(int x, int y, PCCOLOR color, TANK_MANAGER* t_m)
{
    BOOM* booms = t_m->boom_manager;
    int i = 0, count = t_m->boom_count;
    for(; i<count; i++)
    {
        if( 0 == booms[i].live ){
            booms[i].x      = x;
            booms[i].y      = y;
            booms[i].color  = color;
            booms[i].live   = 7;
            booms[i].body   = view[0];
            booms[i].size   = 0;
            break;
        }
    }
}
