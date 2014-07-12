/*
 * tank.h
 *
 *  Created on: 2014年7月6日
 *      Author: cupen
 */

#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED


typedef struct{
	Body body;
	int id; 			// good tank or bad tank
    int size;           // tank size, default value is 1
    int bullet_size;    // the size of tank's bullet; default value is 0
    int bullet_count;   // dafault value is 3;
    int killCount;
} Tank;

#ifdef __cplusplus
extern "C"
{
#endif

	Body* tank_info(const Tank*);

#ifdef __cplusplus
extern "C"
}
#endif

#endif /* TANK_H_INCLUDED */
