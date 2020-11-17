
#include "../include/Tree.h"
#include "../include/Session.h"


using namespace std;

// Tree
Tree::Tree(int rootLabel):node(rootLabel) {}

Tree& Tree::getChild(int nodeInd) {return *children[nodeInd];}

void Tree::addChild(const Tree &child)
{
    Tree* A = child.clone();
    children.push_back(A);
}

int Tree::getChildsNum() {return children.size();}

Tree* Tree::clone() const {}

int Tree::getNodeInd() const {
    return node;
}

Tree *Tree::getMostLeftChild() const {
    if (children.size() >0)
        return children[0];
    return nullptr;
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    Tree* tree;
    Session s = session;
    switch (s.getTreeType()) {
        case MaxRank: {
            tree = new MaxRankTree(rootLabel);
        }
        case Root: {
            tree = new RootTree(rootLabel);
        }
        case Cycle: {
            tree = new CycleTree(rootLabel, session.getCurrCycle());
        }
    }
    s.BFS(*tree);
    return tree;
}


// MAX RANK TREE
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree()
{
    int output=-1;
    int maxNumChild =0;
    for(int i =0; i< children.size(); i++) {
        int currChildChildren = children[i]->getChildsNum();
        if (maxNumChild < currChildChildren){
            maxNumChild = currChildChildren;
            output = children[i]->getNodeInd();
        }
    }
    return output;
}

MaxRankTree* MaxRankTree::clone() const
{
    MaxRankTree* A = new MaxRankTree(node);
    A->children=children;
    return A;
}


// ROOT TREE
RootTree::RootTree(int rootLabel): Tree(rootLabel) {}

RootTree* RootTree::clone() const
{
    RootTree* A = new RootTree(node);
    A->children=children;
    return A;
}

int RootTree::traceTree()
{
    return this->node;
}

// CYCLE TREE
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel),currCycle(currCycle) {}

CycleTree* CycleTree::clone() const
{
    CycleTree* A = new CycleTree(node,currCycle);
    A->children=children;
    return A;
}

int CycleTree::traceTree()
{
    Tree* currChild = this;
    while (currCycle > 0 & currChild->getChildsNum() > 0){
        currChild = currChild->getMostLeftChild();
    }
    return currChild->getNodeInd();
}


