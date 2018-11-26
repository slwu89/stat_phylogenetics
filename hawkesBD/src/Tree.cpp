/*
 *  Tree class
 *
 *  Sean Wu
 *  November 2018
 */

#include "Tree.hpp"
#include "Node.hpp"

/* constructor & destructor */
Tree::Tree() : 
  root(nullptr)
{
  std::cout << "tree born at " << this << std::endl;
  
  initializeTraversalOrder();
}

Tree::~Tree(){
  std::cout << "tree dying at " << this << std::endl;
  for(size_t i=0; i<nodes.size(); i++){
    delete nodes[i];
  }
}

/* print all nodes */
void Tree::listNodes(){
  for(auto it = nodes.begin(); it != nodes.end(); it++){
    (*it)->print();
  }
}

/* traversal */
void Tree::initializeTraversalOrder(){
  postOrderSequence.clear();
  passDown(root);
};

void Tree::passDown(Node* p){
  if(p != nullptr){
    passDown(p->getLft());
    passDown(p->getRht());
    postOrderSequence.emplace_back(p);
  }
}