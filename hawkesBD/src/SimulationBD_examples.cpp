#include <Rcpp.h>

#include <algorithm>
#include <vector>

/* for a halfway decent prng */
#include <random>

/* in case we are lazy with the seed */
#include <cstdlib>
#include <ctime>

//' Simulate Homogeneous Markov (Poisson) Birth-Death Process
//' 
//' @param lambda birth intensity is proportional to lambda
//' @param mu death intensity is proportional to mu
//' @param tmax maximum simulation time
//' @param seed a seed (if set to 0, will draw a "random" seed from the system time)
//' @param maxN if population exceeds this number kill the simulation (useful for preventing runaway processes)
//' 
//' @examples
//' \dontrun{
//' out <- poisson_bd(lambda = 1.1,mu = 1.1,tmax = 30,seed = 42L)
//' plot(stepfun(x = out$t,y = c(0,out$X)),xlim=c(0,ceiling(max(out$t))))
//' }
//' @export
// [[Rcpp::export]]
Rcpp::List poisson_bd(const double lambda, const double mu, const double tmax, unsigned int seed, const unsigned int maxN = 1e4){
  
  /* prng */
  if(seed == 0){
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    seed = std::rand();
  }
  std::mt19937  rng(seed);
  std::uniform_real_distribution<double> runif = std::uniform_real_distribution<double>(0,1);
  
  /* output */
  std::vector<unsigned int> X; /* state space */
  std::vector<double> t; /* point process */
  X.reserve(1e3);
  t.reserve(1e3);
  
  /* simulation */
  double tnow = 0.0;
  unsigned int x = 1;
  
  X.emplace_back(x);
  t.emplace_back(tnow);
  
  while(tnow <= tmax){
    
    /* increment t using exponential distribution */
    double rate = x * (lambda + mu);
    std::exponential_distribution<double> rexp(rate);
    tnow += rexp(rng);
    
    /* choose a type of event */
    double u = runif(rng);
    if(u < lambda / (lambda + mu)){
      
      /* birth */
      x += 1;
      
    } else {
      
      /* death */
      x -= 1;
      
    }
    
    X.emplace_back(x);
    t.emplace_back(tnow);
    
    /* if we hit 0, its absorbing, so break loop now */
    if(x==0 || x >= maxN){
      break;
    }
  }
  /* end simulation loop */
  
  /* return to R */
  return Rcpp::List::create(
    Rcpp::_["X"] = X,
    Rcpp::_["t"] = t
  );
}



//' Simulate Homogeneous non-Markov (Hawkes) Birth-Death Process
//' 
//' The slow version here simulates as a marked Hawkes process, by sampling the immigration process as well as 
//' the marked descendent process.
//' 
//' @param baseline immigration rate (constant; corresponds to homogeneous Poisson immigrant arrivals)
//' @param alpha mean number of offspring for each particle
//' @param beta rate parameter of exponentially distributed particle lifespan
//' @param tmax maximum simulation time
//' @param seed a seed (if set to 0, will draw a "random" seed from the system time)
//' @param maxN if population exceeds this number kill the simulation (useful for preventing runaway processes)
//' 
//' @examples
//' \dontrun{
//' 
//' plot(stepfun(x = out$t,y = c(0,out$X)),xlim=c(0,ceiling(max(out$t))))
//' }
//' @export
// [[Rcpp::export]]
Rcpp::List hawkes_exp_bd_slow(const double mu, const double alpha, const double beta, const double tmax, unsigned int seed, const unsigned int maxN = 1e4){
  
  /* prng */
  if(seed == 0){
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    seed = std::rand();
  }
  std::mt19937  rng(seed);
  std::uniform_real_distribution<double> runif(0,1);
  std::exponential_distribution<double> rexp(beta);
  std::poisson_distribution<unsigned int> rpois(mu*tmax);
  
  /* sample immigrants (the quick way, because its a homogeneous Poisson process) */
  unsigned int n_imm = rpois(rng) + 1;
  std::vector<double> imm_t(n_imm); /* times */
  std::vector<double> imm_m(n_imm); /* marks */
  imm_t[0] = 0.0; /* always somebody at time 1 */
  imm_m[0] = rexp(rng);
  
  /* sample the rest of the immigrant's times */
  std::generate(imm_t.begin(),imm_t.end(),[&](){
    double t = runif(rng);
    t = t*tmax;
    return t;
  });
  std::sort(imm_t.begin(),imm_t.end());
  
  /* sample the rest of the immigrant's marks */
  std::generate(imm_m.begin(),imm_m.end(),[&](){
    return rexp(rng);
  });
  
  unsigned int x = n_imm;
  
  /* sample clusters as NHPP */
  for(size_t i=0; i<imm_t.size(); i++){
    
    /* put at relatively low level of this simulation procedure */
    if(n_imm >= maxN){
      break;
    }
    
  }
  
  return Rcpp::List::create(
    Rcpp::_["immigrants"] = imm_t
  );
}
