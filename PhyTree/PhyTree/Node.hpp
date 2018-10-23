//
//  Node.hpp
//  PhyTree
//
//  Created by Sean Wu on 10/23/18.
//  Copyright © 2018 Sean Wu. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class node {
    
public:
                    node();
                    ~node();
    node*           getLft() { return left; }
    node*           getRht() { return right; }
    node*           getAnc() { return ancestor; }
    int             getIndex() { return index; }
    std::string     getName() { return name; }
    double          getBranchLength(){ return branchLength; }
    void            setLft(node* p) { left = p; }
    void            setRht(node* p) { right = p; }
    void            setAnc(node* p) { ancestor = p; }
    void            setIndex(int x) { index = x; }
    void            setName(std::string s) { name = s; }
    void            setBranchLength(double x) { branchLength = x; }
    void            print();
private:
    node*           left;
    node*           right;
    node*           ancestor;
    int             index;
    std::string     name;
    double          branchLength;
};


#endif /* Node_hpp */
