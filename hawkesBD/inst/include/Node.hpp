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
  virtual ~Node();
  Node*               getLft(){return left;};
  Node*               getRht(){return right;};
  Node*               getAnc(){return ancestor;};
  int                 getIndex(){return index;};
  std::string         getName() { return name; }
  double              getBranchLength() { return branchLength;};
  double              getTime(){ return time; }
  void                setLft(Node* p) { left = p; }
  void                setRht(Node* p) { right = p; }
  void                setAnc(Node* p) { ancestor = p; }
  void                setIndex(int x) { index = x; }
  void                setName(std::string s) { name = s; }
  void                setBranchLength(double x) { branchLength = x; }
  void                setTime(double x) { time = x; }
  void                print();
  
protected:
  Node*               left;
  Node*               right;
  Node*               ancestor;
  int                 index;
  std::string         name;
  double              branchLength;
  double              time;
};


// /* marked Node for Hawkes BD process */
// class Node_hawkes : public Node {
// public:
//   Node_hawkes()
//   
// private:
//   
// };



#endif