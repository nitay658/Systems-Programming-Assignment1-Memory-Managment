#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    Tree& getChild(int nodeInd);
    int getChildsNum();
    virtual Tree* clone()const=0;
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    int getNodeInd() const;
    Tree* getMostLeftChild() const;


protected:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual CycleTree* clone() const;
;

protected:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual MaxRankTree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual RootTree* clone() const;
};

#endif
