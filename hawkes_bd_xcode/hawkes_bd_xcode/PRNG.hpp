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

inline double prng::get_runif(){
    return runif(rng);
};

inline double prng::get_rexp(const double rate){
    std::exponential_distribution<double>rexp(rate);
    return rexp(rng);
};


/* ################################################################################
 * discrete random univariate sampling
 ################################################################################ */

inline int prng::get_rpois(const double lambda){
    std::poisson_distribution<int>rpois(lambda);
    return rpois(rng);
};

inline int prng::get_rbinom(const int n, const double p){
    if(p >= 1.0){
        return n;
    } else {
        std::binomial_distribution<int>rbinom(n,p);
        return rbinom(rng);
    }
};


#endif


