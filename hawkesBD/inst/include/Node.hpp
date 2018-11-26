/*
 *  Node class
 *
 *  Sean Wu
 *  November 2018
 */

#ifndef Node_hpp
#define Node_hpp

/* C++ includes */
#include <iostream>
#include <string>

/* Rcpp header */
#include <Rcpp.h>

/* Node class */
class Node {
public:
  
                  Node();
                  ~Node();
  Node*           getLft(){ return left; };
  Node*           getRht(){ return right; };
  Node*           getAnc(){ return ancestor; }
  unsigned int    getIndex(){ return index; }
  std::string     getName(){ return name; };
  double          getBranchLength(){ return branchLength; };
  void            setLft(Node* p){ left = p; };
  void            setRht(Node* p){ right = p; };
  void            setAnc(Node* p){ ancestor = p; };
  void            setIndex(unsigned int x){ index = x; };
  void            setName(const std::string& s){ name = s; };
  void            setBranchLength(double x){ branchLength = x; };
  void            print();
  
  
private:
  
  Node*           left;
  Node*           right;
  Node*           ancestor;
  unsigned int    index;
  std::string     name;
  double          branchLength;
  
};

#endif