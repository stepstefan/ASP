//
// main.cc
//
// Created by Stefan Stepanovic on 12/11/2019

#include "./maze.h"

int main()
{
    Maze maze;
    maze.height = 0;
    maze.width = 0;
    initializeMaze(&maze, 10, 10, 0, 0, 9, 5);
    // addPassage(&maze, 0, 0, 1, 0);

    printMazeStd(&maze);
    return 0;
}