//
// Created by L on 2022/4/21.
//

#include "ParkingLot.h"
//初始化停车场（栈）
int InitParkingLot(Parking_Lot *P) {
    (*P).base = (Car *) malloc(Parking_Lot_Size*sizeof (Car));
    if(!(*P).base) return OVERFLOW;
    (*P).top = (*P).base;
    (*P).stacksize = Parking_Lot_Size;
    (*P).car_number = 0;
    return OK;
}
//汽车入库
int Warehousing(Parking_Lot *P,Car e)
{
    if((*P).base - (*P).top == P->stacksize)return ERROE;
    *((*P).top)++ = e;
    (*P).car_number++;
    return OK;
}
//汽车出库
int ex_warehousing(Parking_Lot *P , Car *e)
{
    if((*P).base == (*P).top) return ERROE;
    *e = *(--(*P).top);
    (*P).car_number--;
    return OK;
}

