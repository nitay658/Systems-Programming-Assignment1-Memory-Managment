#include "Agent.h"
#include "../include/Agent.h"

using namespace std;
Agent::Agent():cycle_num() {} // D-Constructor
Virus::Virus(): nodeInd(),creationCycle() {} //D-Constructor

ContactTracer::ContactTracer() {} //D-Constructor

Virus::Virus(const Virus& other):nodeInd(other.nodeInd),creationCycle(other.creationCycle){}//copy constructor

Virus* Virus::clone() const
{
    Virus* A = new Virus(nodeInd,creationCycle);
    return A;
}
Agent* Agent::clone() const {}
ContactTracer* ContactTracer::clone() const
{
    ContactTracer* A = new ContactTracer();
    return A;
}
//copy assignment operator
Virus& Virus::operator=(const Virus& other){//TODO*******************
    nodeInd=other.nodeInd;
    creationCycle=other.creationCycle;
}
//Constructor
Virus::Virus(int nodeInd,int cycle):nodeInd(nodeInd),creationCycle(cycle) {}
void Virus::clear(){
    std::remove_const<int>(nodeInd);
}
void Virus::act(Session &session)
{
    session.virusAct(nodeInd);
}

void ContactTracer::act(Session &session)
{
    session.contactTracerAct();
}

int Agent::getCycle()const {
    return cycle_num;
}
