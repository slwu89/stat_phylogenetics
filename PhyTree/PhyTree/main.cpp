//
//  main.cpp
//  PhyTree
//
//  Created by Sean Wu on 10/23/18.
//  Copyright © 2018 Sean Wu. All rights reserved.
//

#include <iostream>

#include "Tree.hpp"

int main(int argc, const char * argv[]) {
    
    tree* treep = new tree;
    treep->print();
    delete treep;
    
    return 0;
}
