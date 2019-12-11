//
// maze.cpp
//
// Created by Stefan Stepanovic on 12/11/2019

#include "./maze.h"

int calcNodeFromCoordinates(Maze* maze, int x, int y)
{
    return maze->width * y + x;
}

void initializeMaze(Maze* maze, int height, int width,
                   int entrance_x, int entrance_y,
                   int exit_x, int exit_y)
{
    if (height <= 0 || width <= 0 ||
        entrance_x < 0 || entrance_x >= width ||
        entrance_y < 0 || entrance_y >= height ||
        exit_x < 0 || exit_x >= width ||
        exit_y < 0 || exit_y >= height)
    {
        printf("Invalid maze init params!\n");
    }
    else
    {
        maze->height = height;
        maze->width = width;
        maze->graph = reinterpret_cast<Graph*>(calloc(1, sizeof(Graph)));
        initializeGraph(maze->graph, height*width);
        // maze->data = reinterpret_cast<int**>(calloc(height, sizeof(int*)));
        // for (int i = 0; i < height; i++)
        // {
        //     maze->data[i] = reinterpret_cast<int*>(calloc(width, sizeof(int)));
        // }

        // Compiler check
        // for (int i = 0; i < height; i++)
        // {
        //     for (int j = 0; j < width; j++)
        //     {
        //         maze->data[i][j] = 0;  // code for wall
        //     }
        // }

        maze->entrance = calcNodeFromCoordinates(maze, entrance_x, entrance_y);
        maze->exit = calcNodeFromCoordinates(maze, exit_x, exit_y);

        // set entrance and exit as pathways
        // maze->data[entrance_y][entrance_x] = 2;  // code for entrance
        // maze->data[exit_y][exit_y] = 3;  // code for exit

        // if ((entrance_x == exit_x + 1 && entrance_y == exit_y) ||
        //     (entrance_x == exit_x - 1 && entrance_y == exit_y) ||
        //     (entrance_x == exit_x && entrance_y == exit_y + 1) ||
        //     (entrance_x == exit_x && entrance_y == exit_y - 1))
        // {
        //     addVertex(maze->graph, maze->entrance, maze->exit);
        // }
    }
}

void addPassage(Maze* maze, int field1_x, int field1_y,
                            int field2_x, int field2_y)
{
    if (field1_x < 0 || field1_x >= maze->width ||
        field1_y < 0 || field1_y >= maze->height ||
        field2_x < 0 || field2_x >= maze->width ||
        field2_y < 0 || field2_y >= maze->height)
    {
        printf("Invalid field params!\n");
    }
    else
    {
        if ((field1_x == field2_x + 1 && field1_y == field2_y) ||
            (field1_x == field2_x - 1 && field2_y == field2_y) ||
            (field1_x == field2_x && field1_y == field2_y + 1) ||
            (field1_x == field2_x && field1_y == field2_y - 1))
        {
            int node1 = calcNodeFromCoordinates(maze, field1_x, field1_y);
            int node2 = calcNodeFromCoordinates(maze, field2_x, field2_y);

            addVertex(maze->graph, node1, node2);
        }
        else
        {
            printf("Fields are not adjacent!\n");
        }
    }
}

void freeMaze(Maze* maze)
{
    freeGraph(maze->graph);
}

void printMazeStd(Maze* maze)
{
    if (maze->height < 80 && maze->width < 50)
    {
        int graph_size = maze->height * maze->width;
        bool* visited = reinterpret_cast<bool*>(calloc(graph_size, sizeof(bool)));
        for (int i = 0; i < graph_size; i++)
        {
            visited[i] = false;
        }
        printf("|");
        for (int j = 0; j < maze->width*2; j++)
        {
            printf("-");
        }
        printf("\n");
        for (int i = 0; i < maze->height; i++)
        {
            printf("|");
            for (int j = 0; j < maze->width; j++)
            {
                int node = calcNodeFromCoordinates(maze, j, i);
                if (node == maze->entrance)
                {
                    printf("O");
                }
                else if (node == maze->exit)
                {
                    printf("X");
                }
                else
                {
                    printf(" ");
                }

                if (j < maze->width - 1)
                {
                    int right_node = calcNodeFromCoordinates(maze, j+1, i);
                    if (maze->graph->data[node][right_node])
                    {
                        printf(" ");
                    }
                    else
                    {
                        printf("|");
                    }
                }
            }
            printf("|\n|");
            if (i < maze->height-1)
            {
                for (int j = 0; j < maze->width; j++)
                {
                    int node = calcNodeFromCoordinates(maze, j, i);
                    int down_node = calcNodeFromCoordinates(maze, j, i+1);
                    if (maze->graph->data[node][down_node])
                    {
                        printf("%d", maze->graph->data[node][down_node]);
                    }
                    else
                    {
                        printf("-");
                    }
                    if (j < maze->width - 1)
                    {
                        printf("-");
                    }
                }
                printf("|\n");
            }
        }
        for (int j = 0; j < maze->width*2; j++)
        {
            printf("-");
        }
        printf("\n");
    }
    else
    {
        printf("Cannot output to std maze larger than 80x50!\n");
    }
}

void printMazeFile(Maze* maze, FIlE* file)
{
    int graph_size = maze->height * maze->width;
        bool* visited = reinterpret_cast<bool*>(calloc(graph_size, sizeof(bool)));
        for (int i = 0; i < graph_size; i++)
        {
            visited[i] = false;
        }
        printf("|");
        for (int j = 0; j < maze->width*2; j++)
        {
            fprintf(file, "-");
        }
        fprintf(file, "\n");
        for (int i = 0; i < maze->height; i++)
        {
            fprintf(file, "|");
            for (int j = 0; j < maze->width; j++)
            {
                int node = calcNodeFromCoordinates(maze, j, i);
                if (node == maze->entrance)
                {
                    fprintf(file, "O");
                }
                else if (node == maze->exit)
                {
                    fprintf(file, "X");
                }
                else
                {
                    fprintf(file, " ");
                }

                if (j < maze->width - 1)
                {
                    int right_node = calcNodeFromCoordinates(maze, j+1, i);
                    if (maze->graph->data[node][right_node])
                    {
                        fprintf(file, " ");
                    }
                    else
                    {
                        fprintf(file, "|");
                    }
                }
            }
            printf("|\n|");
            if (i < maze->height-1)
            {
                for (int j = 0; j < maze->width; j++)
                {
                    int node = calcNodeFromCoordinates(maze, j, i);
                    int down_node = calcNodeFromCoordinates(maze, j, i+1);
                    if (maze->graph->data[node][down_node])
                    {
                        fprintf(file, "%d", maze->graph->data[node][down_node]);
                    }
                    else
                    {
                        fprintf(file, "-");
                    }
                    if (j < maze->width - 1)
                    {
                        fprintf(file, "-");
                    }
                }
                fprintf(file, "|\n");
            }
        }
        for (int j = 0; j < maze->width*2; j++)
        {
            fprintf(file, "-");
        }
        fprintf(file, "\n");
} 