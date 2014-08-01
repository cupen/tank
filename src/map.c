/*
 * map.c
 *
 *  Created on: 2014年7月16日
 *      Author: cupen
 */
#include "map.h"
#include "body.h"

static Body globalMap;

void
set_map(int w, int h){
	globalMap.x = 0;
	globalMap.y = 0;
	globalMap.w = w;
	globalMap.h = h;
}

int is_outside_of_map(const Body* body){
	return is_body_hited(&globalMap, body);
}



