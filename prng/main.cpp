#include <iostream>
#include "RandomVariable.h"

int main() {
    RandomVariable rv;

    int n = 50000;
    double* sample = (double*)(malloc(sizeof(double)*n));
    double sum = 0.0;

    for(int i=0; i<n; i++){
        sample[i] = rv.exponentialRv(1.0/5.0);
        sum += sample[i];
    }

    std::cout << "mean: " << sum/n << std::endl;


    free(sample);
    return 0;
}