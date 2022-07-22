#ifndef GRAPH_H
#define GRAPH_H

#include"node.h"
#include"vector"
#include"Level.h"
class Graph
{
public:
    Graph();
    static void drawGraph(std::vector<Node> path);
};

#endif // GRAPH_H
