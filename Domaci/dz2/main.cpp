//
// main.cc
//
// Created by Stefan Stepanovic on 12/11/2019

#include "./maze.hpp"

#define MAX_LEN 100


void printhelp()
{
    printf("0 : exit\n");
    printf("1 : initialize maze\n");
    printf("2 : add passage\n");
    printf("3 : find path\n");
    printf("4 : print maze to std\n");
    printf("5 : print maze to file\n");
    // printf("6 : print graph\n");
    // printf("7 : free graph\n");
    printf("100 : print help\n");
    printf("\nEnter yout choice: ");
}
int main()
{
    Maze maze;
    maze.height = 0;
    maze.width = 0;


    int sw;

    printhelp();

    scanf("%d", &sw);
    while (sw)
    {
        int height, width, x1, x2, y1, y2;
        char* file_name = new char[MAX_LEN];
        FILE* file;
        switch (sw)
        {
            case (1):
                printf("Insert height, width, x(entracne), y(entrance), x(exit), y(exit): ");
                scanf("%d %d %d %d %d %d", &height, &width, &x1, &y1, &x2, &y2);
                initializeMaze(&maze, height, width, x1, y1, x2, y2);
                break;
            case (2):
                printf("Insert x1, y1, x2, y2: ");
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                addPassage(&maze, x1, y1, x2, y2);
                break;
            case (3):
                BFSmaze(&maze, maze.entrance, maze.exit);
                break;
            case (4):
                printMazeStd(&maze);
                break;
            case (5):
                printf("Insert file name (max 100 characters): ");
                scanf("%s", file_name);
                file = fopen(file_name, "w");
                printMazeFile(&maze, file);
                break;
            default:
                break;
        }
        printf("\nEnter yout choice: ");
        scanf("%d", &sw);
    }

    // initializeMaze(&maze, 10, 8, 0, 0, 7, 5);
    // printMazeStd(&maze);
    // FILE* file = fopen("maze.txt", "w");
    // printMazeFile()
    // addPassage(&maze, 0, 0, 1, 0);
    // addPassage(&maze, 1, 0, 2, 0);
    // addPassage(&maze, 2, 0, 3, 0);
    // addPassage(&maze, 3, 0, 3, 1);
    // addPassage(&maze, 3, 1, 3, 2);
    // addPassage(&maze, 3, 2, 4, 2);
    // addPassage(&maze, 4, 2, 4, 1);
    // addPassage(&maze, 4, 1, 5, 1);
    // addPassage(&maze, 5, 1, 5, 2);
    // addPassage(&maze, 5, 2, 5, 3);
    // addPassage(&maze, 5, 3, 5, 4);
    // addPassage(&maze, 5, 4, 6, 4);
    // addPassage(&maze, 6, 4, 7, 4);
    // addPassage(&maze, 7, 4, 7, 5);

    // BFSmaze(&maze, maze.entrance, maze.exit);

    // printMazeStd(&maze);
    return 0;
}