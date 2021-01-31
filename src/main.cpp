#include<Rcpp.h>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"EuropeanOption.h"
#include"getVecStdDev.h"

using namespace Rcpp;
using std::vector;

// [[Rcpp::export]]
double getEuropeanUpAndInPutPrice(
    int nInt,
    double strike,
    double spot,
    double vol,
    double r,
    double expiry,
    double barrier,
    int nReps = 10000){
  
  // set the seed
  srand( time(NULL) );
  
  //create a new instance of class EuropeanOption
  EuropeanOption myEuropean(nInt, strike, spot, vol, r, expiry, barrier);
  
  // call the method to get option price
  double price = myEuropean.getEuropeanUpAndInPutPrice(nReps);
  
  // return option price  
  return price;
}
