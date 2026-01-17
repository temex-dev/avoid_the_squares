cmake_minimum_required(VERSION 3.30)
project(avoid_the_squares)

set(CMAKE_CXX_STANDARD 20)
add_executable(avoid_the_squares main.cpp
                Enemies.cpp
                Enemies.h
                Player.cpp
                Player.h)

target_link_libraries(avoid_the_squares -lsfml-graphics -lsfml-window -lsfml-system)