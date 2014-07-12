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
	UP	  = 1,
	DOWN  = 2,
	LEFT  = 3,
	RIGHT = 4
} Dir;

typedef struct{
	uint8_t live;
	uint8_t x;
	uint8_t y;
	uint8_t w;
	uint8_t h;
	Color color;
	Dir dir;
	uint64_t drawable;
} Body;

#ifdef __cplusplus
extern "C"
{
#endif

	void move_body(Body* body);
	Body* create_body(void);
	void free_body(Body* body);
	void draw_body(Body* body);
	int is_body_hited(Body* body1, Body* body2);

#ifdef __cplusplus
extern "C"
}
#endif

#endif /* BODY_H_INCLUDED */
