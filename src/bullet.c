#include <stdio.h>
#include <stdlib.h>
#include "rolesdef.h"

//void
//destroy_bullet(Bullet* bullet){
//    bullet->button = 0;
//    draw_block(bullet->x, bullet->y, BLACK, 0);
//    clean_bullet(bullet);
//    bullet->host->bullet_count++;
//    bullet->host = NULL;
//    return;
//}
//
//
//void
//clean_bullets(BulletManager *b_m){
//    if( NULL == b_m){
//		printf("Bullet_Manager is null;");
//		return;
//	}
//	int i=0,lengh = b_m->bullet_Count;
//	for(i=0 ; i<lengh; i++){
//		if( b_m->bullets[i].button )  // true, mean the bullet be FaShe
//		{
//			switch(b_m->bullets[i].dir)
//			{
//			    case UP:
//                    draw_block( b_m->bullets[i].x, b_m->bullets[i].y+1, BLACK, 0);
//                    break;
//
//                case DOWN:
//                    draw_block( b_m->bullets[i].x, b_m->bullets[i].y-1, BLACK, 0);
//                    break;
//
//                case LEFT:
//                    draw_block( b_m->bullets[i].x+1, b_m->bullets[i].y, BLACK, 0);
//                    break;
//
//                case RIGHT:
//                    draw_block( b_m->bullets[i].x-1, b_m->bullets[i].y, BLACK, 0);
//                    break;
//
//                default: printf("void clean_Bullets(BULLET_MANAGER *b_m)");
//			}
//		}
//	}
//}
//
//void
//move_bullets(BulletManager *b_m){
//	if( NULL == b_m){
//		printf("Bullet_Manager is null;");
//		return;
//	}
//
//	int i=0,lengh = b_m->bullet_Count;
//	for(i=0 ; i<lengh; i++)	{
//		// shootting
//		if( b_m->bullets[i].button ){
//			switch(b_m->bullets[i].dir){
//				case UP:
//					b_m->bullets[i].y--;
//					break;
//
//				case DOWN:
//					b_m->bullets[i].y++;
//					break;
//
//				case LEFT:
//					b_m->bullets[i].x--;
//					break;
//
//				case RIGHT:
//					b_m->bullets[i].x++;
//					break;
//			}
//
//			if( b_m->bullets[i].x < 0 ||
//				b_m->bullets[i].x > WIDTH - 1||
//				b_m->bullets[i].y < 0 ||
//				b_m->bullets[i].y > HEIGHT-1 ){
//                destroy_bullet( (b_m->bullets)+i );
//			}
//		}
//	}
//	return;
//}
//
//
//BulletManager*
//create_bullet_manager(const int bullet_count){
//    BulletManager *tempB_M = (BulletManager*)malloc(sizeof(BulletManager));
//    tempB_M->bullet_Count = bullet_count;
//    tempB_M->bullets = calloc( bullet_count, sizeof(Bullet));
//
//    //memset(tempB_M->bullets, 0, bullet_count);
//    return tempB_M;
//}
//
//void
//destroy_bullet_manager(BulletManager *bullet_manager){
//    free(bullet_manager->bullets);
//    free(bullet_manager);
//    return;
//}
//
//void
//bullet_manager_info(int x, int y, BulletManager *b_m, PCCOLOR color){
//    char temp[32] = {};
//    sprintf(temp, "bullet_Count %d",b_m->bullet_Count);
//    draw_string(x,y++, LIGHT_MAGENTA,temp);
//
//    int i = 0, lengh = b_m->bullet_Count;
//    for(i=0; i < lengh; i++)    {
//        sprintf(temp, "bullet %d, %2d, %-2d",b_m->bullets[i].button, b_m->bullets[i].x, b_m->bullets[i].y);
//        draw_string(x,y++, color, temp);
//    }
//    return;
//}
