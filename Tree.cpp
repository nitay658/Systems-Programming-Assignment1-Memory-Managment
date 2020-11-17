#include "Tree.h"

using namespace std;

Tree::Tree(int rootLabel):node(rootLabel) {}

MaxRankTree::MaxRankTree(int rootLabel1, int rootLabel) : Tree(rootLabel1) {}

RootTree::RootTree(int rootLabel): Tree(rootLabel) {}

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel),currCycle(currCycle) {}

Tree& Tree::getChild(int nodeInd) {return *children[nodeInd];}
void Tree::addChild(const Tree &child)
{
    Tree* A = child.clone();
    children.push_back(A);
}
MaxRankTree* MaxRankTree::clone() const
{
    MaxRankTree* A = new MaxRankTree(0, node);
    A->children=children;
    return A;
}
Tree* Tree::clone() const {}
RootTree* RootTree::clone() const
{
    RootTree* A = new RootTree(node);
    A->children=children;
    return A;
}
CycleTree* CycleTree::clone() const
{
    CycleTree* A = new CycleTree(node,currCycle);
    A->children=children;
    return A;
}
