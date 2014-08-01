#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "rolesdef.h"
#include "tank.h"
#include "body.h"

Tank*
create_tank(int x, int y, Dir dir){
    Tank* tank = (Tank*)malloc(sizeof(Tank));
    long drawable = 0b10111101;
    tank->body = create_body(drawable);
    tank->body->live = 1;
    tank->body->speed = 1;
    tank->body->x = x;
    tank->body->y = y;
    tank->body->w = 3;
    tank->body->h = 3;
    tank->body->drawable[UP]     = 0b010111101;
    tank->body->drawable[DOWN]     = 0b101111010;
    tank->body->drawable[LEFT]     = 0b011110011;
    tank->body->drawable[RIGHT] = 0b110011110;
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
}

void
move_tank_right(Tank* tank){
    move_body(tank->body, RIGHT);
}

void
tank_fire(){

}

void
draw_tank(Tank* tank){
    draw_body(tank->body);
}
