#ifndef AGENT_H_
#define AGENT_H_
#include "Session.h"
#include <vector>

class Virus;
class ContactTracer;

class Agent{
public:
    Agent();
    Agent(const Agent& other); //copy constructor
    Agent& operator=(const Agent& other); //copy assignment operator
    virtual void act(Session& session)=0;
    //virtual void clone()=0;
    virtual Agent* clone()const=0;
    virtual void clear()=0;

protected:
    int cycle_num;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    ContactTracer(const ContactTracer& other); //copy constructor
    ContactTracer& operator=(const ContactTracer& other); //copy assignment operator

    virtual void act(Session& session);
    virtual void clear();
    virtual ContactTracer* clone() const;
};


class Virus: public Agent{
public:
    Virus();
    Virus(int nodeInd,int cycle);

    Virus(const Virus& other); //copy constructor
    Virus& operator=(const Virus& other); //copy assignment operator

    virtual void act(Session& session);
    virtual void clear();
    virtual Virus* clone() const;

private:
    const int nodeInd;
    int creationCycle;
};

#endif
