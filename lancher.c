#include <stdio.h>
#include <stdlib.h>
#include "pcc32.h"
#include "rules.h"
//////////////////////////////////////////////////////
//			基本设置
//////////////////////////////////////////////////////
void gameInitialize()
{
  fixConsoleSize(Width*2,Height);    //把控制台窗口限制在一个区域
  setConsoleTitle("Tank War       by Cupenoruler");    //设置标题
  setColors(GREEN,BLACK);                      //设置文本颜色和背景色
  setCursorVisible(0);                         //设置光标是不可见
  return;
}

void doGame(TANK *player, TANK_MAGAGER *t_m, BULLET_MANAGER *b_m)
{
    t_m->nextTank = player;
    while(1){
	    Bullet_Manager_Info(0,Height-1,b_m, MAGENTA);
	    tankInfo(player,MAGENTA );

		getInput( player, b_m );

        move_Tanks(t_m);

        move_Bullets(b_m);
        draw_Bullets(b_m);
        clean_Bullets(b_m);
		delayMS(100);

		// printf("%d",0011);
		// clock_t i = clock();
		// printf("%d",i);
	}
	return;
}

int main(void)
{
    TANK_MAGAGER *tank_manager = create_Tank_Manager();
    BULLET_MANAGER *bullet_manager = create_Bullet_Manager(5);

    TANK* player = (TANK*)malloc(sizeof(TANK));
    player->id = 1;
    player->x = 5;
    player->y = 10;
    player->dir = UP;
    player->color = GREEN;
    player->size = 1;
    player->nextTank = NULL;

    //addTank(tank_manager, player);

	drawString(5,10,RED,"hello WORD");

    doGame(player, tank_manager, bullet_manager);
    return 0;
}
