/*
 *  Pseudo random number generator
 *
 *  Sean Wu
 *  November 2018
 */

#ifndef PRNG_hpp
#define PRNG_hpp

/* C++ includes */
#include <random>
#include <iostream>
#include <math.h>

/* Rcpp header */
#include <Rcpp.h>

/* PRNG class */
class prng {
public:
  
  /* constructor & destructor */
  prng(const uint_least32_t seed);
  ~prng();
  
  /* delete copy constructor/assignment operator, default move constructor/assignment operator */
  prng(const prng&) = delete;
  prng& operator=(const prng&) = delete;
  prng(prng&&) = default;
  prng& operator=(prng&&) = default;
  
  /* continuous random univariate sampling */
  double                                 get_runif();
  double                                 get_rexp(const double rate);

  
  /* discrete random univariate sampling */
  int                                    get_rpois(const double lambda);
  int                                    get_rbinom(const int n, const double p);
  
private:
  std::mt19937                            rng;
  std::uniform_real_distribution<double>  runif;
};

#endif
