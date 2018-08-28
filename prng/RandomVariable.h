//
// Created by Sean Wu on 8/27/18.
//

#ifndef PRNG_RANDOMVARIABLE_H
#define PRNG_RANDOMVARIABLE_H

/* random variable class */
class RandomVariable {
public:
    /* constructor */
    RandomVariable(void);
    RandomVariable(int x);

    /* methods */
    double uniformRv(void);
    double uniformRv(double lower, double upper);
    double exponentialRv(double lambda);


protected:
    int    seed;
};

#endif //PRNG_RANDOMVARIABLE_H
