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
  
              Tree(double lambda_, double mu_, double duration_, unsigned int seed_);
              ~Tree();
  void        listNodes();
  
  std::vector<Node*>& getTraversalOrder(){ return postOrderSequence; }
  
  /* bd process */
  void                simulate(const unsigned int maxN);
  Node*               chooseNodeFromSet();
  
protected:
  
  /* data */
  Node*               root;
  std::vector<Node*>  nodes;
  std::vector<Node*>  postOrderSequence;
  std::set<Node*>     activeNodes;
  size_t              numExtant;
  
  /* parameters */
  double              lambda;
  double              mu;
  double              duration;
  
  /* PRNG */
  std::unique_ptr<prng> prngPtr;
  
  /* functions */
  void                initializeTraversalOrder();
  void                passDown(Node* p);
  
  
};


#endif