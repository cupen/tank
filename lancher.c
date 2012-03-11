#include <stdio.h>
#include <stdlib.h>
#include "rolesdef.h"

#define ENEMY_COUNT         4                 // 敌方数量
#define BULLET_COUNT        ENEMY_COUNT*3+3 // 子弹总数- 敌方&玩家
//#define INPUT_ARRAY_LENGH   16

int input[INPUT_ARRAY_LENGH] = {0};
int isRunning = 1;

//////////////////////////////////////////////////////
//			基本设置
//////////////////////////////////////////////////////
void gameInitialize()
{
  fixConsoleSize( (WIDTH+INFO_BLOCK_SPACE+INFO_BLOCK_SPACE_FOR_BULLET)*2,HEIGHT); // as setBounds
  setConsoleTitle("Tank War    by Cupenoruler");
  setColors(GREEN,BLACK);
  setCursorVisible(0);
  return;
}



int isLocationEmpty(int x, int y,const TANK* tank)
{
    x = abs( x - tank->x);
    y = abs( y - tank->y);

    if( x < tank->size*2 &&
        y < tank->size*2)
    {
        return 0;  // false

    } else {
        return 1;  // true

    }

}

void enemySupply( TANK_MANAGER* t_m )
{
    int locations[8] =
    {
        1,       1,
        WIDTH-1, 1,
        WIDTH-1, HEIGHT-1,
        1,       HEIGHT-1
    };

    int index = 0;

    if( ENEMY_COUNT > t_m->tank_count-1)
    {
        TANK* tank = t_m->nextTank;
        while(index < 8)
        {
            while(NULL != tank)
            {
                if(isLocationEmpty( locations[index], locations[index+1],tank)){
                    if(NULL == tank->nextTank){  // OK, the locatoin is empty. I can add a Enemy Tank.
                        TANK* temp = create_Tank(5,1);
                        temp->x = locations[index];
                        temp->y = locations[index+1];
                        temp->live = 1;
                        addTank(t_m, temp);
                    }

                } else {
                    break;

                }

                tank = tank->nextTank;
            }
            index += 2;
        }
    }
    return;
}


void getInput()
{
    if(kbhit())
    {
        int i = 0;
        for(; i<INPUT_ARRAY_LENGH; i++)
        {
            if(0 == input[i]){
                input[i] = jkGetKey();
                return;

            } else {
                continue;
            }
        }
    }
    return;
}

void doGame(TANK *player, TANK_MANAGER *t_m, BULLET_MANAGER *b_m)
{
    //BOOM* boom1 = createBoom(5,5,GREEN,0);
    //BOOM* boom2 = createBoom(10,5,RED,1);
    //BOOM* boom3 = createBoom(15,5,MAGENTA,2);
    //BOOM* boom4 = createBoom(20,5,LIGHT_BLUE,3);

    while(isRunning)
    {
        drawRectangle(WIDTH,0,INFO_BLOCK_SPACE,HEIGHT-1,LIGHT_GREEN);
	    Bullet_Manager_Info(WIDTH+INFO_BLOCK_SPACE, 0, b_m, LIGHT_BLUE);
	    Tank_Manager_Info(WIDTH+INFO_BLOCK_SPACE, 7, t_m, LIGHT_BLUE);
	    tankInfo( WIDTH+1, 1, player, LIGHT_CYAN );

        /*
        if(player->nextTank == NULL)
        {
            TANK* tank = create_Tank(5,1);
            tank->color = LIGHT_RED;
            player->nextTank = tank;
        }
        */
        //drawBoom(boom1);
        //drawBoom(boom2);
        //drawBoom(boom3);
        //drawBoom(boom4);

        getInput();
        enemySupply(t_m);
        draw_Booms(t_m->boom_manager, t_m->boom_count);

        operate_BulletHitTank(t_m, b_m);
        operate_BulletHitBullet(b_m);

        draw_Bullets(b_m);
        //draw_Tanks(t_m); // all in move_Tanks(TANK_MANAGER*);

        clean_Bullets(b_m);
		//clean_Tanks(t_m); // all in move_Tanks(TANK_MANAGER*);
        move_Tanks(t_m, b_m);
        move_Bullets(b_m);
		delayMS(100);

		// clock_t i = clock();
		// printf("%d",i);
		//input[0] = 'j';
		//input[1] = 'j';
		//input[10] = '/';
	}
	return;
}



int main(void)
{
    gameInitialize();
    TANK_MANAGER *tank_manager = create_Tank_Manager();
    BULLET_MANAGER *bullet_manager = create_Bullet_Manager(BULLET_COUNT);

    TANK* player = create_Tank(1,1);
    player->x = 6;
    player->y = 10;
    player->dir = RIGHT;
    player->color = LIGHT_GREEN;

    addTank(tank_manager, player);

    doGame(player, tank_manager, bullet_manager);

    destroy_Bullet_Manager(bullet_manager);
    destroy_Tank_Manager(tank_manager);
    return 0;
}
