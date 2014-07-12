/*
 * tank.h
 *
 *  Created on: 2014年7月6日
 *      Author: cupen
 */

#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED

#include "body.h"


typedef struct{
	Body* body;
	int id; 			// good tank or bad tank
    int killCount;
} Tank;

#ifdef __cplusplus
extern "C"
{
#endif

	Tank* create_tank(int x, int y, Dir dir);
	void move_tank_up(Tank* tank);
	void move_tank_down(Tank* tank);
	void move_tank_left(Tank* tank);
	void move_tank_right(Tank* tank);
	void draw_tank(Tank* tank);

#ifdef __cplusplus
extern "C"
}
#endif

#endif /* TANK_H_INCLUDED */
