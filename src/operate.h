#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#ifndef OPERATE_H_
#define OPERATE_H_


#define KEY_M 'm'

typedef Command char;

typedef struct{
    char* cmdList;
    int size;
    CmdQueue* next;
} CmdQueue;


CmdQueue*
create_cmdqueue(int size){
    CmdQueue* bean = (CmdQueue*)malloc(sizeof(CmdQueue));
    bean->cmdList = (char*)malloc(size);
    bean->size = size;
    bean->next = NULL;
    return bean;
}

Command
cmdqueue_pop(CmdQueue* queue){

}

void
cmdqueue_insert(CmdQueue* queue, Command cmd){

}

void
cmdqueue_add(CmdQueue* queue, Command cmd){
    char* nextCmd = queue->cmdList;
    for (int i = 0; i < queue->size; i++) {
        nextCmd += i;
        if( *nextCmd == 0){
            *nextCmd = cmd;
            return;
        }
    }
    // 当前队列不够用则扩展一下
    if( !queue->next ){
        queue->next = create_cmdqueue( queue->size * 2 );
    }
    return cmdqueue_add( queue->next );
}




#endif
