//
// Created by L on 2022/4/21.
//

#ifndef PARKINGLOT_MODULAR_H
#define PARKINGLOT_MODULAR_H

#include "time.h"
#include "malloc.h"


#define Parking_Lot_Size 3
#define OK 1
#define ERROE -1
#define OVERFLOW -2

typedef struct {
    char license_plate_number[3];
    time_t Entry_time;
    time_t Departture_time;
}Car;

typedef struct {
    Car *base;
    Car *top;
    int car_number;
    int stacksize;
}Parking_Lot;

extern int InitParkingLot(Parking_Lot *P);
extern int Warehousing(Parking_Lot *P,Car e);
extern int ex_warehousing(Parking_Lot *P , Car *e);
#endif //PARKINGLOT_MODULAR_H
