//
// graph.cc
//
// Created by Stefan Stepanovic on 12/10/2019

#include "./graph.hpp"

void freeGraph(Graph* graph)
{
    if (graph->n > 0)
    {
        for (int i =0; i < graph->n; i++)
        {
            bool* vec = graph->data[i];
            free(vec);
        }
    }
    graph->n = 0;
}

void initializeGraph(Graph* graph, int n)
{
    freeGraph(graph);
    graph->data = reinterpret_cast<bool**>(calloc(n, sizeof(bool*)));
    for (int i = 0; i < n; i++)
    {
        graph->data[i] = reinterpret_cast<bool*>(calloc(n, sizeof(bool)));
    }

    // Check that all is 0 (compiler)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        graph->data[i][j] = false;
    }

    graph->n = n;
}

void addNode(Graph* graph)
{
    if (graph->n > 0)
    {
        bool** new_data = reinterpret_cast<bool**>(realloc(graph->data, (graph->n + 1) * sizeof(bool*)));
        if (new_data)
        {
            for (int i = 0; i < graph->n; i++)
            {
                bool* new_row = reinterpret_cast<bool*>(realloc(new_data[i], (graph->n+1)*sizeof(bool)));
                // new_row[graph->n] = false;
                if (new_row)
                {
                    new_data[i] = new_row;
                }
                else
                {
                    printf("Realloc failed rows\n");
                }
            }
            new_data[graph->n] = reinterpret_cast<bool*>(calloc(graph->n + 1, sizeof(bool)));
            // Check on false (compiler)
            for (int i = 0; i < graph->n+1; i++)
            {
                new_data[graph->n][i] = false;
            }
            graph->data = new_data;
            graph->n++;
            printf("Added node at the end of adjacency matrix\n");
        }
        else
        {
            printf("Realloc failed cols\n");
        }
    }
    else
    {
        printf("Graph is not initialized!\n");
    }
}

void addVertex(Graph* graph, int node1, int node2)
{
    if (graph->n > 0)
    {
        if ((node1 < graph->n) && (node2 < graph->n) &&
            (node1 >= 0) && (node2 > 0))
        {
            graph->data[node1][node2] = true;
            graph->data[node2][node1] = true;
            printf("Added vertex between %d and %d\n", node1, node2);
        }
        else
        {
            printf("Provided nodes are aout of bouds %d %d\n", node1, node2);
        }
    }
    else
    {
        printf("Graph is not initialized!\n");
    }
}

void removeVertex(Graph* graph, int node1, int node2)
{
    if (graph->n > 0)
    {
        if ((node1 < graph->n) && (node2 < graph->n) &&
            (node1 >= 0) && (node2 > 0))
        {
            graph->data[node1][node2] = false;
            graph->data[node2][node1] = false;
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
        if ((node < graph->n) && (node >= 0))
        {
            // remove node in every row
            for (int i = 0; i < graph->n-1; i++)
            {
                for (int j = node; j < graph->n-1; j++)
                {
                    graph->data[i][j] = graph->data[i][j+1];
                }
                bool* new_row = reinterpret_cast<bool*>(realloc(graph->data[i], (graph->n-1) * sizeof(bool)));
                if (new_row)
                {
                    graph->data[i] = new_row;
                }
                else
                {
                    printf("Realloc failed rows\n");
                }
            }
            // remove node in every column
            for (int i = node; i < graph->n-1; i++)
            {
                graph->data[i] = graph->data[i+1];
            }
            bool** new_data = reinterpret_cast<bool**>(realloc(graph->data, (graph->n-1)*sizeof(bool*)));
            if (new_data)
            {
                graph->data = new_data;
                graph->n--;
            }
            else
            {
                printf("Realloc failed cols\n");
            }
        }
        else
        {
            printf("Provided node are aout of bouds %d", node);
        }
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
            printf("%d ", graph->data[i][j]);
        }
        printf("\n");
    }
}

// template<typename T>
Queue::Queue(int max_elem)
{
    data = new int[max_elem];
    top = 0;
    bot = 0;
}

// template<typename T>
void Queue::push(int elem)
{
    data[top++] = elem;
}

// template<typename T>
int Queue::pop()
{
    return data[bot++];
}

// template<typename T>
bool Queue::empty()
{
    return (bot == top);
}

void BFS(Graph* graph, int node_start, int node_end)
{
    // queue
    Queue queue(graph->n+1);

    int* parents = new int[graph->n];

    // look-up searched
    bool* searched = reinterpret_cast<bool*>(calloc(graph->n, sizeof(bool)));
    for (int i = 0; i < graph->n; i++)
    {
        searched[i] = false;
    }

    // Add start to search
    queue.push(node_start);
    searched[node_start] = true;
    while (!queue.empty())
    {
        int node = queue.pop();
        if (node == node_end)
        {
            break;
        }
        printf("%d ", node);
        for (int j = 0; j < graph->n; j++)
        {
            if ((graph->data[node][j]) && !(searched[j]))
            {
                searched[j] = true;
                parents[j] = node;
                queue.push(j);
            }
        }
    }
}