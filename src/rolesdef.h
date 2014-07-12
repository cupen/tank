/*******************************************************\
 * Author:  Cupenoruler                                *
 * Email:   Cupenoruler@foxmail.com                    *
 * Notes:   Some functions about Console Tank.         *
 * Date:    2012-3-7 01:36:39                          *
\*******************************************************/
#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

#include <stdint.h>
#include "body.h"
#include "bullet.h"
#include "tank.h"
#include "boom.h"
#include "ui.h"


typedef struct {
	int bullet_Count;	// Bullet_Count <= 8  must be true
	Bullet* bullets;    // it is a bullet array
	// Bullet *nextBullet;
} BulletManager;

typedef struct {
    Boom *boom_manager;
    int boom_count;
	int tank_count;
	Tank *nextTank;
} TankManager;

#ifdef __cplusplus
extern "C"
{
#endif

//    /////////////////////////////////////////////////
//    //       file name: tank.c
//    /////////////////////////////////////////////////
//    /* tank 管理器*/
//    TankManager *create_tank_manager();
//    void destroy_tank_manager(TankManager *);
//    Tank* create_tank(int id, int size);
//    Tank* create_tank_from_templete(Tank templateTank);
//    Tank* create_tank_with_random();
//    int  add_tank(TankManager *t_m, Tank* tank);
//    int  del_tank(TankManager *t_m, Tank* tank);
//
//    /* 使用tank管理器，统一管理tank的行为 */
//    void move_tanks(TankManager*, BulletManager*);
//    void draw_tanks(const TankManager*);
//    void clean_tanks(const TankManager*);
//
//    /* tank 行为 */
//    void move_tank(Tank *tank);
//    void draw_tank(Tank *tank);
//    void clean_tank(Tank *tank);
//    void tank_fire(Tank *tank, const BulletManager *);
//    void operate_tank_with_AI(Tank *tank, BulletManager*);
//
//
//    void operate_tank_with_input(Tank *tank, BulletManager*);
//
//
//    ///////////////////////////////////////////////////////
//    //        file name:  bullet.c
//    ///////////////////////////////////////////////////////
//    /* bullet 管理器 */
//    BulletManager* create_bullet_manager(const int bullet_count);
//    void destroy_bullet_manager(BulletManager*);
//
//    /* 使用Bullet管理器，统一管理Bullet的行为 */
//    void move_bullets(BulletManager *b_m);
//    void draw_bullets(BulletManager *b_m);
//    void clean_bullets(BulletManager *b_m);
//
//    /* Bullet的行为*/
//    void draw_bullet(Bullet *bullet);
//    void move_bullet(Bullet *bullet); //嵌到move_Bullets()里了
//    void clean_bullet(Bullet *bullet);// 嵌到clean_Bullets()里了
//    void destroy_bullet(Bullet* bullet);
//
//    /////////////////////////////////////////////////////
//    //        file name:  opetateHitEvent.c
//    /////////////////////////////////////////////////////
//    void operate_tank_hit_tank( Tank* currentTank, const TankManager*);
//    void operate_bullet_hit_tank( TankManager*, const BulletManager*);
//    void operate_bullet_hit_bullet(BulletManager* b_m);
//
//    int check_tank_hit_tank(Tank* tank,Tank* other);
//    int check_bullet_hit_tank(Bullet* bullet, Tank* tank);

#ifdef __cplusplus
}
#endif

#endif // RULES_H_INCLUDED

