/* contains R-facing C++ functions */

/* Rcpp header */
#include <Rcpp.h>

/* to write out stuff */
#include <fstream>
#include <string>

/* in case we are lazy with the seed */
#include <cstdlib>
#include <ctime>

#include "Tree.hpp"

//' Simulate Birth-Death Cladogenesis Process on Tree
//' 
//' @examples
//' \dontrun{
//' simulate_bd_poisson(seed = 0L,lambda = 1.5,mu = 0.95,duration = 5,maxN = 1e3L,out = "/Users/slwu89/Desktop/out.nwk")
//' MyTree <- ape::read.tree("/Users/slwu89/Desktop/out.nwk")
//' plot(MyTree)
//' }
//' @export
// [[Rcpp::export]]
void simulate_bd_poisson(unsigned int seed, 
                         const double lambda, const double mu, const double duration, 
                         const unsigned int maxN,
                         const std::string& out){
  
  if(seed == 0){
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    seed = std::rand();
  }
  
  std::unique_ptr<Tree> treeP;
  treeP = std::make_unique<Tree>(lambda,mu,duration,seed);
  
  treeP->simulate(maxN);
  
  treeP->listNodes();
  
  std::ofstream outfile;
  outfile.open(out);
  outfile << treeP->getNewick();
  outfile << ";";
  outfile.close();
  
}