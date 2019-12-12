//
// main.cc
//
// Created by Stefan Stepanovic on 12/11/2019

#include "./maze.hpp"

int main()
{
    Maze maze;
    maze.height = 0;
    maze.width = 0;
    initializeMaze(&maze, 10, 8, 0, 0, 7, 5);
    addPassage(&maze, 0, 0, 1, 0);
    
    addPassage(&maze, 1, 0, 2, 0);
    addPassage(&maze, 2, 0, 3, 0);
    addPassage(&maze, 3, 0, 3, 1);
    addPassage(&maze, 3, 1, 3, 2);
    addPassage(&maze, 3, 2, 4, 2);
    addPassage(&maze, 4, 2, 4, 1);
    addPassage(&maze, 4, 1, 5, 1);
    addPassage(&maze, 5, 1, 5, 2);
    addPassage(&maze, 5, 2, 5, 3);
    addPassage(&maze, 5, 3, 5, 4);
    addPassage(&maze, 5, 4, 6, 4);
    addPassage(&maze, 6, 4, 7, 4);
    addPassage(&maze, 7, 4, 7, 5);

    BFSmaze(&maze, maze.entrance, maze.exit);

    printMazeStd(&maze);
    return 0;
}