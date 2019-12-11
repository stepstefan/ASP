//
// main.cc
//
// Created by Stefan Stepanovic on 12/10/2019

#include "./graph.hpp"

void printhelp()
{
    printf("0 : exit\n");
    printf("1 : initialize graph\n");
    printf("2 : add node\n");
    printf("3 : remove node\n");
    printf("4 : add vertex\n");
    printf("5 : remove vertex\n");
    printf("6 : print graph\n");
    printf("7 : free graph\n");
    printf("100 : print help\n");
    printf("\nEnter yout choice: ");
}

int main()
{
    Graph graph;
    graph.n = 0;

    int sw;

    printhelp();

    scanf("%d", &sw);
    while (sw)
    {
        int n, node, node1, node2;
        switch (sw)
        {
            case (1):
                printf("Insert number of nodes: ");
                scanf("%d", &n);
                initializeGraph(&graph, n);
                break;
            case (2):
                addNode(&graph);
                break;
            case (3):
                printf("Select node: ");
                scanf("%d", &node);
                removeNode(&graph, node);
                break;
            case (4):
                printf("Select nodes: ");
                scanf("%d %d", &node1, &node2);
                addVertex(&graph, node1, node2);
                break;
            case (5):
                printf("Select nodes: ");
                scanf("%d %d", &node1, &node2);
                removeVertex(&graph, node1, node2);
                break;
            case (6):
                printGraph(&graph);
                break;
            case (7):
                freeGraph(&graph);
            default:
                break;
        }
        printf("\nEnter yout choice: ");
        scanf("%d", &sw);
    }
    BFS(&graph, 0, 10);
    freeGraph(&graph);
    return 0;
}