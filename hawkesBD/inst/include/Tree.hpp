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
#include <memory>
#include <set>

/* forward declare node & PRNG class */
class Node;
class prng;

/* tree class */
class Tree {
public:
  
              Tree(double lambda, double mu, double duration, std::unique_ptr<prng> prng_);
              ~Tree();
  void        listNodes();
  
  std::vector<Node*>& getTraversalOrder(){ return postOrderSequence; }
  
protected:
  
  /* data */
  Node*               root;
  std::vector<Node*>  nodes;
  std::vector<Node*>  postOrderSequence;
  
  /* PRNG */
  std::unique_ptr<prng> prngPtr;
  
  /* functions */
  void                initializeTraversalOrder();
  void                passDown(Node* p);
  
  
};


#endif