cmake_minimum_required(VERSION 3.26)
project(CPP_Assignment_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP_Assignment_4 main.cpp
        GameSpecs.h
        City.cpp
        City.h
        Human.cpp
        Human.h
        Organism.cpp
        Organism.h
        Zombie.cpp
        Zombie.h)
