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
    printf("4 : add edge\n");
    printf("5 : remove edge\n");
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
                addEdge(&graph, node1, node2);
                break;
            case (5):
                printf("Select nodes: ");
                scanf("%d %d", &node1, &node2);
                removeEdge(&graph, node1, node2);
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

    // initializeGraph(&graph, 5);
    // addEdge(&graph, 0, 2);
    // addEdge(&graph, 2, 1);
    // addEdge(&graph, 1, 3);
    // addEdge(&graph, 3, 4);
    // addEdge(&graph, 2, 3);

    // BFS(&graph, 2, 3);
    freeGraph(&graph);
    return 0;
}