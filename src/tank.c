#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "rolesdef.h"
#include "tank.h"
#include "body.h"

Tank*
create_tank(int x, int y, Dir dir){
	Tank* tank = (Tank*)malloc(sizeof(Tank));
	tank->body = create_body();
 	tank->body->live = 1;
 	tank->body->speed = 1;
 	tank->body->x = x;
	tank->body->y = y;
 	tank->body->w = 3;
 	tank->body->h = 3;
 	tank->body->drawable = 0b101111010;
 	return tank;
}

void
move_tank_up(Tank* tank){
	move_body(tank->body, UP);
}

void
move_tank_down(Tank* tank){
	move_body(tank->body, DOWN);
}

void
move_tank_left(Tank* tank){
	move_body(tank->body, LEFT);
	;
}

void
move_tank_right(Tank* tank){
	move_body(tank->body, RIGHT);
	;
}

void
draw_tank(Tank* tank){
	draw_body(tank->body);
}
