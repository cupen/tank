/*******************************************************\
 * Author:  Cupenoruler                                *
 * Email:   Cupenoruler@foxmail.com                    *
 * Notes:   Some functions about Console Tank.         *
 * Date:    2012-3-7 01:36:39                          *
\*******************************************************/
#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

#include "pcc32.h"
#include "initdef.h"

typedef struct _Boom
{
    int live;
    int x;
    int y;
    int size;
    int body;
    PCCOLOR color;
} BOOM;

typedef enum _DIR
{
	UP	  = 1,
	DOWN  = 2,
	LEFT  = 3,
	RIGHT = 4
} DIR;

typedef struct _TANK    // see the function which named creat_Tank in the "tank.c" file.
{
	int x;              //九宫格中心点横坐标
	int y;              //九宫格中心点纵坐标
	DIR dir;            //方向
	int live;           //生命
	int is_stop;  		// 1 or 0
	PCCOLOR color;
	int id; 			// good tank or bad tank
    int size;           // tank size, default value is 1
    int bullet_size;    // the size of tank's bullet; default value is 0
    int bullet_count;   // dafault value is 3;
    int killCount;
	struct _TANK *nextTank;
} TANK;

typedef struct _Bullet
{
	int x;               //子弹横坐标；
	int y;               //子弹纵坐标；
	DIR dir;             //方向
	int button;          //子弹开关；0无子弹，1有子弹
	PCCOLOR color;
	int size;
	int id;
	TANK *host;
} BULLET;

typedef struct _Bullet_Manager
{
	int bullet_Count;	// Bullet_Count <= 8  must be true
	BULLET *bullets;    // it is a bullet array
	// Bullet *nextBullet;
} BULLET_MANAGER;

typedef struct _Tank_Manager
{
    BOOM *boom_manager;
    int boom_count;
	int tank_count;
	TANK *nextTank;
} TANK_MANAGER;

#ifdef __cplusplus
extern "C"
{
#endif

    /////////////////////////////////////////////////
    //       file name: tank.c
    /////////////////////////////////////////////////
    /* tank 管理器*/
    TANK_MANAGER *create_Tank_Manager();
    void destroy_Tank_Manager(TANK_MANAGER *);
    TANK* create_Tank(int id, int size);
    TANK* create_Tank_FromTemplete(TANK templateTank);
    TANK* create_TankWithRandom();
    int  addTank(TANK_MANAGER *t_m, TANK* tank);
    int  delTank(TANK_MANAGER *t_m, TANK* tank);

    /* 使用tank管理器，统一管理tank的行为 */
    void move_Tanks(TANK_MANAGER*, BULLET_MANAGER*);
    void draw_Tanks(const TANK_MANAGER*);
    void clean_Tanks(const TANK_MANAGER*);

    /* tank 行为 */
    void moveTank(TANK *tank);
    void drawTank(TANK *tank);
    void cleanTank(TANK *tank);
    void tankFire(TANK *tank, const BULLET_MANAGER *);
    void operateTankWithAI(TANK *tank, BULLET_MANAGER*);

    void tankInfo(int x, int y,const TANK*, PCCOLOR);
    void operateTankWithInput(TANK *tank, BULLET_MANAGER*);


    ///////////////////////////////////////////////////////
    //        file name:  bullet.c
    ///////////////////////////////////////////////////////
    /* bullet 管理器 */
    BULLET_MANAGER* create_Bullet_Manager(const int bullet_count);
    void destroy_Bullet_Manager(BULLET_MANAGER*);
    void Bullet_Manager_Info(int x, int y, BULLET_MANAGER *b_m, PCCOLOR color);

    /* 使用Bullet管理器，统一管理Bullet的行为 */
    void move_Bullets(BULLET_MANAGER *b_m);
    void draw_Bullets(BULLET_MANAGER *b_m);
    void clean_Bullets(BULLET_MANAGER *b_m);

    /* Bullet的行为*/
    void drawBullet(BULLET *bullet);
    void moveBullet(BULLET *bullet); //嵌到move_Bullets()里了
    void cleanBullet(BULLET *bullet);// 嵌到clean_Bullets()里了
    void destroyBullet(BULLET* bullet);


    /////////////////////////////////////////////////////
    //        file name:  drawImp.c
    /////////////////////////////////////////////////////
    void drawBlock(int x,int y,PCCOLOR color, int blockIndex );
    void drawString(int x,int y,PCCOLOR color,char* str);
    void drawRectangle(int x,int y, int width, int height,PCCOLOR color);


    /////////////////////////////////////////////////////
    //        file name:  opetateHitEvent.c
    /////////////////////////////////////////////////////
    void operate_TankHitTank( TANK* currentTank, const TANK_MANAGER*);
    void operate_BulletHitTank( TANK_MANAGER*, const BULLET_MANAGER* );
    void operate_BulletHitBullet(BULLET_MANAGER* b_m);

    int checkTankHitTank(TANK* tank,TANK* other);
    int checkBulletHitTank(BULLET* bullet, TANK* tank);

    /////////////////////////////////////////////////////
    //        file name:  boom.c
    /////////////////////////////////////////////////////
    void addBoom(int x, int y, PCCOLOR color, TANK_MANAGER*);
    void drawBoom(BOOM*);
    void draw_Booms(BOOM* boom, int count);
    BOOM* createBoom(int x, int y, PCCOLOR color, int body_view_index);

#ifdef __cplusplus
}
#endif

#endif // RULES_H_INCLUDED
