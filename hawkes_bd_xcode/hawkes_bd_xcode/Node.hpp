#ifndef Node_hpp
#define Node_hpp

#include <string>

class Node {
public:
                        Node();
    Node*               getLft(){return left;};
    Node*               getRht(){return right;};
    Node*               getAnc(){return ancestor;};
    int                 getIndex(){return index;};
    std::string         getName() { return name; }
    double              getBranchLength() { return branchLength;};
    double              getTime(){ return time; }
    void                setLft(Node* p) { left = p; }
    void                setRht(Node* p) { right = p; }
    void                setAnc(Node* p) { ancestor = p; }
    void                setIndex(int x) { index = x; }
    void                setName(std::string s) { name = s; }
    void                setBranchLength(double x) { branchLength = x; }
    void                setTime(double x) { time = x; }
    void                print();
    
protected:
    Node*               left;
    Node*               right;
    Node*               ancestor;
    int                 index;
    std::string         name;
    double              branchLength;
    double              time;
};


#endif
