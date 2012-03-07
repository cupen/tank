/*******************************************************\
* Author:  Cupenoruler                                  *
* Email:   Cupenoruler@foxmail.com                      *
* Notes:   Some functions about Console Tank.           *
* License: Some toy function, Just for fun.             *
* Date:    2012-3-7 00:28:39                            *
\*******************************************************/

#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

#include "pcc32.h"

#define  Width      32
#define  Height     20
#define  M          5   //敌方数量
#define  N          3   //子弹数量

typedef enum _DIR
{
	UP	  = 1,
	DOWN  = 2,
	LEFT  = 3,
	RIGHT = 4
} DIR;

typedef struct _TANK
{
	int x;              //九宫格中心点横坐标
	int y;              //九宫格中心点纵坐标
	DIR dir;            //方向
	int live;           //生命
	int is_stop;  		// 1 or 0
	PCCOLOR color;
	int id; 			// good tank or bad tank
    int size;     // tank size, default value = 2
	struct _TANK *nextTank;
} TANK;

typedef struct _Bullet
{
	int x;               //子弹横坐标；
	int y;               //子弹纵坐标；
	DIR dir;             //方向
	int button;          //子弹开关；0无子弹，1有子弹
	PCCOLOR color;
	int id;
	// struct _Bullet *nextBullet;
} BULLET;

typedef struct _Bullet_Manager
{
	int bullet_ID;
	int bullet_Count;	// Bullet_Count <= 8  must be true
	BULLET *bullets;    // it is a bullet array
	// Bullet *nextBullet;
} BULLET_MANAGER;
//{1,3,{0,0,UP,0,BLACK}, {0,0,UP,0,BLACK},{0,0,UP,0,BLACK}}

typedef struct _Tank_Manager
{
    BULLET_MANAGER *bullet_manager;
	int count;
	TANK *nextTank;
} TANK_MAGAGER;

#ifdef __cplusplus
extern "C"
{
#endif

    /* tank 管理器*/
    TANK_MAGAGER *create_Tank_Manager();
    TANK* create_Tank(int id, int size);
    TANK* create_Tank_FromTemplete(TANK templateTank);
    int  addTank(TANK_MAGAGER *t_m, TANK* tank);
    int  delTank(TANK_MAGAGER *t_m, const TANK* tank);
    void getInput(TANK *tank, BULLET_MANAGER *b_m);

    /* 使用tank管理器，统一管理tank的行为 */
    void move_Tanks(const TANK_MAGAGER *t_m);
    void draw_Tanks(const TANK_MAGAGER *t_m);

    /* tank 行为 */
    void moveTank(TANK *tank);
    void drawTank(TANK *tank);
    void cleanTank(TANK *tank);
    void tankFire(TANK *tank, BULLET_MANAGER *b_m);
    void operateTankWithAI(TANK *tank);

    /* bullet 管理器 */
    BULLET_MANAGER* create_Bullet_Manager(const int bullet_count);
    void destroy_Bullet_Manager(BULLET_MANAGER *b_m);
    void Bullet_Manager_Info(int x, int y, BULLET_MANAGER *b_m, PCCOLOR color);

    /* 使用Bullet管理器，统一管理Bullet的行为 */
    void move_Bullets(BULLET_MANAGER *b_m);
    void draw_Bullets(BULLET_MANAGER *b_m);
    void clean_Bullets(BULLET_MANAGER *b_m);

    /* Bullet的行为*/
    void drawBullet(BULLET *bullet);
    // void moveBullet(BULLET *bullet); 嵌到move_Bullets()里了
    // voif cleanBullet(BULLET *bullet); 嵌到clean_Bullets()里了

    /* pcc32ex */
    void drawBlock(int x,int y,PCCOLOR color, int blockIndex );
    void drawString(int x,int y,PCCOLOR color,char* str);
    void drawRectangle(int x,int y, int width, int height);

#ifdef __cplusplus
}
#endif

#endif // RULES_H_INCLUDED
