//
// Created by L on 2022/4/21.
//

#ifndef PARKINGLOT_SIDEWALK_H
#define PARKINGLOT_SIDEWALK_H

#include "ParkingLot.h"

typedef struct QNode{
    Car car;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
    int car_number;
}LinkQueue;

extern int InitSidewalk(LinkQueue *S);
extern int EntrySidewalk(LinkQueue *S,Car e);
extern int OutSidewalk(LinkQueue *S,Car e);
#endif //PARKINGLOT_SIDEWALK_H
