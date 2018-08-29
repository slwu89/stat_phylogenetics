#include <iostream>
#include <iomanip>
#include <cmath>

#include "RandomVariable.h"

int main() {

    /* prng */
    RandomVariable rv;

    /* a great user-interface! */
    int numTosses = 100;
    int numHeads = 43;
    int numTails = numTosses - numHeads;
    int chainLength = 1000000;
    int printFrequency = 10;
    int sampleFrequency = 1;
    double window = 0.125;

    /* initialize theta */
    double theta = rv.uniformRv();

    /* record trace of chain */
    int bins[100];
    for(int i=0; i<100; i++){
        bins[i] = 0;
    }
    int numSamples = 0;

    /* run MCMC */
    for(int n=1; n<=chainLength; n++){

        /* propose a new value for theta */
        double thetaPrime = theta + (rv.uniformRv() - 0.5) * window;
        if(thetaPrime < 0.){
            thetaPrime = - thetaPrime;
        } else if(thetaPrime > 1.){
            thetaPrime = 2.0 - thetaPrime;
        }

        // print (part 1)
        if (n % printFrequency == 0) {
            std::cout << std::setw(5) << n << " -- ";
            std::cout << std::fixed << std::setprecision(3) << theta << " -> ";
            std::cout << std::fixed << std::setprecision(3) << thetaPrime << " ";
        }

        /* calculate the probability of accepting thetaPrime
         * as the next state of the chain */
        double logLikeRatio = (numHeads*log(thetaPrime) + numTails*log(1.0 - thetaPrime)) -
                (numHeads*log(theta) + numTails*log(1.0 - theta));
        double logPriorRatio = 0.0; /* log(1) */
        double logHastingsRatio = 0.0; /* log(1) */

        double logR = logLikeRatio + logPriorRatio + logHastingsRatio;

        double R = 0.0;
        /* safe exponentiation */
        if(logR < -300.0){
            R = 0.0;
        } else if(logR > 0.0){
            R = 1.0;
        } else {
            R = exp(logR);
        }

        /* accept or reject thetaPrime */
        double u = rv.uniformRv();
        bool isAccepted = false;
        if(u < R){
            theta = thetaPrime;
            isAccepted = true;
        }

        // print (part 2)
        if (n % printFrequency == 0) {
            if (isAccepted)
                std::cout << "(Accepted)";
            else
                std::cout << "(Rejected)";
            std::cout << std::endl;
        }

        /* sample the chain's current state */
        if(n % sampleFrequency == 0){
            numSamples += 1;
            bins[(int)(theta*100.0)]++;
        }
    }

    std::cout << "MCMC run complete!" << std::endl;
    std::cout << std::endl;

    /* print table */
    // summarize the results
    double cumulativeProbability = 0.0;
    for (int i=0; i<100; i++){
        double intervalProbability = (double)bins[i] / numSamples;
        cumulativeProbability += intervalProbability;
        std::cout << std::fixed << std::setprecision(2) << i * 0.01 << " - ";
        std::cout << std::fixed << std::setprecision(2) << (i+1) * 0.01 << " -- ";
        std::cout << std::setw(5) << bins[i] << " ";
        std::cout << std::fixed << std::setprecision(3) << intervalProbability << " ";
        std::cout << std::fixed << std::setprecision(3) << cumulativeProbability << " ";
        std::cout << std::endl;
    }

    return 0;
}