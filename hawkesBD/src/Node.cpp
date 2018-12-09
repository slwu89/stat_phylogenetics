/*
 *  Node class
 *
 *  Sean Wu
 *  November 2018
 */

#include "Node.hpp"

/* constructor & destructor */
// Node::Node() : 
//   left(nullptr), right(nullptr), ancestor(nullptr),
//   index(0), name(""), branchLength(0.0)
//   {
//   // std::cout << "node born at " << this << std::endl;
// }

Node::Node(){
  left = NULL;
  right = NULL;
  ancestor = NULL;
  index = 0;
  name = "";
  branchLength = 0.0;
  time = 0.0;
};

Node::~Node(){};

void Node::print(){
  std::cout << "Node " << index << " (" << this << ")" << std::endl;
  std::cout << "  Lft:  " << left << std::endl;
  std::cout << "  Rht:  " << right << std::endl;
  std::cout << "  Anc:  " << ancestor << std::endl;
  std::cout << "  Name: \"" << name << "\"" << std::endl;
  std::cout << "  BrLen:  " << branchLength << std::endl;
  std::cout << "  Time: " << time << std::endl;
}
