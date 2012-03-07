#include <stdio.h>
#include <stdlib.h>
#include "pcc32.h"
#include "rules.h"

void draw_Bullets(BULLET_MANAGER *b_m)
{
	if( NULL == b_m){
		printf("Bullet_Manager is null;");
		return;
	}
	int i=0,lengh = b_m->bullet_Count;
	for(i=0 ; i<lengh; i++)
	{
		if( b_m->bullets[i].button )  // true, mean the bullet be FaShe
		{
			drawBlock( b_m->bullets[i].x, b_m->bullets[i].y, b_m->bullets[i].color, 2);
		}
	}
}

void drawBullet(BULLET *bullet)
{
    drawBlock(bullet->x, bullet->y, bullet->color, 2);
}

void clean_Bullets(BULLET_MANAGER *b_m)
{
    if( NULL == b_m){
		printf("Bullet_Manager is null;");
		return;
	}
	int i=0,lengh = b_m->bullet_Count;
	for(i=0 ; i<lengh; i++)
	{
		if( b_m->bullets[i].button )  // true, mean the bullet be FaShe
		{
			switch(b_m->bullets[i].dir)
			{
			    case UP:
                    drawBlock( b_m->bullets[i].x, b_m->bullets[i].y+1, b_m->bullets[i].color, 0);
                    break;

                case DOWN:
                    drawBlock( b_m->bullets[i].x, b_m->bullets[i].y-1, b_m->bullets[i].color, 0);
                    break;

                case LEFT:
                    drawBlock( b_m->bullets[i].x+1, b_m->bullets[i].y, b_m->bullets[i].color, 0);
                    break;

                case RIGHT:
                    drawBlock( b_m->bullets[i].x-1, b_m->bullets[i].y, b_m->bullets[i].color, 0);
                    break;

                default: printf("void clean_Bullets(BULLET_MANAGER *b_m)");
			}
		}
	}
}

void move_Bullets(BULLET_MANAGER *b_m)
{
	if( NULL == b_m){
		printf("Bullet_Manager is null;");
		return;
	}

	int i=0,lengh = b_m->bullet_Count;
	for(i=0 ; i<lengh; i++)
	{
		if( b_m->bullets[i].button )  // true, mean the bullet be FaShe
		{
			switch(b_m->bullets[i].dir)
			{
				case UP:
					b_m->bullets[i].y--;
					break;

				case DOWN:
					b_m->bullets[i].y++;
					break;

				case LEFT:
					b_m->bullets[i].x--;
					break;

				case RIGHT:
					b_m->bullets[i].x++;
					break;
			}

			if( b_m->bullets[i].x < 0 ||
				b_m->bullets[i].x > Width - 1||
				b_m->bullets[i].y < 0 ||
				b_m->bullets[i].y > Height-1 )
			{
				b_m->bullets[i].button = 0; // bullet is  XiaoShi
			}
		}
	}
	return;
}


/*
void addBullet(BULLET_MANAGER *bullet_manager)
{
    int i = 0,lengh = bullet_manager->bullet_Count;
}

*/

BULLET_MANAGER* create_Bullet_Manager(const int bullet_count)
{
    BULLET_MANAGER *tempB_M = (BULLET_MANAGER*)malloc(sizeof(BULLET_MANAGER));
    tempB_M->bullet_Count = bullet_count;
    tempB_M->bullets = calloc( bullet_count, sizeof(BULLET));

    //memset(tempB_M->bullets, 0, bullet_count);
    return tempB_M;
}

void destroy_Bullet_Manager(BULLET_MANAGER *bullet_manager)
{
    free(bullet_manager->bullets);
    free(bullet_manager);
    return;
}

void Bullet_Manager_Info(int x, int y, BULLET_MANAGER *b_m, PCCOLOR color)
{
    char temp[32] = {};
    sprintf(temp, "bullet_Count %d",b_m->bullet_Count);
    drawString(x,y++, MAGENTA,temp);

    int i = 0, lengh = b_m->bullet_Count;
    for(i=0; i < lengh; i++)
    {
        sprintf(temp, "bullet %d, %2d, %-2d",b_m->bullets[i].button, b_m->bullets[i].x, b_m->bullets[i].y);
        drawString(x,y++, color, temp);
    }
    return;
}
