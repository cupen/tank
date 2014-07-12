/*
 * bullet.h
 *
 *  Created on: 2014年7月6日
 *      Author: cupen
 */

#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "tank.h"

typedef struct{
	int id;
	Body body;
	Tank* host;
} Bullet;


#endif /* BULLET_H_INCLUDED */
