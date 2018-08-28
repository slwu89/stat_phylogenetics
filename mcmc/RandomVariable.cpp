//
// Created by Sean Wu on 8/27/18.
//

#include <ctime>
#include <cmath>
#include <iostream>

#include "RandomVariable.h"

/* constructor */
RandomVariable::RandomVariable(){
    seed = static_cast<int>(time(nullptr));
    std::cout << "Default constructor. The seed equals " << seed << std::endl;
};

RandomVariable::RandomVariable(int x){
    seed = x;
    std::cout << "Alternate constructor. The seed equals " << seed << std::endl;
}


/* methods */
double RandomVariable::uniformRv() {
    int hi = seed / 127773;
    int lo = seed % 127773;
    int test = 16807 * lo - 2836 * hi;
    if (test > 0){
        seed = test;
    } else {
        seed = test + 2147483647;
    }
    return static_cast<double>(seed) / static_cast<double>(2147483647);
}

double RandomVariable::uniformRv(double lower, double upper) {
    return (lower + uniformRv() * (upper - lower));
};

double RandomVariable::exponentialRv(double lambda) {
    return -log(uniformRv())/lambda;
};