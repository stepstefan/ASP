//
// dz1.cpp
//
// Created by Stefan Stepanovic on 12/12/2020

#include <iostream>
#include <limits>
#include <vector>
#include <utility>
#include <map>

const size_t ERROR_ID = std::numeric_limits<size_t>::infinity();

/**
 * @brief Undirected graph structure 
 * 
 */
typedef struct graph
{
    // keep track of connected nodes
    std::vector<std::vector<bool>> connectivity_;

    // keep track of weights of edges
    // data on specific edge is valid only if connectivity of those nodes is true
    std::vector<std::vector<double>> data_;

    std::map<size_t, size_t> node_index_map_;

    // number of nodes
    size_t n = 0;

    size_t max_index = 0;
} Graph;


/**
 * @brief Free memory occupied by graph
 * 
 * @param graph 
 */
void freeGraph(Graph* graph)
{
    if (graph->n > 0)
    {
        for (size_t i = 0; i < graph->n; i++)
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
        graph->node_index_map_.clear();
    }
    graph->n = 0;
}

/**
 * @brief Initialize graph with n unconnected nodes
 * 
 * @param graph 
 * @param n 
 */
void initializeGraph(Graph* graph, size_t n)
{
    freeGraph(graph);
    graph->connectivity_ = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
    graph->data_ = std::vector<std::vector<double>>(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));
    for (size_t i = 0; i < n; i++)
    {
        graph->node_index_map_.insert(std::make_pair(i, i));
    }
    graph->n = n;
    graph->max_index = n-1;
}

/**
 * @brief Add node to graph and assign it next successive id
 * 
 * @param graph 
 */
size_t addNode(Graph* graph)
{
    if (graph->n > 0)
    {
        size_t new_id = ++graph->max_index;  // find current max id and increment it

        graph->data_.push_back(std::vector<double>(graph->n, std::numeric_limits<double>::infinity()));
        graph->connectivity_.push_back(std::vector<bool>(graph->n, false));

        for (size_t i = 0; i < graph->n + 1; i++)
        {
            graph->data_[i].push_back(std::numeric_limits<double>::infinity());
            graph->connectivity_[i].push_back(false);
        }

        graph->node_index_map_.insert(std::make_pair(new_id, graph->n));  // assign mapping from id to index
        graph->n++;
        return new_id;
    }
    else
    {
        printf("Graph is not initialized!\n");
        return ERROR_ID;
    }
}

/**
 * @brief Add edge between nodes with specified weight
 * 
 * @param graph 
 * @param node1 
 * @param node2 
 * @param weight 
 */
void addEdge(Graph* graph, size_t node1, size_t node2, double weight = 0)
{
    if (graph->n > 0)
    {
        if ((graph->node_index_map_.find(node1) != graph->node_index_map_.end()) &&
            (graph->node_index_map_.find(node2) != graph->node_index_map_.end()))
        {
            size_t idx1 = graph->node_index_map_[node1];
            size_t idx2 = graph->node_index_map_[node2];

            graph->connectivity_[idx1][idx2] = true;
            graph->connectivity_[idx2][idx1] = true;
            graph->data_[idx1][idx2] = weight;
            graph->data_[idx2][idx1] = weight;
            printf("Added edge between %ld and %ld\n", node1, node2);
        }
        else
        {
            printf("Provided nodes do not exist: %ld %ld\n", node1, node2);
        }
    }
    else
    {
        printf("Graph is not initialized!\n");
    }
}

/**
 * @brief Remove edge between nodes
 * 
 * @param graph 
 * @param node1 
 * @param node2 
 */
void removeEdge(Graph* graph, size_t node1, size_t node2)
{
    if (graph->n > 0)
    {
        if ((graph->node_index_map_.find(node1) != graph->node_index_map_.end()) &&
            (graph->node_index_map_.find(node2) != graph->node_index_map_.end()))
        {
            size_t idx1 = graph->node_index_map_[node1];
            size_t idx2 = graph->node_index_map_[node2];

            graph->connectivity_[idx1][idx2] = false;
            graph->connectivity_[idx2][idx1] = false;
            graph->data_[idx1][idx2] = std::numeric_limits<double>::infinity();
            graph->data_[idx2][idx1] = std::numeric_limits<double>::infinity();
        }
        else
        {
            printf("Provided nodes do not exist: %ld %ld", node1, node2);
        }
    }
    else
    {
        printf("Graph is not initialized!\n");
    }
}

/**
 * @brief Remove specific node from graph
 * 
 * @param graph 
 * @param node 
 */
void removeNode(Graph* graph, size_t node)
{
    if (graph->node_index_map_.find(node) != graph->node_index_map_.end())
    {
        size_t idx = graph->node_index_map_[node];
        graph->connectivity_.erase(graph->connectivity_.begin() + idx);
        graph->data_.erase(graph->data_.begin() + idx);

        for (size_t i = 0; i < graph->n - 1; i++)
        {
            graph->connectivity_.at(i).erase(graph->connectivity_.at(i).begin() + idx);
            graph->data_.at(i).erase(graph->data_.at(i).begin() + idx);
        }
        for (auto& element : graph->node_index_map_)
        {
            if (element.second > idx)
            {
                element.second--;
            }
        }
        graph->node_index_map_.erase(node);
        graph->n--;
    }
    else
    {
        printf("Node does not exist!\n");
    }
}

/**
 * @brief Print graph to std::out
 * 
 * @param graph 
 */
void printGraph(Graph* graph)
{
    printf("Number of nodes %ld\n", graph->n);
    std::cout << "   ";
    for (const auto& element : graph->node_index_map_)
    {
        std::cout << element.first << "\t";
    }

    std::cout << std::endl;
    std::cout << "   ";
    for (const auto& element : graph->node_index_map_)
    {
        std::cout << "_\t";
    }

    std::cout << std::endl;

    for (const auto& element1 : graph->node_index_map_)
    {
        std::cout << element1.first << "| ";
        for (const auto& element2 : graph->node_index_map_)
        {
            size_t idx1 = element1.second;
            size_t idx2 = element2.second;

            std::cout << graph->data_.at(idx1).at(idx2) << "\t";
        }
        std::cout << std::endl;
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
    printf("\nEnter your choice: ");

    scanf("%d", &sw);
    while (sw)
    {
        size_t n, node, node1, node2;
        switch (sw)
        {
            case (1):
                printf("Insert number of nodes: ");
                scanf("%ld", &n);
                initializeGraph(&graph, n);
                break;
            case (2):
                addNode(&graph);
                break;
            case (3):
                printf("Select node: ");
                scanf("%ld", &node);
                removeNode(&graph, node);
                break;
            case (4):
                printf("Select nodes: ");
                scanf("%ld %ld", &node1, &node2);
                addEdge(&graph, node1, node2);
                break;
            case (5):
                printf("Select nodes: ");
                scanf("%ld %ld", &node1, &node2);
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
        printf("\nEnter your choice: ");
        scanf("%d", &sw);
    }

    freeGraph(&graph);
    return 0;
}