cmake_minimum_required(VERSION 3.19)
project(LSCPatisserie C)

set(CMAKE_C_STANDARD 99)

add_executable(LSCPatisserie main.c "Fonctions gateaux.c" "Fonctions gateaux.h" Tools.c Tools.h)
