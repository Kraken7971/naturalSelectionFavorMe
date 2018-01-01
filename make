#! /bin/bash
g++ -c $1
g++ $2 -o a.out -lsfml-graphics -lsfml-window -lsfml-system
