//
// Created by L on 2022/4/21.
//

#include "ParkingLot.h"

int InitParkingLot(Parking_Lot *P) {
    (*P).base = (Car *) malloc(Parking_Lot_Size*sizeof (Car));
    if(!(*P).base) return OVERFLOW;
    (*P).base = (*P).top;
    (*P).stacksize = Parking_Lot_Size;
    return OK;
}

int Warehousing(Parking_Lot *P,Car e)
{
    if((*P).base - (*P).top == P->stacksize)return ERROE;
    *((*P).top)++ = e;
    return OK;
}

int ex_warehousing(Parking_Lot *P , Car *e)
{
    if((*P).base == (*P).top) return ERROE;
    *e = *(--(*P).top);
    return OK;
}

