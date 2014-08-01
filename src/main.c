#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "draw.h"
#include "body.h"
#include "tank.h"


void
start_game(){
    start_draw();
}

void
end_game(){
    getch();
    end_draw();
}

void
do_game(){
    int count = 10;
    while(count-- > 0){
        Tank* tank = create_tank(0, 1, UP);
        draw_tank(tank);
        refresh_draw();
        tank->body->dir = DOWN;
        draw_tank(tank);
        refresh_draw();
        tank->body->dir = LEFT;
    }
}

void input_by_human(){

}

int
main(void){
    start_game();
    do_game();
    end_game();
    return 0;
}
