//
// graph.cc
//
// Created by Stefan Stepanovic on 12/12/2020

#include <iostream>
#include <limits>
#include <vector>
#include <priority_queue>

typedef struct graph
{
    std::vector<std::vector<bool>> connectivity_;
    std::vector<std::vector<double>> data_;
    int n = 0;
} Graph;


void freeGraph(Graph* graph)
{
    if (graph->n > 0)
    {
        for (int i = 0; i < graph->n; i++)
        {
            graph->data_[i].clear();
            graph->data_[i].shrink_to_fit();
            graph->connectivity_[i].clear();
            graph->connectivity_[i].shrink_to_fit();
        }
        graph->data_.clear();
        graph->data_.shrink_to_fit();
        graph->connectivity_.clear();
        graph->connectivity_.shrink_to_fit();
    }
    graph->n = 0;
}

void initializeGraph(Graph* graph, int n)
{
    freeGraph(graph);
    graph->connectivity_ = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
    graph->data_ = std::vector<std::vector<double>>(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));
    graph->n = n;
}

void addNode(Graph* graph)
{
    if (graph->n > 0)
    {
        graph->data_.push_back(std::vector<double>(graph->n, std::numeric_limits<double>::infinity()));
        graph->connectivity_.push_back(std::vector<bool>(graph->n, false));

        for (size_t i = 0; i < graph->n + 1; i++)
        {
            graph->data_[i].push_back(std::numeric_limits<double>::infinity());
            graph->connectivity_[i].push_back(false);
        }
        graph->n++;
    }
    else
    {
        printf("Graph is not initialized!\n");
    }
}

void addEdge(Graph* graph, int node1, int node2, double weight = 0)
{
    if (graph->n > 0)
    {
        if ((node1 < graph->n) && (node2 < graph->n) &&
            (node1 >= 0) && (node2 > 0))
        {
            graph->connectivity_[node1][node2] = true;
            graph->connectivity_[node2][node1] = true;
            graph->data_[node1][node2] = weight;
            graph->data_[node2][node1] = weight;
            printf("Added edge between %d and %d\n", node1, node2);
        }
        else
        {
            printf("Provided nodes are out of bouds %d %d\n", node1, node2);
        }
    }
    else
    {
        printf("Graph is not initialized!\n");
    }
}

void removeEdge(Graph* graph, int node1, int node2)
{
    if (graph->n > 0)
    {
        if ((node1 < graph->n) && (node2 < graph->n) &&
            (node1 >= 0) && (node2 > 0))
        {
            graph->connectivity_[node1][node2] = false;
            graph->connectivity_[node2][node1] = false;
            graph->data_[node1][node2] = std::numeric_limits<double>::infinity();
            graph->data_[node2][node1] = std::numeric_limits<double>::infinity();
        }
        else
        {
            printf("Provided nodes are aout of bouds %d %d", node1, node2);
        }
    }
    else
    {
        printf("Graph is not initialized!\n");
    }
}

void removeNode(Graph* graph, int node)
{
    if (graph->n > 1)
    {
        graph->connectivity_.erase(graph->connectivity_.begin() + node);
        graph->data_.erase(graph->data_.begin() + node);

        for (size_t i = 0; i < graph->n - 1; i++)
        {
            graph->connectivity_.at(i).erase(graph->connectivity_.at(i).begin() + node);
            graph->data_.at(i).erase(graph->data_.at(i).begin() + node);
        }

        graph->n--;
    }
    else
    {
        printf("Graph must have more than one node!\n");
    }
}

void printGraph(Graph* graph)
{
    printf("Number of nodes %d\n", graph->n);
    for (int i = 0; i < graph->n; i++)
    {
        for (int j = 0; j < graph->n; j++)
        {
            std::cout << graph->connectivity_.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < graph->n; i++)
    {
        for (int j = 0; j < graph->n; j++)
        {
            std::cout << graph->data_.at(i).at(j) << " ";
        }
        std::cout << std::endl;;
    }
}


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
}

int main()
{
    Graph graph;
    graph.n = 0;

    int sw;

    printhelp();
    printf("\nEnter yout choice: ");

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
                printhelp();
                break;
        }
        printf("\nEnter yout choice: ");
        scanf("%d", &sw);
    }

    freeGraph(&graph);
    return 0;
}