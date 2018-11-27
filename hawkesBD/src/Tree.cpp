/*
 *  Tree class
 *
 *  Sean Wu
 *  November 2018
 */

#include "Tree.hpp"
#include "Node.hpp"
#include "PRNG.hpp"


/* ################################################################################
 * constructor & destructor
################################################################################ */
 
Tree::Tree(double lambda_, double mu_, double duration_, unsigned int seed_) : 
  root(NULL),
  numExtant(0),
  lambda(lambda_),
  mu(mu_),
  duration(duration_),
  prngPtr(std::make_unique<prng>(seed_))
{
  std::cout << "tree born at " << this << std::endl;
  activeNodes.clear();
  nodes.clear();
}

Tree::~Tree(){
  std::cout << "tree dying at " << this << std::endl;
  for(size_t i=0; i<nodes.size(); i++){
    delete nodes[i];
  }
  activeNodes.clear();
}


/* ################################################################################
 * print all nodes
################################################################################ */
 
void Tree::listNodes(){
  for(auto it = nodes.begin(); it != nodes.end(); it++){
    (*it)->print();
  }
}


/* ################################################################################
 * traversal
################################################################################ */
 
void Tree::initializeTraversalOrder(){
  postOrderSequence.clear();
  passDown(root);
};

void Tree::passDown(Node* p){
  if(p != NULL){
    passDown(p->getLft()); 
    passDown(p->getRht()); 
    postOrderSequence.push_back(p); 
  }
}


/* ################################################################################
 * birth-death process simulation
################################################################################ */
 
/* run a simulation */
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
    double rate = activeNodes.size() * (lambda + mu);
    t += prngPtr->get_rexp(rate);
    
    /* if t is still less than duration, go ahead do the speciation or extinction thing
     * on a randomly selected active lineage
     */
    if(t < duration){
      /* choose a ndoe */
      Node* p = chooseNodeFromSet();
      p->setTime(t);
      
      /* choose a type of event */
      double u = prngPtr->get_runif();
      if(u < lambda / (lambda + mu)){
        
        /* speciation */
        Node* newLft = new Node; /* allocate new left and right nodes */
        Node* newRht = new Node;
        nodes.push_back(newLft); /* add the new nodes to them tree */
        nodes.push_back(newRht);
        newLft->setAnc(p); /* set the ancestor of both new nodes to be p */
        newRht->setAnc(p);
        p->setLft(newLft); /* set the left and right values of p to be the new nodes */
        p->setRht(newRht);
        activeNodes.erase(p); /* modify the list of active nodes */
        activeNodes.insert(newLft);
        activeNodes.insert(newRht);
        
      } else {
        
        /* extinction */
        activeNodes.erase(p); /* poor p ... he's dead */
        
      }
      
    }
    
    
    /* killswitch for memory */
    if(nodes.size() > maxN){
      Rcpp::Rcout << "warning: exceeded 'maxN' number of nodes; do not trust output" << std::endl;
      break;
    }
    
  } /* end sim */
  
  /* clean up */
  
  
  /* any nodes that are still alive have their time set to current time */
  numExtant = activeNodes.size();
  for(Node* nde : activeNodes){
    nde->setTime(duration);
  }
  
  initializeTraversalOrder();
  
  /* set the index variable and assign branch lengths from the node times */
  int nodeIdx = 0;
  for(int i=0; i<postOrderSequence.size(); i++){
    Node* p = postOrderSequence[i];
    if(p->getLft() == NULL && p->getRht() == NULL){
      p->setIndex(nodeIdx++);
      p->setName( std::to_string(nodeIdx) ); 
    }
    if(p->getAnc() != NULL){
      p->setBranchLength( p->getTime() - p->getAnc()->getTime() );
    }
  }
  for(int i=0; i<postOrderSequence.size(); i++){
    Node* p = postOrderSequence[i];
    if( !(p->getLft() == NULL && p->getRht() == NULL) ){
      p->setIndex(nodeIdx++); 
    }
  }

}

/* choose a node from set of active nodes */
Node* Tree::chooseNodeFromSet(){
  int whichNode = (int)(activeNodes.size() * prngPtr->get_runif()); 
  int i = 0;
  for(Node* nde : activeNodes){
    if(whichNode == i){
      return nde;
    }
    i++;
  }
  return NULL;
};


/* ################################################################################
 * write tree in Newick format
################################################################################ */

/* return tree in newick format as a string */
std::string Tree::getNewick(){
  std::stringstream ss;
  if(root->getLft() != NULL && root->getRht() != NULL){
    writeTree(root, ss);
  } else {
    writeTree(root->getLft(), ss);
  }
  std::string newick = ss.str();
  return newick;
};

/* write the tree recursively */
void Tree::writeTree(Node* p, std::stringstream& ss){
  
  if(p != NULL){
    if(p->getLft() == NULL){
      ss << p->getName() << ":" << std::fixed << std::setprecision(5) << p->getBranchLength();
    } else {
      ss << "(";
      writeTree(p->getLft(), ss); 
      ss << ",";
      writeTree(p->getRht(), ss); 
      if(p->getAnc() == NULL){
        ss << ")";
      } else {
        ss << "):" << std::fixed << std::setprecision(5) << p->getBranchLength();
      }
    }
  } 
}