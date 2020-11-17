#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
#include "../src/json.hpp"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    Session(const Session& other); //copy constructor
    Session& operator=(const Session& other); //copy assignment operator
    Session(Session&& other);//move constructor
    Session& operator=(Session&& other);//move assignment operator
    ~Session(); //Destructor


    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void copy(const Session& other);
    void clear();
    void move(Session& other);
    void contactTracerAct();
    void virusAct(int nodeInd);
    
    void enqueueInfected(int node);
    int dequeueInfected();
    TreeType getTreeType() const;
    void BFS(Tree& tree);
    int getCurrCycle() const;



private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int currCycle;
    std::queue<int> infectedQueue;

    void to_json(nlohmann::basic_json<> &j);
};

#endif
