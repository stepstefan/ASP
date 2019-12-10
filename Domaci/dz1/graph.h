//
// graph.h
//
// Created by Stefan Stepanovic on 12/10/2019

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph
{
    bool** data;
    int n;
} Graph;

// initializes graph with n nodes
void initializeGraph(Graph* graph, int n);

// adds vertex to graph between node1 and node2
void addVertex(Graph* graph, int node1, int node2);

// remove vertex from graph between node1 and node2
void removeVertex(Graph* graph, int node1, int node2);

// add node to graph
void addNode(Graph* graph);

// remove node from graph
void removeNode(Graph* graph, int node);

// print graph
void printGraph(Graph* graph);

// free graph
void freeGraph(Graph* graph);
