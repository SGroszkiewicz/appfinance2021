#include<iostream>
#include<cmath>
#include<algorithm>   // *max_element()
#include"getOneGaussianByBoxMueller.h"
#include"EuropeanOption.h"
#include"getVecStdDev.h"


//definition of constructor
EuropeanOption::EuropeanOption(
	int nInt_,
	double strike_,
	double spot_,
	double vol_,
	double r_,
	double expiry_,
	double barrier_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		barrier = barrier_;
		generatePath();
}


// generatePath method definition
void EuropeanOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();

	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
		thisPath.push_back(spot * exp(cumShocks));
	}
}


// getEuropeanUpAndInPutPrice method definition - calculate the price of the European up-and-in put option
double EuropeanOption::getEuropeanUpAndInPutPrice(int nReps){

	double rollingSum = 0.0;
	double lastPrice = 0.0;

	for(int i = 0; i < nReps; i++){
		generatePath();
		lastPrice = thisPath[nInt-1];                                                               // check the last price of the underlying
		double thisMax = *max_element(thisPath.begin(), thisPath.end());                            // find the maximum price of the underlying
		rollingSum += ( (strike > lastPrice) && (thisMax >= barrier ) ) ? (strike-lastPrice) : 0;   // construction of up-and-in put option
	}

	return exp(-r*expiry)*rollingSum/double(nReps);

}

// getEuropeanUpAndInPutPriceStdDev method definition - calculate the standard deviation of the European up-and-in put option
double EuropeanOption::getEuropeanUpAndInPutPriceStdDev(int nReps){

	double rollingSum = 0.0;
	double lastPrice = 0.0;
	std::vector<double> myVec2;

	for(int i = 0; i < nReps; i++){
		generatePath();
		lastPrice = thisPath[nInt-1];                                                               // check the last price of the underlying
		double thisMax = *max_element(thisPath.begin(), thisPath.end());                            // find the maximum price of the underlying
		rollingSum = ( (strike > lastPrice) && (thisMax >= barrier ) ) ? (strike-lastPrice) : 0;    // construction of up-and-in put option
		myVec2.push_back( exp(-r*expiry) * rollingSum );                                              // place into the vector
	}

	return getVecStdDev(myVec2);

}

