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
        printf("��ǰ������ͣ������%d  ��ǰ����Ⱥ�������%d\n", Parking.car_number, Sidewalk.car_number);
        while (Parking.car_number != Parking_Lot_Size)
        {
            printf("����ʻ����\n");
            printf("�ó������ƺ�Ϊ��");
            scanf("%s",&car[i].license_plate_number);
            EntrySidewalk(&Sidewalk,car[i]);
            printf("�������복��\n");
            OutSidewalk(&Sidewalk,car[i]);
            Warehousing(&Parking,car[i]);
            time(&car[i].Entry_time);
            printf("��ǰ������ͣ������%d  ��ǰ����Ⱥ�������%d\n", Parking.car_number, Sidewalk.car_number);
     label: printf("����ͣ����S�������������⣨O��\n");
            scanf(" %c",&a);
            if(a == 'S') {
                i++;
            } else if(a == 'O'&&(Parking.car_number != 0))
            {
                time(&car[i].Departture_time);
                time_diff = difftime(car[i].Departture_time,car[i].Entry_time);
                printf("��⳵����%s ͣ��ʱ��:%fСʱ,Ӧ�շ��ã�%fԪ\n",car[i].license_plate_number,time_diff*5/60,time_diff*2);
                ex_warehousing(&Parking,&car[i]);
                i--;
                goto label;
            } else{
                printf("ERROR");
                break;
            }
        }
        if(Parking.car_number == Parking_Lot_Size) {
            printf("��������,����ͣ���ڱ����ͣ���ڱ��");

        }
        break;
    }
    return 0;
}
