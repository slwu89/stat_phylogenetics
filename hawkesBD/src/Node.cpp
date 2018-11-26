/*
 *  Node class
 *
 *  Sean Wu
 *  November 2018
 */

#include "Node.hpp"

/* constructor & destructor */
Node::Node() : 
  left(nullptr), right(nullptr), ancestor(nullptr),
  index(0), name(""), branchLength(0.0)
  {
  std::cout << "node born at " << this << std::endl;
}

Node::~Node(){
  std::cout << "node dying at " << this << std::endl;
}

/* print the node */
void Node::print(){
  std::cout << "Node " << index << " (" << this << ")" << std::endl;
  std::cout << "  Lft:    " << left << std::endl;
  std::cout << "  Rht:    " << right << std::endl;
  std::cout << "  Anc:    " << ancestor << std::endl;
  std::cout << "  Name:    \"" << name << "\"" << std::endl;
  std::cout << "  Brlen:    " << branchLength << std::endl;
}