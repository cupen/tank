/*
 * body.h
 *
 *  Created on: 2014年7月6日
 *      Author: cupen
 */
#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <stdint.h>
#include "draw.h"

typedef enum{
	UP	  = 0,
	DOWN  = 1,
	LEFT  = 2,
	RIGHT = 3
} Dir;

typedef struct{
	int live;
	int x;
	int y;
	int w;
	int h;
	int speed;
	Color color;
	Dir dir;
	uint64_t drawable[4];
} Body;

#ifdef __cplusplus
extern "C"
{
#endif

	void move_body(Body* body, Dir dir);
	Body* create_body(long drawable);
	void free_body(Body* body);
	void draw_body(const Body* body);
	int is_body_hited(const Body* body1, const  Body* body2);

#ifdef __cplusplus
extern "C"
}
#endif

#endif /* BODY_H_INCLUDED */
