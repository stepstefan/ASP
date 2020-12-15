//
// dz2.cpp
//
// Created by Stefan Stepanovic on 12/12/2020

#include <iostream>
#include <limits>
#include <vector>
#include <utility>
#include <map>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <set>
#include <stack>
#include <algorithm>

const size_t ERROR_ID = std::numeric_limits<size_t>::infinity();

/**
 * @brief Undirected graph structure 
 * 
 */
typedef struct graph
{
    // keep track of connected nodes
    // 0 not connected
    // 1 connected
    // 2 can be connected
    std::vector<std::vector<int>> connectivity_;

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
    graph->connectivity_ = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
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
        graph->connectivity_.push_back(std::vector<int>(graph->n, 0));

        for (size_t i = 0; i < graph->n + 1; i++)
        {
            graph->data_[i].push_back(std::numeric_limits<double>::infinity());
            graph->connectivity_[i].push_back(0);
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
 * @param type : 0, 1, 2 for connection type
 */
void addEdge(Graph* graph, size_t node1, size_t node2, double weight = 0, int type = 1)
{
    if (graph->n > 0)
    {
        if ((graph->node_index_map_.find(node1) != graph->node_index_map_.end()) &&
            (graph->node_index_map_.find(node2) != graph->node_index_map_.end()))
        {
            size_t idx1 = graph->node_index_map_[node1];
            size_t idx2 = graph->node_index_map_[node2];

            graph->connectivity_[idx1][idx2] = type;
            graph->connectivity_[idx2][idx1] = type;
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

            graph->connectivity_[idx1][idx2] = 0;
            graph->connectivity_[idx2][idx1] = 0;
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

typedef std::pair<double, size_t> EdgeType;  // weight, node: default comparison of std::pair type takes first element into consideration

double Prims(Graph* graph)
{
    srand((unsigned) time(0));
    int randomNumber = (std::rand() % graph->n);
    std::map<size_t, size_t>::iterator it = graph->node_index_map_.begin();
    std::advance(it, randomNumber);

    size_t start_node = 0;

    std::cout << "Node: " << start_node << std::endl;


    std::priority_queue<EdgeType, std::vector<EdgeType>, std::greater<EdgeType>> pqueue;  // min p_queue
    std::map<size_t, bool> added;
    for (const auto& element : graph->node_index_map_)
    {
        added.insert(std::make_pair(element.first, false));
    }

    pqueue.push(std::make_pair(0, start_node));

    double total_cost = 0.0;

    while (!pqueue.empty())
    {
        EdgeType edge = pqueue.top();
        pqueue.pop();

        double weight = edge.first;
        size_t node = edge.second;
        size_t index = graph->node_index_map_[node];

        if (!added[node])
        {
            total_cost += weight;
            added[node] = true;

            std::cout << "Node: " << node << std::endl;


            for (const auto& element : graph->node_index_map_)
            {
                if (graph->connectivity_[index][element.second] == 1)
                {
                    if (!added[element.first])
                    {
                        pqueue.push(std::make_pair(graph->data_[index][element.second], element.first));
                    }
                }
            }
        }
    }
    return total_cost;
}

struct LocalSort
{
    explicit LocalSort(const Graph* graph):
    graph_(graph)
    {}

    bool operator()(
        const std::vector<size_t>& elem1,
        const std::vector<size_t>& elem2)
    {
        int cnt1 = 0;
        int cnt2 = 0;
        for (int i = 0; i < elem1.size() - 1; i++)
        {
            size_t node1 = elem1.at(i);
            size_t node2 = elem1.at(i+1);

            if (graph_->connectivity_.at(node1).at(node2) == 2)
            {
                cnt1++;
            }
        }
        for (int i = 0; i < elem2.size() - 1; i++)
        {
            size_t node1 = elem2.at(i);
            size_t node2 = elem2.at(i+1);

            if (graph_->connectivity_.at(node1).at(node2) == 2)
            {
                cnt1++;
            }
        }

        return (cnt1 > cnt2);
    }

    const Graph* graph_;
};

void MinPaths(Graph* graph, size_t start_node)
{
    std::priority_queue<EdgeType, std::vector<EdgeType>, std::greater<EdgeType>> pqueue;  // min p_queue

    // Set distances to inf
    std::map<size_t, double> distances;
    for (const auto& element : graph->node_index_map_)
    {
        distances.insert(std::make_pair(element.first, std::numeric_limits<double>::infinity()));
    }

    // keeps track of previous nodes for every node
    std::map<size_t, std::vector<std::vector<size_t>>> track;
    for (const auto& element : graph->node_index_map_)
    {
        track.insert(std::make_pair(element.first, std::vector<std::vector<size_t>>()));
    }

    std::vector<std::vector<size_t>> empty_track;
    empty_track.push_back(std::vector<size_t>());
    track.at(start_node) = empty_track;

    std::map<size_t, bool> finished;
    for (const auto& element : graph->node_index_map_)
    {
        finished.insert(std::make_pair(element.first, false));
    }
    finished.at(start_node) = true;

    // Init values for start node
    pqueue.push(std::make_pair(0, start_node));
    distances.at(start_node) = 0;

    while (!pqueue.empty())
    {
        EdgeType edge = pqueue.top();
        pqueue.pop();

        size_t node = edge.second;
        std::cout << "Processing: " << node << std::endl;

        // pqueue can contain copys of elements as it is filled incrementally
        // check if this node is already optimized better and skip this iteration
        // avoid multiple copies of same path
        if (edge.first > distances.at(node))
        {
            std::cout << "\t This node is already optimized better" << std::endl;
        }
        else
        {
            double weight = edge.first;
            size_t index = graph->node_index_map_[node];
            finished.at(node) = true;

            for (const auto& element : graph->node_index_map_)
            {
                if (graph->connectivity_[index][element.second] > 0 && !finished.at(element.first))
                {
                    if (distances[element.first] > distances[node] + graph->data_[index][element.second])
                    {
                        distances[element.first] = distances[node] + graph->data_[index][element.second];
                        track[element.first].clear();
                        track[element.first] = track[node];
                        for (auto& track_element : track[element.first])
                        {
                            track_element.push_back(node);
                        }
                        pqueue.push(std::make_pair(distances[element.first], element.first));
                    }
                    else
                    {
                        if (distances[element.first] == distances[node] + graph->data_[index][element.second])
                        {
                            for (const auto& track_element : track[node])
                            {
                                std::vector<size_t> copy_track = track_element;
                                copy_track.push_back(node);
                                track.at(element.first).push_back(copy_track);
                            }
                        }
                    }
                }
            }
        }
    }

    for (const auto& element : distances)
    {
        std::cout << "Distance " << start_node << " - " << element.first << " = " << element.second << " with paths: \n" << std::flush;

        if (track.at(element.first).size() == 2)
        {
            std::swap(track.at(element.first)[0], track.at(element.first)[1]);
        }

        std::sort(
            track.at(element.first).begin(),
            track.at(element.first).end(),
            LocalSort(graph));

        for (const auto& track_element : track.at(element.first))
        {
            for (const auto& prev_node : track_element)
            {
                std::cout << prev_node << " ";
            }
            std::cout << element.first << std::endl;
        }
        std::cout << std::endl;
    }
}

int main()
{
    Graph graph;

    size_t size;
    printf("\nEnter the number of keypoints: ");

    scanf("%ld", &size);
    initializeGraph(&graph, size);
    printf("\nEnter possible pairs of connected keypoints with possible price for it separated by space");
    printf("\nFor stop signal insert negative price\n");

    size_t node1, node2;
    double price = 0;
    int type = 1;
    while (price >= 0)
    {
        scanf("%ld %ld %lf %d", &node1, &node2, &price, &type);
        if (price >= 0)
        {
            addEdge(&graph, node1, node2, price, type);
        }
    }

    double cost = Prims(&graph);
    std::cout << "Optimal cost is: " << cost << std::endl;

    size_t vNode;
    printf("Enter the V node: ");
    scanf("%ld", &vNode);

    MinPaths(&graph, vNode);


    printGraph(&graph);

    freeGraph(&graph);
    return 0;
}