//
//  Tree.cpp
//  PhyTree
//
//  Created by Sean Wu on 10/23/18.
//  Copyright © 2018 Sean Wu. All rights reserved.
//

#include "Tree.hpp"
#include "Node.hpp"

tree::~tree(){
    std::cout << "tree's destructor being called at: " << this << std::endl;
    
    for(int i=0; i<nodes.size(); i++){
        delete nodes.at(i);
    }
}

tree::tree(){
    std::cout << "tree's constructor being called at: " << this << std::endl;
    
    /* put some nodes in the tree */
    for(int i=0; i<5; i++){
        node* newNode = new node;
        nodes.emplace_back(newNode);
    }
    for(int i=0; i<nodes.size(); i++){
        std::cout << "nodes[" << i << "] = " << nodes[i] << std::endl;
    }
    
    /* set the member pointers */
    node* p = nodes.at(0);
    p->setAnc(nodes.at(3));
    p->setLft(nullptr);
    p->setRht(nullptr);
    p->setIndex(0);
    p->setBranchLength(0.10);
    p->setName("Sp1");
    
    p = nodes.at(1);
    p->setAnc(nodes.at(3));
    p->setLft(nullptr);
    p->setRht(nullptr);
    p->setIndex(1);
    p->setBranchLength(0.10);
    p->setName("Sp2");
    
    p = nodes.at(2);
    p->setAnc(nodes.at(4));
    p->setLft(nullptr);
    p->setRht(nullptr);
    p->setIndex(2);
    p->setBranchLength(0.30);
    p->setName("Sp3");
    
    p = nodes.at(3);
    p->setAnc(nodes.at(4));
    p->setLft(nodes.at(0));
    p->setRht(nodes.at(1));
    p->setIndex(3);
    p->setBranchLength(0.20);
    p->setName("");
    
    p = nodes.at(4);
    p->setAnc(nullptr);
    p->setLft(nodes.at(3));
    p->setRht(nodes.at(2));
    p->setIndex(4);
    p->setBranchLength(0.0);
    p->setName("");
    
    root = nodes.at(4);
}

void tree::print(){
    for(int i=0; i<nodes.size(); i++){
        nodes.at(i)->print();
    }
}
