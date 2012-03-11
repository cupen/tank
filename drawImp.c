/////////////////////////////////////////////////////////////////////////////////////////////////
// ¡Ë¡è¡ï¡ñ¡ù¤û§û©»¡û¡ü¡ı¡ú
//¨€¨~¨}¨|¨{¨z¨y¨x¡ğ¡ğ¡ó¤å¡õ¡÷¨Œ¡î¡ï¨‹¡ø¡ö¡ô¡ñ¡â¡Ì¡Á…d…e¡ú¨¨ˆ ¡è¡ş©ï©¥©§©³©·©»©¿¨q ¨q¡É¨r(¦á¦ä¦á)¨q¡É¨r
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "pcc32.h"
#define gotoLocation(x,y) gotoTextPos(x*2,y);
// #define drawString(x,y,color,string) gotoLocation(x,y); setTextColor(color); printf("%s",string);

//////////////////////////0////1///2////3////4////5///6////7/////8////9//
static char BLOCK[ ][3]={"  ","¡ö","¡è","©¥","©§","©³","©·","©¿","©»","¡î"};

void drawString(int x,int y,PCCOLOR color,char* str)
{
    if( (x<<1) > getLineWidth() ||
        y > getLineNum() ||
        x < 0 ||
        y < 0 )

    {
        return;
    }

	gotoLocation(x,y);
	setTextColor(color);
	printf("%s",str);
}

void drawBlock(int x,int y,PCCOLOR color, int blockIndex )
{
    if( (x<<1) > getLineWidth() ||
        y > getLineNum() ||
        x < 0 ||
        y < 0 )

    {
        return;
    }

	gotoLocation(x,y);
	setTextColor(color);
	printf("%2s",BLOCK[blockIndex]);
}

void drawRectangle(const int _x, const int _y, const int width, const int height, PCCOLOR color)
{
    int x = _x;
    int y = _y;

    drawBlock(x,y,color,5);
    while( x < width + _x - 1 )
    {
        x++;
        drawBlock(x,y,color,3);
    }

    drawBlock(x,y,color,6);
    while( y < height + _y -1 )
    {
        y++;
        drawBlock(x,y,color,4);
    }

    drawBlock(x,y,color,7);
    while( x > _x )
    {
        x--;
        drawBlock(x,y,color,3);
    }

    drawBlock(x,y,color,8);
    while( y > _y + 1 )
    {
        y--;
        drawBlock(x,y,color,4);
    }

	return;
}
