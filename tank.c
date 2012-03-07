#include <stdio.h>
#include <stdlib.h>
#include "pcc32.h"
#include "rules.h"
//#include "bullet.c"
//#include "drawdraw.c"

char tankView_x[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
char tankView_y[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
//char index = 0;

void tankInfo(TANK *tank, PCCOLOR color)
{
	// system("cls");
	char temp[6] = {};
	sprintf(temp,"(%2d.%-2d),%2d",tank->x,tank->y,tank->dir);
	drawString(0,0,color,temp);
}

void getInput(TANK *tank, BULLET_MANAGER *bullet_manager)
{
	if(kbhit())
	{
		switch(jkGetKey())
		{
			case JK_UP:
			case 'w':
				tank->dir = UP;
				tank->is_stop = 0; // start move
				break;

			case JK_DOWN:
			case 's':
				tank->dir = DOWN;
				tank->is_stop = 0; // start move
				break;

			case JK_LEFT:
			case 'a':
				tank->dir = LEFT;
				tank->is_stop = 0; // start move
				break;

			case JK_RIGHT:
			case 'd':
				tank->dir = RIGHT;
				tank->is_stop = 0; // start move
				break;

			case 'j':
				tankFire(tank,bullet_manager);
				return;

			default: break;
		}
	}
}

void drawTank(TANK *tank)
{
    char index = 0;
    switch(tank->dir)
    {
        case UP: //1,3,4,5,6,8
            index = 0x5d; // 01011101
            break;

        case DOWN: //0.2.3.4.5.7
            index = 0xba; // 10111010
            break;

        case LEFT: //1,2,3,4,7,8
            index = 0x73; // 01110011
            break;

        case RIGHT: //0,1,4,5,6,7
            index = 0xce; // 11001110
            break;

        default : printf("void dirawTank");
    }

    int i =0;
    for(i=0; i<8; i++)
    {
        if( index & (0x80>>i) )
        {
            drawBlock( tank->x + tankView_x[i],
                       tank->y + tankView_y[i],
                       tank->color,
                       1);
        }
    }
    drawBlock(tank->x, tank->y, tank->color, 1);
}

void cleanTank(TANK *tank)
{
    switch(tank->dir)
	{
		case UP:
            drawBlock(tank->x,tank->y+1,BLACK,0);
			drawBlock(tank->x,tank->y+2,BLACK,0);
			drawBlock(tank->x-1,tank->y+2,BLACK,0);
			drawBlock(tank->x+1,tank->y+2,BLACK,0);
			break;

		case DOWN:
            drawBlock(tank->x,tank->y-1,BLACK,0);
			drawBlock(tank->x,tank->y-2,BLACK,0);
			drawBlock(tank->x-1,tank->y-2,BLACK,0);
			drawBlock(tank->x+1,tank->y-2,BLACK,0);
            break;

		case LEFT:
            drawBlock(tank->x+1,tank->y,BLACK,0);
			drawBlock(tank->x+2,tank->y,BLACK,0);
            drawBlock(tank->x+2,tank->y-1,BLACK,0);
            drawBlock(tank->x+2,tank->y+1,BLACK,0);
			break;

		case RIGHT:
            drawBlock(tank->x-1,tank->y,BLACK,0);
			drawBlock(tank->x-2,tank->y,BLACK,0);
			drawBlock(tank->x-2,tank->y-1,BLACK,0);
			drawBlock(tank->x-2,tank->y+1,BLACK,0);
			break;

		default :printf("void cleanTank(TANK *tank)");
	}
}

void moveTank(TANK *tank)
{
	if(tank->is_stop){
		return;
	}

	switch( tank->dir )
	{
		case UP:
			tank->y--;
			break;

		case DOWN:
			tank->y++;
			break;

		case LEFT:
			tank->x--;
			break;

		case RIGHT:
			tank->x++;
			break;
		// case : break;
		// case : break;

		default: printf("Unknow dir");
	}

	// can't out the bounds
	tank->x = ( tank->x < Width-1-tank->size    ? tank->x    : Width - 1 - tank->size);
	tank->x = ( tank->x < tank->size            ? tank->size : tank->x );
	tank->y = ( tank->y < Height-1-tank->size   ? tank->y    : Height - 1 - tank->size );
	tank->y = ( tank->y < tank->size		    ? tank->size : tank->y );

	if( 1 == tank->id )  //only for player
	{
		tank->is_stop = 1; // stop move
	}
}

void move_Tanks(const TANK_MAGAGER *tank_manager)
{
	TANK *tank = tank_manager->nextTank;

	while(NULL != tank)
	{
		if( 1 != tank->id )
		{
		    operateTankWithAI(tank);
		}
		moveTank(tank);
		drawTank(tank);
		cleanTank(tank);
		tank = tank->nextTank;
	}
}

void draw_Tanks(const TANK_MAGAGER *tank_manager)
{
    TANK *tank = tank_manager->nextTank;

	while(NULL != tank)
	{
		//operateTankWithAI(tank);
		//moveTank(tank);
		drawTank(tank);
		//cleanTank(tank);
		tank = tank->nextTank;
	}
}

void tankFire(TANK *tank, BULLET_MANAGER *bullet_manager)
{
	int i=0,lengh = bullet_manager->bullet_Count;
	for(i=0 ; i<lengh; i++)
	{
		if( bullet_manager->bullets[i].button )  // true, mean the bullet be FaShe ing
		{
			continue;
		}
		else
		{
		    bullet_manager->bullets[i].id     = tank->id;
			bullet_manager->bullets[i].button = 1;
			bullet_manager->bullets[i].x		= tank->x;
			bullet_manager->bullets[i].y 	 	= tank->y;
			bullet_manager->bullets[i].dir 	= tank->dir;
			bullet_manager->bullets[i].color  = tank->color;
			break;
		}
	}
}

TANK_MAGAGER* create_Tank_Manager()
{
    TANK_MAGAGER *tempT_B = malloc(sizeof(TANK_MAGAGER));
    tempT_B->count = 0;
    tempT_B->nextTank = NULL;

    return tempT_B;
}

/**
 * 释放掉tank链表, 使用凶残的递归;
 * 注意 链表节点个数 == 递归深度
 * 链表末尾节点必须是NULL，否则会无限递归，最终召唤出Stack Overflow
 */
void destroy_Tank(TANK *tank)
{
    if( NULL != tank ){
        destroy_Tank(tank->nextTank); // 递归检查下一节点
        free(tank->nextTank); // 上面的递归结束后，表示当前节点下面的节点已经全部释放了！可以放心的咔嚓当前节点了~
        tank->nextTank = NULL; // 防止咸鱼翻身，确保不能再访问释放掉的内存~

    } else {
        return;

    }
}

void destroy_Tank_Manager(TANK_MAGAGER *t_m)
{
    TANK *tank = t_m->nextTank;
    destroy_Tank(tank);
    return;
}

int addTank(TANK_MAGAGER *t_m, TANK* tank)
{
    TANK *tankLinks = t_m->nextTank;

    if(NULL == tankLinks){
        tankLinks = tank;

    } else {
        while( NULL != (tankLinks=tankLinks->nextTank) ){}; //find the lastest node of linktable
        tankLinks->nextTank = tank;

    }
    t_m->count++;
    return 0;
}
/*
int addTankWithRandom(TANK_MAGAGER *t_m)
{
    TANK* temp = create_Tank_With_Random();
    if( NULL != temp)
    {
        addTank(t_m,temp);
        return 0; //success
    }
    return 1; // faile

}
*/

int delTank(TANK_MAGAGER *t_m, const TANK* tank)
{
    TANK *tankLinks = t_m->nextTank;

    while( NULL != tankLinks)
    {
        if( tank == tankLinks->nextTank)
        {
            TANK *temp = tankLinks->nextTank->nextTank; // get the the deleting node's child node
            free(tankLinks->nextTank);                  // deleting the node
            tankLinks->nextTank = temp;                 // the child node replace it.''
            break;
        }
        tankLinks = tankLinks->nextTank;
    }
    t_m->count--;
    return 0;
}

TANK* create_Tank(int id, int size)
{
    TANK* temp = (TANK*)malloc(sizeof(TANK));

    temp->id = id;
    temp->x = 1;
    temp->y = 1;
    temp->dir = UP;
    temp->color = RED;
    temp->nextTank = NULL;
    temp->size = size;
    return temp;
}

/*
TANK* create_Tank_With_Random()
{
    TANK* temp = create_Tank(0);
    srand( (long)clock() );
    temp->x = rand()%100;
    temp->y = rand()%100;
    //temp->dir = rand()%4

    return temp;
}
*/

TANK* create_Tank_FromTemplete(TANK templateTank)
{
    TANK* temp = (TANK*)malloc(sizeof(TANK));

    temp->id = templateTank.id;
    temp->x = templateTank.x;
    temp->y = templateTank.y;
    temp->dir = templateTank.dir;
    temp->color = templateTank.color;
    temp->nextTank = NULL;

    return temp;
}

void operateTankWithAI(TANK *tank)
{
	srand((unsigned int)clock() );
	switch(rand() % 10)
	{
		case 0:
			break;

		case 1:
			tank->dir = UP;
			break;

		case 2:
			break;

		case 3:
			tank->dir = DOWN;
			break;

		case 4:
			break;

		case 5:
			tank->dir = LEFT;
			break;

		case 6:
			break;

		case 7:
			break;

		case 8:
			tank->dir = RIGHT;
			break;

		case 9:
			break;

	}
	tank->is_stop = 0; //move
	return;
}
