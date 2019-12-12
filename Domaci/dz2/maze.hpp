//
// maze.h
//
// Created by Stefan Stepanovic on 12/11/2019

#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "../dz1/graph.hpp"

typedef struct Maze
{
    Graph* graph;
    int width, height;
    int entrance, exit;
} Maze;

// initialize maze with no pathways, height, width and entrance/exit coordinates
void initializeMaze(Maze* maze, int height, int width,
                    int entrance_x, int entrance_y,
                    int exit_x, int exit_y);

// mark field as passage
void addPassage(Maze* maze, int field1_x, int filed1_y,
                            int field2_x, int field2_y);

// print maze to std out
void printMazeStd(Maze* maze);

// Print maze to file
void printMazeFile(Maze* maze);

void printMaze(Maze* maze, std::ofstream os);

void freeMaze(Maze* maze, FILE* file);

void BFSmaze(Maze* maze, int node_start, int node_end);
