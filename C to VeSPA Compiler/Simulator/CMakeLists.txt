cmake_minimum_required(VERSION 3.29)
project(RocketSim C)

set(CMAKE_C_STANDARD 23)

add_executable(RocketSim Log/Logger.c main.c)
