//
// Created by L on 2022/4/21.
//

#include "Sidewalk.h"

int InitSidewalk(LinkQueue *S)
{
    (*S).front = (QueuePtr) malloc(sizeof (QNode));
    if(!(*S).front)return OVERFLOW;
    (*S).rear = (*S).front;
    (*S).front = NULL;
    return OK;
}

int EntrySidewalk(LinkQueue *S,Car e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof (QNode));
    if(!p) return OVERFLOW;
    p->car = e;
    p->next = NULL;
    (*S).rear->next = p;
    (*S).rear = p;
    return OK;
}

int OutSidewalk(LinkQueue *S,Car *e)
{
    QueuePtr p;
    if(S->front == S->rear)return ERROE;
    p=(*S).front->next;
    *e = p->car;
    (*S).front->next=p->next;
    if((*S).rear == p) (*S).rear = (*S).front;
    free(p);
    return OK;
}
