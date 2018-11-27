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
Tree::Tree(double lambda_, double mu_, double duration_, unsigned int seed_) : 
  root(nullptr),
  numExtant(0),
  lambda(lambda_),
  mu(mu_),
  duration(duration_),
  prngPtr(std::make_unique<prng>(seed_))
{
  std::cout << "tree born at " << this << std::endl;
  activeNodes.clear();
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
    postOrderSequence.push_back(p);
  }
}

/* birth-death process simulation */
void Tree::simulate(const unsigned int maxN){
  
  /* generate a birth-death process with parameter lambda, mu, and duration */
  
  /* initialize the single lineage, adding the descendant to a list of active nodes */
  nodes.push_back( new Node );
  nodes.push_back( new Node ); 
  nodes[0]->setLft(nodes[1]); 
  nodes[1]->setAnc(nodes[0]);
  
  activeNodes.insert(nodes[1]);
  root = nodes[0];
  
  /* generate the full tree */
  double t = 0.0;
  while(t < duration){
    
    /* increment t using exponential distribution */
    unsigned int nnodes = activeNodes.size();
    double rate =  nnodes * (lambda + mu);
    t += prngPtr->get_rexp(rate);
    
    if(t < duration){
      
      /* choose a node */
      Node* p = chooseNodeFromSet();
      p->setTime(t);
      
      /* choose type of event */
      double u = prngPtr->get_runif();
      
      if(u < lambda / (lambda + mu)){
        // /* speciation */
        // Node* newLft = new Node; /* 1. allocate new left and right nodes */
        // Node* newRht = new Node;
        // nodes.emplace_back(newLft); /* 2. add the new nodes to the tree */
        // nodes.emplace_back(newRht);
        // newLft->setAnc(p); /* 3. set the ancestor of both new nodes to be p */
        // newRht->setAnc(p);
        // p->setLft(newLft); /* 4. set the left and right values of p to be the new nodes */
        // p->setRht(newRht);
        // activeNodes.erase(p); /* 5. modify the list of active nodes */
        // activeNodes.insert(newLft);
        // activeNodes.insert(newRht);
        
        
        // speciation event
        Node* newLft = new Node;  /* 1. allocate new left and right nodes */
        Node* newRht = new Node; 
        nodes.push_back(newLft); /* 2. add the new nodes to the tree */
        nodes.push_back(newRht); 
        newLft->setAnc(p); /* 3. set the ancestor of both new nodes to be p */
        newRht->setAnc(p); 
        p->setLft(newLft); /* 4. set the left and right values of p to be the new nodes */
        p->setRht(newRht); 
        activeNodes.erase(p);  /* 5. modify the list of active nodes */
        activeNodes.insert(newLft); 
        activeNodes.insert(newRht);
        
      } else {
        /* extinction */
        activeNodes.erase(p); /* poor p ... he's dead */
      }
      
    }
    
    /* if we get an absurd number of nodes, break out of loop */
    if(nnodes >= maxN){
      break;
    }
    
  } /* end sim */
  
  /* clean up */
  numExtant = activeNodes.size();
  for(Node* node : activeNodes){
    node->setTime(duration);
  }
  initializeTraversalOrder();
  
  /* set the index variable and assign branch lengths from the node times */
  // unsigned int nodeIdx = 0;
  // for(size_t i=0; i<postOrderSequence.size(); i++){
  //   Node* p = postOrderSequence[i];
  //   if(p->getLft() == nullptr && p->getRht() == nullptr){
  //     p->setIndex(nodeIdx++);
  //     p->setName(std::to_string(nodeIdx));
  //   }
  //   if(p->getAnc() != nullptr){
  //     p->setBranchLength(p->getTime() - p->getAnc()->getTime());
  //   }
  // }
  // 
  // for(size_t i=0; i<postOrderSequence.size(); i++){
  //   Node* p = postOrderSequence[i];
  //   if(!( p->getLft() == nullptr && p->getRht() == nullptr )){
  //     p->setIndex(nodeIdx);
  //   }
  // }
  
  // set the index variable and assign branch lengths from the node times
  int nodeIdx = 0;
  for (int i=0; i<postOrderSequence.size(); i++)
  {
    Node* p = postOrderSequence[i];
    if (p->getLft() == NULL && p->getRht() == NULL)
    {
      p->setIndex(nodeIdx++);
      p->setName( std::to_string(nodeIdx) ); }
    if (p->getAnc() != NULL)
      p->setBranchLength( p->getTime() - p->getAnc()->getTime() );
  }
  for (int i=0; i<postOrderSequence.size(); i++)
  {
    Node* p = postOrderSequence[i];
    if ( !(p->getLft() == NULL && p->getRht() == NULL) )
      p->setIndex(nodeIdx++); }
  
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

/* Newick format */
std::string Tree::getNewick(){
  std::stringstream ss;
  if(root->getLft() != nullptr && root->getRht() != nullptr){
    writeTree(root, ss);
  } else {
    writeTree(root->getLft(), ss); 
  }
  std::string newick = ss.str(); 
  return newick;
};

void Tree::writeTree(Node* p, std::stringstream& ss){
  
  if(p != nullptr){
    if(p->getLft() == nullptr){
      ss << p->getName() << ":" << std::fixed << std::setprecision(5) << p->getBranchLength();
    } else {
      ss << "(";
      writeTree(p->getLft(), ss); 
      ss << ",";
      writeTree(p->getRht(), ss); 
      if(p->getAnc() == nullptr){
        ss << ")";
      } else {
        ss << "):" << std::fixed << std::setprecision(5) << p->getBranchLength();
      }
    }
  } 
}