#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rolesdef.h"

char tankView_x[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
char tankView_y[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
//char index = 0;

void tankInfo(int x, int y,const TANK *tank, PCCOLOR color)
{
	// system("cls");
	char temp[32] = {};
	sprintf(temp,"Local %2d.%-2d",tank->x,tank->y);
	drawString(x,y++,color,temp);

    y++;
	sprintf(temp,"Live  %3d",tank->live);
	drawString(x,y++,color,temp);

    y++;
	sprintf(temp,"Kills %3d",tank->killCount);
	drawString(x,y++,color,temp);

    y++;
	sprintf(temp,"Bullet%3d",tank->bullet_size);
	drawString(x,y++,color,temp);

	if(0 >= tank->live)
	{
	    drawString(x,y+3,LIGHT_GRAY,"You are dead!!!!!!");
	}
}


/**
 * all the attributes of TANK must be initialize
`*/
TANK* create_Tank(int id, int size)
{
    TANK* temp = (TANK*)malloc(sizeof(TANK));

    temp->id = id;
    temp->x = 1;
    temp->y = 1;
    temp->dir = UP;
    temp->color = LIGHT_RED;
    temp->nextTank = NULL;
    temp->size = size;
    temp->bullet_size = 0;
    temp->bullet_count = 3;
    temp->live = 1;
    temp->is_stop = 1;
    temp->killCount = 0;

    return temp;
}

TANK* create_TankWithRandom()
{
    TANK* temp = create_Tank(3,1);
    srand( (unsigned int)time(NULL) );
    temp->x = rand()%50;
    temp->y = rand()%50;
    temp->dir = rand()%4;

    return temp;
}

TANK* create_TankFromTemplete(TANK templateTank)
{
    TANK* temp = create_Tank(templateTank.id, templateTank.size);

    temp->x = templateTank.x;
    temp->y = templateTank.y;
    temp->dir = templateTank.dir;
    temp->color = templateTank.color;
    temp->nextTank = NULL;

    return temp;
}


int addTank(TANK_MANAGER *t_m, TANK* tank)
{
    TANK *tankLinks = t_m->nextTank;
    if(NULL == t_m->nextTank){
        //tankLinks = tank;
        t_m->nextTank = tank;

    } else {
        while( NULL != tankLinks->nextTank ) //find the lastest node of linktable
        {
            tankLinks = tankLinks->nextTank;
        }
        tankLinks->nextTank = tank;

    }
    t_m->tank_count++;
    return 0;
}

void operateTankWithInput(TANK *tank, BULLET_MANAGER *bullet_manager)
{
    int i=0;
    for(; i < INPUT_ARRAY_LENGH; i++)
    {
        switch(input[i])
        {
			case 'w':
			case 'W':
				tank->dir = UP;
				tank->is_stop = 0; // start move
				break;

			case 's':
			case 'S':
				tank->dir = DOWN;
				tank->is_stop = 0; // start move
				break;

			case 'a':
			case 'A':
				tank->dir = LEFT;
				tank->is_stop = 0; // start move
				break;

			case 'd':
			case 'D':
				tank->dir = RIGHT;
				tank->is_stop = 0; // start move
				break;

			case 'j':
			case 'J':
				tankFire(tank,bullet_manager);
                break;
/*
            case JK_UP:
                tank->nextTank->dir = UP;
				tank->nextTank->is_stop = 0; // start move
                break;

            case JK_DOWN:
                tank->nextTank->dir = DOWN;
				tank->nextTank->is_stop = 0; // start move
                break;

            case JK_LEFT:
                tank->nextTank->dir = LEFT;
				tank->nextTank->is_stop = 0; // start move
                break;

			case JK_RIGHT:
                tank->nextTank->dir = RIGHT;
				tank->nextTank->is_stop = 0; // start move
                break;

            case '/':
                tankFire(tank->nextTank, bullet_manager);
                break;
*/
        }
        input[i] = 0;
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

        default : printf("void drawTank");
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

	if( 1 == tank->id )  //only for player
	{
		tank->is_stop = 1; // stop move
	}
}

int checkBounds(TANK* tank, const int width, const int height)
{
    // can't out the bounds
	tank->x = ( tank->x < width-1-tank->size    ? tank->x    : width - 1 - tank->size);
	tank->x = ( tank->x < tank->size            ? tank->size : tank->x );
	tank->y = ( tank->y < height-1-tank->size   ? tank->y    : height - 1 - tank->size );
	tank->y = ( tank->y < tank->size		    ? tank->size : tank->y );

	return 0;
}

void move_Tanks(TANK_MANAGER* t_m, BULLET_MANAGER* b_m)
{
	TANK *tank = t_m->nextTank;
    srand((unsigned int)time(NULL) );
	while(NULL != tank)
	{
		if( 1 == tank->id ){
            operateTankWithInput( tank, b_m );
		} else {
            operateTankWithAI(tank, b_m);
            if( 0 >= tank->live){
                TANK* temp = tank->nextTank;

                addBoom(tank->x, tank->y, tank->color, t_m);    // tank boom^
                delTank(t_m, tank);
                tank = temp;
                //continue;
                return;
            }
		}

		moveTank(tank);
		operate_TankHitTank(tank, t_m);
		checkBounds(tank, WIDTH, HEIGHT);
		drawTank(tank);
		cleanTank(tank);
		tank = tank->nextTank;
	}
}

void draw_Tanks(const TANK_MANAGER *tank_manager)
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

void clean_Tanks(const TANK_MANAGER *tank_manager)
{
    TANK *tank = tank_manager->nextTank;

	while(NULL != tank)
	{
		//moveTank(tank);
		//drawTank(tank);
		cleanTank(tank);
		tank = tank->nextTank;
	}
}

void tankFire(TANK *tank, const BULLET_MANAGER *bullet_manager)
{
    if( 0 >= tank->bullet_count){
        return;
    } else {
        tank->bullet_count--;
    }

	int i=0,lengh = bullet_manager->bullet_Count;
	for(i=0 ; i<lengh; i++)
	{
		if( 0 != bullet_manager->bullets[i].button )  // true, mean the bullet be FaShe ing
		{
			continue;
		}
		else
		{
		    bullet_manager->bullets[i].button = 1;
		    bullet_manager->bullets[i].host   = tank;
		    bullet_manager->bullets[i].id     = tank->id;
			bullet_manager->bullets[i].dir    = tank->dir;
			bullet_manager->bullets[i].color  = tank->color;
			bullet_manager->bullets[i].size   = tank->bullet_size;

			switch(tank->dir)
			{
			    case UP:
                    bullet_manager->bullets[i].x = tank->x;
                    bullet_manager->bullets[i].y = tank->y - tank->size;
                    break;

                case DOWN:
                    bullet_manager->bullets[i].x = tank->x;
                    bullet_manager->bullets[i].y = tank->y + tank->size;
                    break;

                case LEFT:
                    bullet_manager->bullets[i].x = tank->x - tank->size;
                    bullet_manager->bullets[i].y = tank->y;
                    break;

                case RIGHT:
                    bullet_manager->bullets[i].x = tank->x + tank->size;
                    bullet_manager->bullets[i].y = tank->y;
                    break;

                default : printf("tankFire()");
			}
			break;
		}
	}
}

TANK_MANAGER* create_Tank_Manager()
{
    TANK_MANAGER *tempT_B = (TANK_MANAGER*)malloc(sizeof(TANK_MANAGER));
    tempT_B->boom_count = 5;

    tempT_B->boom_manager = (BOOM*)calloc( tempT_B->boom_count, sizeof(BOOM) );
    tempT_B->tank_count = 0;
    tempT_B->nextTank = NULL;

    return tempT_B;
}

/**
 * 使用凶残的递归,释放掉tank链表,;
 * 注意 链表节点个数 == 递归深度
 * 链表末尾节点必须是NULL，否则会无限递归，最终召唤出Stack Overflow
 */
void destroy_TankLinkTable(TANK *tank)
{
    if( NULL != tank ){
        destroy_TankLinkTable(tank->nextTank); // 递归检查下一节点
        free(tank->nextTank); // 上面的递归结束后，表示当前节点下面的节点已经全部释放了！可以放心的咔嚓当前节点了~
        tank->nextTank = NULL; // 防止咸鱼翻身，确保不能再访问释放掉的内存~

    } else {
        return;

    }
}

void destroy_Tank_Manager(TANK_MANAGER *t_m)
{
    TANK *tank = t_m->nextTank;
    destroy_TankLinkTable(tank);
    return;
}


int addTankWithRandom(TANK_MANAGER *t_m)
{
    TANK* temp = create_TankWithRandom();
    TANK* others = t_m->nextTank;
    if( NULL != temp)
    {
        if(NULL != others)
        {
            while(checkTankHitTank(temp, others)) // fang zhi peng zhuang
            {
                srand(rand());
                temp->x = rand();
                temp->y = rand();
            }
            others = others->nextTank;
        }
        addTank(t_m,temp);
        return 0; //success
    }
    return 1; // fail

}

int delTank(TANK_MANAGER *t_m, TANK* tank)
{
    TANK *tankLinks = t_m->nextTank;

    while( NULL != tankLinks &&
           NULL != tank )
    {
        if( tank == tankLinks->nextTank)
        {
            tankLinks->nextTank = tank->nextTank;           // remove it from linkTable.

            free(tank);                                     // deleting it
            t_m->tank_count--;
            return 0; // success
        }
        tankLinks = tankLinks->nextTank;
    }
    return 1; // faile
}


void operateTankWithAI(TANK *tank, BULLET_MANAGER *b_m)
{
	switch(rand() % 13)
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
            tank->dir = RIGHT;
			break;

		case 8:
			break;

		case 9:
            tankFire(tank,b_m);
			break;

        default : tankFire(tank,b_m);

	}
	tank->is_stop = 0; //move
	return;
}

void Tank_Manager_Info(int x, int y, TANK_MANAGER* t_m, PCCOLOR color)
{
    TANK* tank = t_m->nextTank;
    char temp[32] = {};
    sprintf(temp, "Enemy Count %3d",t_m->tank_count-1);
    drawString(x, y++, LIGHT_MAGENTA,temp);

    while(NULL != tank)
    {
        sprintf(temp, "id = %2d,live = %2d ",tank->id, tank->live);
        drawString(x,y++, color, temp);
        tank = tank->nextTank;
    }

    sprintf(temp, "boom_Count %3d   ",t_m->boom_count);
    drawString(x, y++, LIGHT_MAGENTA,temp);
    int i = 0, lengh = t_m->boom_count;
    for(i=0; i<lengh; i++)
    {
        sprintf(temp, "live=%2d,size=%2d   ",t_m->boom_manager[i].live, t_m->boom_manager[i].size);
        drawString(x,y++, color, temp);
    }
    while( y < HEIGHT)
    {
        drawString(x,y++, color, "                 ");
    }


    return;
}
