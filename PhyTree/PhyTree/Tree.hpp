//
//  Tree.hpp
//  PhyTree
//
//  Created by Sean Wu on 10/23/18.
//  Copyright © 2018 Sean Wu. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

/* forward declare node class */
class node;

/* tree class */
class tree {
public:
    
    tree();
    ~tree();
    void print();
    
private:
    node*               root;
    std::vector<node*>  nodes;
    
};

#endif /* Tree_hpp */
