///////////////////////////////////////////////////////////////
// ¡Ë¡è¡ï¡ñ¡ù¤û§û©»¡û¡ü¡ı¡ú
//
//
//
//
//
//
//
//¨€¨~¨}¨|¨{¨z¨y¨x¡ğ¡ğ¡ó¤å¡õ¡÷¨Œ¡î¡ï¨‹¡ø¡ö¡ô¡ñ¡â¡Ì¡Á…d…e¡ú¨¨ˆ ¡è¡ş©ï©¥©§©³©·©»©¿¨q ¨q¡É¨r(¦á¦ä¦á)¨q¡É¨r
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pcc32.h"

#define gotoLocation(x,y) gotoTextPos(x*2,y);
// #define drawString(x,y,color,string) gotoLocation(x,y); setTextColor(color); printf("%s",string);


static char BLOCK[ ][3]={"  ","¡ö","¡è","©¥","©§","¨q ","¨r","¨t","¨s"};

void drawString(int x,int y,PCCOLOR color,char* str)
{
	gotoLocation(x,y);
	setTextColor(color);
	printf("%s",str);
}

void drawBlock(int x,int y,PCCOLOR color, int blockIndex )
{
	// drawString(x,y,color,BLOCK[blockIndex]);
	gotoLocation(x,y);
	setTextColor(color);
	printf("%2s",BLOCK[blockIndex]);
}

void drawRectangle(int x,int y, int width, int height)
{
	return;
}

