//
//  Node.cpp
//  PhyTree
//
//  Created by Sean Wu on 10/23/18.
//  Copyright © 2018 Sean Wu. All rights reserved.
//

#include "Node.hpp"

node::node() :
    left(nullptr),
    right(nullptr),
    ancestor(nullptr),
    index(0),
    name(""),
    branchLength(0.0)
{
    std::cout << "node's constructor being called at: index " << index << " address " << this << std::endl;
};

node::~node(){
    std::cout << "node's destructor being called at: index " << index << " address " << this << std::endl;
}

void node::print(){
    std::cout << "Node " << index << " (" << this << ")" << std::endl;
    std::cout << "  Lft:    " << left << std::endl;
    std::cout << "  Rht:    " << right << std::endl;
    std::cout << "  Anc:    " << ancestor << std::endl;
    std::cout << "  Name:    \"" << name << "\"" << std::endl;
    std::cout << "  Brlen:    " << branchLength << std::endl;
}
