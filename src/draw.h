/*
 * draw.h
 *
 *  Created on: 2014年7月6日
 *      Author: cupen
 */

#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

typedef enum Color{
	RED 	= 1,
	GREEN	= 2,
	BLACK	= 3
} Color;


#ifdef __cplusplus
extern "C"
{
#endif

	void start_draw();
	void end_draw();
	void refresh_draw();

	void draw_test();
	void draw_text(char* str, Color color);
	void draw_text_at(char* text, Color color, int x, int y);

//	void draw_block(int x,int y, Color color, int blockIndex );
//	void draw_rectangle(const int x, const int y, const int width, const int height, Color color);

#ifdef __cplusplus
}
#endif

#endif /* DRAW_H_INCLUDED */
