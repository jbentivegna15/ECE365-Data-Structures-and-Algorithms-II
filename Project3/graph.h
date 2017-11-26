/*
Joseph Bentivegna
Professor Sable
DSA2 Project 3
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <climits>
#include "heap.h"

class graph {

  public:
    graph();
    //initialize graph hashTable

    bool dijkstra(const std::string &start);
    //apply dijkstra's algorithm on a graph given the starting point

    bool hasNode(const std::string &node);
    //check if we have visited the node

    void insert(const std::string &line);
    //insert the node into the graph

    void exportFile(std::ofstream &out);
    //output the graph

  private:
    //size of the graph
    int capacity;
    class edge;
    class node;

    class edge {
      public:
        int cost;  //edge cost
        node *dest;  //destination node
    };

    class node {
      public:
        std::string name;  //name of vertix
        std::list<edge> adj;  //list full of edges from node

        //for use in the dijkstra process
        bool known;
        int dist;
        std::list<std::string> path;
    };

    //list of nodes
    std::list<node*> nodeList;
    //hashtable of nodes
    hashTable * graphItems;

};

#endif
