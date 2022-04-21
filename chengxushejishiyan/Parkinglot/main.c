//
// Created by L on 2022/4/21.
//
#include "stdio.h"
#include "time.h"

int main()
{
    time_t timep;
    time(&timep);
    printf("%s", ctime(&timep));
}