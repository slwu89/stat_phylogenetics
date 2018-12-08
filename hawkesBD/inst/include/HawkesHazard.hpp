/*
 *  Hazard functions for Hawkes Birth-Death Processes
 *  not elegant, brute force method.
 *
 *  Sean Wu
 *  November 2018
 */


#include <iostream>
#include <math.h>

/* need a root-finder and a numerical quadrature routine */
#include <gsl/gsl_roots.h>
#include <gsl/gsl_integration.h>

#ifndef HawkesHazard_hpp
#define HawkesHazard_hpp

// /* parameters for offspring intensity */
// struct gamma_pars {
//   double a;
//   double b;
//   double Z;
// };
// 
// /* intensity function for offspring for one point */
// double gamma_exp(const double t, void* p){
//   struct gamma_pars* pars = (struct gamma_pars*) p;
//   double a = pars->a;
//   double b = pars->b;
//   double Z = pars->Z;
//   return a*b*(t < Z ? 1.0 : 0.0);
// }
// 
// /* cumulative (integrated) intensity */
// double Lambda_exp(const double t, const double a, const double b, const double Z){
//   
//   /* parameters of the parent node */
//   gamma_pars p = {a,b,Z};
//   
//   /* bounds of integration */
//   double a0 = 0;
//   double a1 = std::fmin(t,Z);
//   
//   /* function to be integrated */
//   gsl_function lambda;
//   lambda.function = &gamma_exp;
//   lambda.params = &p;
//   
//   double Lambda, error; /* cumulative intensity */
//   
//   gsl_integration_cquad_workspace* w = gsl_integration_cquad_workspace_alloc(100);
//   gsl_integration_cquad(&lambda, a0, a1, 0, 1e-8, w, &Lambda, NULL, NULL);
//   gsl_integration_cquad_workspace_free(w);
//   
//   return Lambda;
// }
// 
// /* distribution function of time one point reproduces */
// double F_exp(const double t, const double a, const double b, const double Z){
//   return 1.0 - exp(-Lambda_exp(t,a,b,Z));
// }
// 
// /* numerically invert the distribution function F^-1(u) = t to get the time to next offspring */
// double Finv_exp(double u, void* p){
//   
//   struct gamma_pars* pars = (struct gamma_pars*) p;
//   double a = pars->a;
//   double b = pars->b;
//   double Z = pars->Z;
//   
//   double result;
//   
//   return result;
// }


#endif