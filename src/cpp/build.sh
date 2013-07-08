#!/bin/bash
g++ -o world-population-simulator -std=c++0x -pthread debug.cpp worker.cpp world_object.cpp world.cpp person.cpp mother.cpp main.cpp
