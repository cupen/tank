/*
 * body.c
 *
 *  Created on: 2014年7月6日
 *      Author: cupen
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "body.h"
#include "draw.h"


void
move_body(Body* body, Dir dir){
	body->dir = dir;
	switch(dir){
	case UP:
		body->y -= body->speed;
		break;

	case DOWN:
		body->y += body->speed;
		break;

	case LEFT:
		body->x -= body->speed;
		break;

	case RIGHT:
		body->y += body->speed;
		break;

	default:

		break;
	}
	return;
}

Body*
create_body(long drawable){
	Body* body = (Body*)malloc(sizeof(Body));
	body->x = 0;
	body->y = 0;
	body->w = 0;
	body->h = 0;
	body->live = 0;
	body->speed = 1;
	body->dir = 0;
	body->drawable[UP] = drawable;
	body->drawable[DOWN] = drawable;
	body->drawable[LEFT] = drawable;
	body->drawable[RIGHT] = drawable;
	return body;
}

void
free_body(Body* body){
	free(body);
}

void
draw_body(const Body* body){
	int blockCount = body->w * body->h;
	int blockForDraw = body->drawable[body->dir];
	while(blockCount--){
		for(int hInc = body->h - 1; hInc >= 0; hInc--){
			for(int wInc = body->w - 1; wInc >= 0; wInc--){
				if (blockForDraw & 0x1){
					draw_text_at("██",RED, body->x + wInc, body->y + hInc);
				}
				blockForDraw >>= 1;
			}
		}
	}
}


inline static int
_is_point_in_rectangle(int pointX, int pointY, int rectX, int rectY, int rectW, int rectH){
	return (
		pointX >= rectX
		&& pointX <= (rectX + rectW)
		&& pointY >= rectY
		&& pointY <= (rectY + rectH)
	);
}

int
is_body_hited(const Body* body1, const Body* body2){
	return _is_point_in_rectangle(
				body1->x,
				body1->y,
				body2->x + body1->w,
				body2->y + body1->h,
				body2->w + body1->w,
				body2->h + body2->h
			);
}
