/*
 *  Pseudo random number generator
 *
 *  Sean Wu
 *  November 2018
 */

#include "PRNG.hpp"


/* ################################################################################
 * constructor & destructor
################################################################################ */
 
prng::prng(const uint_least32_t seed) : rng(seed){
   runif = std::uniform_real_distribution<double>(0,1);
   std::cout << "prng born at " << this << std::endl;
};
 
prng::~prng(){
  std::cout << "prng dying at " << this << std::endl;
};


/* ################################################################################
 * continuous random univariate sampling
################################################################################ */

double prng::get_runif(){
 return runif(rng);
};

double prng::get_rexp(const double rate){
 std::exponential_distribution<double>rexp(rate);
 return rexp(rng);
};


/* ################################################################################
 * discrete random univariate sampling
################################################################################ */

int prng::get_rpois(const double lambda){
 std::poisson_distribution<int>rpois(lambda);
 return rpois(rng);
};

int prng::get_rbinom(const int n, const double p){
 if(p >= 1.){
   return n;
 } else {
   std::binomial_distribution<int>rbinom(n,p);
   return rbinom(rng);
 }
};
