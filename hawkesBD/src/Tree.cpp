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
Tree::Tree(double lambda_, double mu_, double duration_, std::unique_ptr<prng> prng_) : 
  root(nullptr),
  lambda(lambda_),
  mu(mu_),
  duration(duration_),
  prngPtr(std::move(prng_))
{
  std::cout << "tree born at " << this << std::endl;
}

Tree::~Tree(){
  std::cout << "tree dying at " << this << std::endl;
  for(size_t i=0; i<nodes.size(); i++){
    delete nodes[i];
  }
  activeNodes.clear();
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

/* birth-death process simulation */
void Tree::simulate(){
  
  /* generate a birth-death process with parameter lambda, mu, and duration */
  
  /* initialize the single lineage, adding the descendant to a list of active nodes */
  nodes.push_back(new Node);
  nodes.push_back(new Node);
  nodes[0]->setLft(nodes[1]);
  nodes[1]->setAnc(nodes[0]);
  
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
      Node* p = chooseNodeFromSet();
      
      /* choose type of event */
      double u = prngPtr->get_runif();
      
      if(u < lambda / (lambda + mu)){
        /* speciation */
        Node* newLft = new Node; /* 1. allocate new left and right nodes */
        Node* newRht = new Node;
        nodes.emplace_back(newLft); /* 2. add the new nodes to the tree */
        nodes.emplace_back(newRht);
        newLft->setAnc(p); /* 3. set the ancestor of both new nodes to be p */
        newRht->setAnc(p);
        p->setLft(newLft); /* 4. set the left and right values of p to be the new nodes */
        p->setRht(newRht);
        activeNodes.erase(p); /* 5. modify the list of active nodes */
        activeNodes.insert(newLft);
        activeNodes.insert(newRht);
      } else {
        /* extinction */
        activeNodes.erase(p); /* poor p ... he's dead */
      }
      
    }
    
  }
}

Node* Tree::chooseNodeFromSet(){
  unsigned int whichNode = (int)(activeNodes.size() * prngPtr->get_runif());
  unsigned int i = 0;
  for(Node* node : activeNodes){
    if(whichNode == i){
      return node;
    }
    i++;
  }
  return nullptr;
};