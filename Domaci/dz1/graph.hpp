//
// graph.h
//
// Created by Stefan Stepanovic on 12/10/2019

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// template<typename T>
class Queue
{
 public:
    explicit Queue(int max_elem);
    void push(int elem);
    int pop();
    bool empty();

 private:
    int top;
    int bot;
    int* data;
};

typedef struct graph
{
    bool** data;
    int n;
} Graph;

// initializes graph with n nodes
void initializeGraph(Graph* graph, int n);

// adds edge to graph between node1 and node2
void addEdge(Graph* graph, int node1, int node2);

// remove edge from graph between node1 and node2
void removeEdge(Graph* graph, int node1, int node2);

// add node to graph
void addNode(Graph* graph);

// remove node from graph
void removeNode(Graph* graph, int node);

// print graph
void printGraph(Graph* graph);

// free graph
void freeGraph(Graph* graph);

// BFS
void BFS(Graph* graph, int node_start, int node_end);
