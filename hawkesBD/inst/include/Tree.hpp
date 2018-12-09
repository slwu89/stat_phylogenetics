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
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <set>

#include <Rcpp.h>

/* forward declare node & PRNG class */
class Node;
class prng;

/* tree class */
class Tree {
public:
  
              // Tree(double lambda_, double mu_, double duration_, unsigned int seed_);
              Tree(double duration_, unsigned int seed_);
              // ~Tree();
  virtual     ~Tree();
  void        listNodes();
  
  std::vector<Node*>& getTraversalOrder(){ return postOrderSequence; }
  
  /* bd process */
  // void                simulate(const unsigned int maxN);
  virtual void                simulate(const unsigned int maxN) = 0;
  
  void                process_simulate(); /* call after a simulation has run */
  
  /* Newick format */
  std::string         getNewick();
  
  /* accessors */
  size_t              getNumExtant(){ return numExtant; }
  void                setNumExtant(size_t x){ numExtant = x; }
  
protected:
  
  /* data */
  Node*               root;
  std::vector<Node*>  nodes;
  std::vector<Node*>  postOrderSequence;
  std::set<Node*>     activeNodes;
  size_t              numExtant;
  
  // /* parameters */
  // double              lambda;
  // double              mu;
  double              duration;
  
  /* PRNG */
  std::unique_ptr<prng> prngPtr;
  
  /* functions */
  void                initializeTraversalOrder();
  void                passDown(Node* p);
  Node*               chooseNodeFromSet();
  
  /* Newick format */
  void                writeTree(Node* p, std::stringstream& ss);
  
};

/* tree class for Poisson BD */
class Tree_PoissonBD : public Tree {
public:
  
  Tree_PoissonBD(double lambda_, double mu_, double duration_, unsigned int seed_);
  ~Tree_PoissonBD();
  
  virtual void                simulate(const unsigned int maxN);
  
private:
  
  /* parameters */
  double              lambda;
  double              mu;
  double              duration;
  
};


#endif