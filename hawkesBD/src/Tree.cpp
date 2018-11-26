/*
 *  Tree class
 *
 *  Sean Wu
 *  November 2018
 */

#include "Tree.hpp"
#include "Node.hpp"
#include "PRNG.hpp"

/* constructor & destructor */
Tree::Tree(double lambda, double mu, double duration, std::unique_ptr<prng> prng_) : 
  root(nullptr),
  prngPtr(std::move(prng_))
{
  std::cout << "tree born at " << this << std::endl;
  
  /* generate a birth-death process with parameter lambda, mu, and duration */
  
  /* initialize the single lineage, adding the descendant to a list of active nodes */
  nodes.push_back(new Node);
  nodes.push_back(new Node);
  nodes[0]->setLft(nodes[1]);
  nodes[1]->setAnc(nodes[0]);
  
  std::set<Node*>     activeNodes;
  activeNodes.insert(nodes[1]);
  root = nodes[0];
  
  /* generate the full tree */
  double t = 0.0;
  while(t < duration){
    
    /* increment t using exponential distribution */
    double rate = activeNodes.size() * (lambda + mu);
    t += prngPtr->get_rexp(rate);
    
    if(t < duration){
      /* choose a node */
      Node* p = nullptr;
      
      /* choose type of event */
      double u = prngPtr->get_runif();
      if(u < lambda / (lambda + mu)){
        /* speciation */
         
      } else {
        /* extinction */
        
      }
      
    }
    
  }
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