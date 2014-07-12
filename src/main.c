#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "body.h"


#define ENEMY_COUNT         4                 // 敌方数量
#define BULLET_COUNT        ENEMY_COUNT*3+3 // 子弹总数- 敌方&玩家
//#define INPUT_ARRAY_LENGH   16

int isRunning = 1;

//////////////////////////////////////////////////////
//			基本设置
//////////////////////////////////////////////////////
void
initialize(){

}

//void
//getInput(){
//    if(kbhit())
//    return;
//}

int
main(void){
	start_draw();

	Body* body = create_body();
	body->w = 3;
	body->h = 3;
	body->drawable = 0b101111010;
	draw_body(body);
//	draw_text_at("██", RED, 13, 13);
	draw_text_at("是啊", RED, 13, 13);
	refresh_draw();
	getch();
	end_draw();
    return 0;
}

#include <ncurses.h>

int main1()
{       int ch;

        initscr();                      /* Start curses mode            */
        raw();                          /* Line buffering disabled      */
        keypad(stdscr, TRUE);           /* We get F1, F2 etc..          */
        noecho();                       /* Don't echo() while we do getch */

        printw("Type any character to see it in bold\n");
        ch = getch();                   /* If raw() hadn't been called
                                         * we have to press enter before it
                                         * gets to the program          */
        if(ch == KEY_F(1))              /* Without keypad enabled this will */
                printw("F1 Key pressed");/*  not get to us either       */
                                        /* Without noecho() some ugly escape
                                         * charachters might have been printed
                                         * on screen                    */
        else
        {       printw("The pressed key is ");
                attron(A_BOLD);
                printw("%c", ch);
                attroff(A_BOLD);
        }
        refresh();                      /* Print it on to the real screen */
        getch();                        /* Wait for user input */
        endwin();                       /* End curses mode                */

        return 0;
}

