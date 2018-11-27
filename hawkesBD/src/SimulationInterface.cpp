/* contains R-facing C++ functions */

/* Rcpp header */
#include <Rcpp.h>

/* to write out stuff */
#include <fstream>
#include <string>

#include "Tree.hpp"

//' Simulate Birth-Death Cladogenesis Process on Tree
//' 
//' @export
// [[Rcpp::export]]
void simulate_bd_poisson(const unsigned int seed, 
                         const double lambda, const double mu, const double duration, 
                         const unsigned int maxN,
                         const std::string& out){
  
  std::unique_ptr<Tree> treeP;
  treeP = std::make_unique<Tree>(lambda,mu,duration,seed);
  
  treeP->simulate(maxN);
  
  treeP->listNodes();
  
  std::ofstream outfile;
  outfile.open(out);
  outfile << treeP->getNewick();
  outfile.close();
  
}