/////////////////////////////////////////////////////////////////////////////////////////////////
// ∷¤★●※┗←↑↓→
//█▇▆▅▄▃▂▁○○◇ゅ□△▽☆★▼▲■◆●♀√×卍卐→◢▓ ¤〓╋━┃┏┓┗┛╭ ╭∩╮(︶︿︶)╭∩╮
/////////////////////////////////////////////////////////////////////////////////////////////////
// #define drawString(x,y,color,string) gotoLocation(x,y); setTextColor(color); printf("%s",string);
//////////////////////////0////1///2////3////4////5///6////7/////8////9//
#include <ncurses.h>
#include <locale.h>
#include "draw.h"

static char BLOCK[ ][3]={"  ","■","¤","━","┃","┏","┓","┛","┗","☆"};

void
draw_test(){
	initscr();                      /* Start curses mode              */
	printw("Hello World !!!");      /* Print Hello World              */
	refresh();                      /* Print it on to the real screen */
	getch();                        /* Wait for user input */
	endwin();                       /* End curses mode                */
	return;
}

void
start_draw(){
	setlocale(LC_ALL, "");
	initscr();
}

void
end_draw(){
	endwin();
}

void
draw_text(char* text, Color color){

	printw(text);
}

void
draw_text_at(char* text, Color color, int x, int y){
	move(x,y);
	draw_text(text, RED);
}

void
refresh_draw(){
	refresh();
}


//void draw_block(int x,int y, Color color, int blockIndex );
