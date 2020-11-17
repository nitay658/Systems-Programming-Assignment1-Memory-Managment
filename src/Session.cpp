#include "../include/Session.h"
#include "fstream"
#include "json.hpp"
#include "../include/Agent.h"
#include "../include/Tree.h"




using json = nlohmann::json;
using namespace std;

void Session::simulate(){
    bool gameOn = true;
    while (gameOn){
        gameOn = false;
        for (int i =0; i< agents.size(); i++){
            if (agents[i]->getCycle() < currCycle){
                agents[i]->act(*this);

            }
            else
                gameOn = true;
        }
        currCycle++;
    }
    json j;
    to_json(j);

}

void Session::to_json(json& j)
{
    j["graph"] = g.getEdges();
    j["infected"] = g.getInfectedNodes();

}

Session::Session(const std::string& path):g(),treeType(),agents()
{
    ifstream i(path);
    json j;
    j << i;
    g = Graph(j["graph"]);
    for(int i=0;i<j["agents"].size();i++)
    {
        if(j["agents"][i][0]=="V"){
            Virus A;
            int num = j["agents"][i][1];
            A = Virus(num,-1);
            addAgent(A);
        }
        else {
            ContactTracer A;
            A = ContactTracer();
            addAgent(A);
        }
    }
    treeType=j["tree"][0];
}

void Session::addAgent(const Agent &agent)
{
    Agent* A = agent.clone();
    agents.push_back(A);
}

void Session::setGraph(const Graph& graph)
{
    g=graph;

}
void Session::enqueueInfected(int node)
{
    infectedQueue.push(node);
}

int Session::dequeueInfected()
{
    if(!infectedQueue.empty()) {
        int output=infectedQueue.front();
        infectedQueue.pop();
        return output;
    }
    return -1;
}

void Session::virusAct(int nodeInd)
{
    if(!g.isInfected(nodeInd))
    {
        g.infectNode(nodeInd);
        enqueueInfected(nodeInd);
    }
    vector<int> v = g.getNeighbours(nodeInd);
    for(int i=0;i<v.size();i++)
    {
        if(!g.isInfected(i))
        {
            Virus newVirus = Virus(i,currCycle);
            addAgent(newVirus);
            break;
        }
    }
}


Session::Session(const Session& other):g(),treeType(),agents() //copy constructor
{
    this->copy(other);
}

void Session::contactTracerAct()
{
    int node;
    int nodeToDetouch;
    if (!infectedQueue.empty()){
        node = dequeueInfected();
        Tree* treeFromInfected;
        treeFromInfected = treeFromInfected->createTree(*this, node);
        nodeToDetouch = treeFromInfected->traceTree();
        g.detouchNode(nodeToDetouch);
    }
}

Session& Session::operator=(const Session& other) //copy assignment operator
{
    if(this==& other) {
        return *this;
    }
    clear();
    this->copy(other);
    return *this;
}


Session::Session(Session&& other): g(),treeType(),agents()//move constructor
{
    move(other);
}

Session& Session::operator=(Session&& other)//move assignment operator
{
    if (this != &other)//checking self-assignment
    {
        clear(); //delete the old resources
        this->copy(other);//copy the new resources
    }
    return *this;
}

void Session::copy(const Session &other)
{
    for(int i=0;i<other.agents.size();i++)
    {
        Agent *newAgent = other.agents[i];
        agents.push_back(newAgent);
    }
    g=other.g;
    treeType=other.treeType;
}

void Session::clear()
{
    for(int i=0;i<agents.size();i++) {
        agents[i]->clear();
    }
    agents.clear();
}

void Session::move(Session &other)
{
    agents=std::move(other.agents);
    g=other.g;
    other.g.clear(); //???
    treeType=other.treeType;
    //other.treeType??;
    for(auto &run : other.agents)
    {
        agents.push_back(run);
        run= nullptr;
    }
}

void Session::BFS(Tree& tree) {
    vector<int> children = g.getNeighbours(tree.getNodeInd());
    for (int i =0; i< children.size(); i++){
        Tree* childTree = tree.createTree(*this, children[i]);
        tree.addChild(*childTree);
    }
}


TreeType Session::getTreeType() const {
    return treeType;
}

int Session::getCurrCycle() const {
    return currCycle;
}
