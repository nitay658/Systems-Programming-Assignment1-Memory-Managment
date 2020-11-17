#include "Graph.h"
using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix):edges(),infect()
{
        edges=std::move(matrix);
        for(int i=0;i<matrix.size();i++)
        {
            infect.push_back(0);
        }
}
Graph::Graph(): edges(),infect(){} // D-Constructor
// COPY CONSTRUCTOR
Graph::Graph(const Graph& other): edges(),infect() {
    this->copy(other);
}

//copy assignment operator
Graph& Graph::operator=(const Graph &other) {
    if (this != &other)//checking self-assignment
    {
        clear(); //delete the old resources
        this->copy(other);//copy the new resources
    }
    return *this;
}

void Graph::copy(const Graph& other)
{
    edges=other.edges;
    for(int i=0; i< edges.size(); i++ )
    {
        infect.push_back(other.infect[i]);
    }
}

void Graph::clear()
{
    for(int i=0;i<edges.size();i++) {
        edges[i].clear();
    }
    edges.clear();
}

//move constructor
Graph::Graph(Graph&& other): edges(),infect()
{
    move(other);
}

//move assignment operator
Graph& Graph::operator=(Graph&& other) {
    if (this != &other) {
        this->clear();
        move(other);
    }
    return *this;
}

//Destructor
Graph::~Graph(){
    clear();
}

void Graph::move(Graph &other)
{
    edges=std::move(other.edges);
}

void Graph::infectNode(int nodeInd)
{
    infect[nodeInd]=1;
}

bool Graph::isInfected(int nodeInd)
{
    return (infect[nodeInd]==1);
}

vector<int> Graph::getNeighbours(int node)
{
    vector<int> output;
    for(int i=0;i<edges[node].size();i++)
    {
        if(edges[node][i]==1)
            output.push_back(i);
    }
    return output;
}

void Graph::detouchNode(int nodeInd) {
    for(int i=0;i<edges.size();i++) {
        edges[nodeInd][i]=0;
        edges[i][nodeInd]=0;
    }
}

