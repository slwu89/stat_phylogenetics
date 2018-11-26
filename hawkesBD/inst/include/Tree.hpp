/*
 *  Tree class
 *
 *  Sean Wu
 *  November 2018
 */

#ifndef Tree_hpp
#define Tree_hpp

/* C++ includes */
#include <iostream>
#include <vector>

/* forward declare node class */
class Node;

/* tree class */
class Tree {
public:
  
              Tree();
              ~Tree();
  void        listNodes();
  
  std::vector<Node*>& getTraversalOrder(){ return postOrderSequence; }
  
private:
  
  /* data */
  Node*               root;
  std::vector<Node*>  nodes;
  std::vector<Node*>  postOrderSequence;
  
  /* functions */
  void                initializeTraversalOrder();
  void                passDown(Node* p);
  
  
};


#endif