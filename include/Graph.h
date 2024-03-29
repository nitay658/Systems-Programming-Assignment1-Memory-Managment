#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"

using namespace std;

class Graph{
public:
    Graph();
    Graph(std::vector<std::vector<int>> matrix);
    Graph(const Graph& other); //copy constructor
    Graph& operator=(const Graph& other); //copy assignment operator
    Graph(Graph&& other);//move constructor
    Graph& operator=(Graph&& other);//move assignment operator
    ~Graph(); //Destructor
    
    void infectNode(int nodeInd);
    vector<int> getNeighbours(int node);
    bool isInfected(int nodeInd);
    void clear();
    void copy(const Graph& other);
    void move(Graph& other);
    vector<vector<int>> getEdges()const;
    void detouchNode(int nodeInd);
    vector<int> getInfectedNodes();

private:
    std::vector<std::vector<int>> edges;
    vector<int> infect;

};

#endif
