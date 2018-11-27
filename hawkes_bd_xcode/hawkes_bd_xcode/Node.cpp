//
//  Node.cpp
//  hawkes_bd_xcode
//
//  Created by Sean Wu on 11/26/18.
//  Copyright © 2018 Sean Wu. All rights reserved.
//

#include <iostream>
#include "Node.hpp"

Node::Node(){
    left = NULL;
    right = NULL;
    ancestor = NULL;
    index = 0;
    name = "";
    branchLength = 0.0;
    time = 0.0;
};

void Node::print(){
    std::cout << "Node " << index << " (" << this << ")" << std::endl;
}
