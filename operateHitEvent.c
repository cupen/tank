#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rolesdef.h"


int checkTankHitTank(TANK* tank_1,TANK* tank_2)
{
    unsigned char abs_x = abs( (tank_1->x) - (tank_2->x) );
    unsigned char abs_y = abs( (tank_1->y) - (tank_2->y) );
    int space = tank_1->size + tank_2->size + 1; // you dai WanShan

    if( abs_x<space && abs_y<space ){
        return 1; // It's mean the Tank one is hiting Tank two;

    } else {
        return 0;

    }
}

int checkBulletHitTank(BULLET* bullet, TANK* tank)
{
    unsigned char abs_x = abs( (bullet->x) - (tank->x) );
    unsigned char abs_y = abs( (bullet->y) - (tank->y) );
    int space = bullet->size + tank->size + 1; // you dai WanShan

    if( abs_x<space && abs_y<space ){
        return 1; // It's mean the Tank one is hiting Tank two;

    } else {
        return 0;

    }
}
int checkBulletHitBullet(BULLET* bullet, BULLET* other_bullet)
{
    unsigned char abs_x = abs( (bullet->x) - (other_bullet->x) );
    unsigned char abs_y = abs( (bullet->y) - (other_bullet->y) );
    int space = bullet->size + other_bullet->size + 1;

    if( abs_x<space && abs_y<space ){
        return 1; // It's mean the Tank one is hiting Tank two;

    } else {
        return 0;

    }
}

void operate_BulletHitTank( TANK_MANAGER* t_m, const BULLET_MANAGER* b_m )
{
    TANK* tank = t_m->nextTank;
    BULLET* bullets = b_m->bullets;
    int i = 0;
    const int lengh = b_m->bullet_Count;

    while(NULL != tank)
    {
        for(i=0; i<lengh; i++)
        {
            if(0 == bullets[i].button ||    // the valu=0 was mean the bullet is not live
               bullets[i].id == tank->id ){ // don't hit ZiJiaRen

                continue;
            }

            if(checkBulletHitTank(bullets+i, tank))
            {
                //tankInfo(WIDTH, 0, tank, MAGENTA);
                bullets[i].host->killCount++;
                tank->live--;
                destroyBullet( bullets+i );
                if( 0 >= tank->live)
                {
                    if( 1 == tank->id)
                    {
                        drawString(4,4, GREEN,"you are dead!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    }
                }
            }
        }
        tank = tank->nextTank;
    }
}

void operate_TankHitTank(TANK* currentTank, const TANK_MANAGER* t_m)
{
    TANK* linkTable = t_m->nextTank;
    while( NULL != linkTable )
    {
        if(currentTank == linkTable)
        {
            linkTable = linkTable->nextTank;
            continue;
        }

        if(checkTankHitTank( currentTank,linkTable))
        {
            switch(currentTank->dir)
            {
                case UP   : currentTank->y++; break;
                case DOWN : currentTank->y--; break;
                case LEFT : currentTank->x++; break;
                case RIGHT: currentTank->x--; break;
                default: break;
            }
        }
        linkTable = linkTable->nextTank;
    }
    return;
}

void operate_BulletHitBullet(BULLET_MANAGER* b_m)
{
    BULLET* bullets = b_m->bullets;
    int lengh = b_m->bullet_Count;
    int i = 0,j = 0;

    for(; i < lengh; i++)
    {
        if( 0 == bullets[i].button)
        {
            continue;
        }

        for(j= i+1; j < lengh; j++)
        {
            if( 0 == bullets[j].button ||
               bullets[i].host == bullets[j].host )
            {
                continue;
            }

            if(checkBulletHitBullet(bullets + i, bullets + j))
            {
                destroyBullet( bullets+i );
                destroyBullet( bullets+j );
                break;
            }
        }
    }
}

/*
////////////////////////////////////////////////
//  ! you dai wan shan  I'm plan to add two attributes which named "old_x","olde_y" for TANK .
////////////////////////////////////////////////
void operateTankHitTank(TANK_MANAGER* t_m)
{
    TANK* tank = t_m->nextTank;
    TANK* others = NULL;

    while(NULL != tank)
    {
        others = tank->nextTank;
        while(NULL != others )
        {
            if(checkTankHitTank(tank,others))
            {
                switch(tank->dir)
                {
                    case UP   : tank->y++; break;
                    case DOWN : tank->y--; break;
                    case LEFT : tank->x++; break;
                    case RIGHT: tank->x--; break;
                    default: break;
                }
            }
            others = others->nextTank;
        }
        tank = tank->nextTank;
    }
}
*/
