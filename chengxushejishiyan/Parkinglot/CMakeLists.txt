cmake_minimum_required(VERSION 3.21)
project(Parkinglot)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Parkinglot
        main.c
        ParkingLot.c
        ParkingLot.h Sidewalk.c Sidewalk.h)
