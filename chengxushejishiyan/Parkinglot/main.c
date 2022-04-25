//
// Created by L on 2022/4/21.
//
#include "stdio.h"
#include "ParkingLot.h"
#include "Sidewalk.h"

Car car[100];
Parking_Lot Parking;
LinkQueue Sidewalk;

int main()
{
    char a;
    int i = 0;
    double time_diff;
    InitParkingLot(&Parking);
    InitSidewalk(&Sidewalk);
    while(1) {
        printf("当前车库中停车数：%d  当前便道等候车辆数：%d\n", Parking.car_number, Sidewalk.car_number);
        while (Parking.car_number != Parking_Lot_Size)
        {
            printf("汽车驶入便道\n");
            printf("该车辆车牌号为：");
            scanf("%s",&car[i].license_plate_number);
            EntrySidewalk(&Sidewalk,car[i]);
            printf("汽车进入车库\n");
            OutSidewalk(&Sidewalk,car[i]);
            Warehousing(&Parking,car[i]);
            time(&car[i].Entry_time);
            printf("当前车库中停车数：%d  当前便道等候车辆数：%d\n", Parking.car_number, Sidewalk.car_number);
     label: printf("继续停车（S）还是汽车出库（O）\n");
            scanf(" %c",&a);
            if(a == 'S') {
                i++;
            } else if(a == 'O'&&(Parking.car_number != 0))
            {
                time(&car[i].Departture_time);
                time_diff = difftime(car[i].Departture_time,car[i].Entry_time);
                printf("离库车辆：%s 停车时间:%f小时,应收费用：%f元\n",car[i].license_plate_number,time_diff*5/60,time_diff*2);
                ex_warehousing(&Parking,&car[i]);
                i--;
                goto label;
            } else{
                printf("ERROR");
                break;
            }
        }
        if(Parking.car_number == Parking_Lot_Size) {
            printf("车库已满,车辆停靠在便道，停靠在便道");

        }
        break;
    }
    return 0;
}
