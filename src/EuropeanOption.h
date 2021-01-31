#include<vector>

class EuropeanOption{
public:

	//constructor
	EuropeanOption(
		int nInt_,           // number of observations before expiration
		double strike_,      // strike price
		double spot_,        // price of the underyling at the moment of option pricing
		double vol_,         // annualized volatility rate
		double r_,           // annualized risk-free rate
		double expiry_,      // time to maturity (expiration)
		double barrier_      // barrier price
		);

	//destructor
	~EuropeanOption(){};

	//class methods
	void generatePath();
	double getEuropeanUpAndInPutPrice(int nReps);
	double getEuropeanUpAndInPutPriceStdDev(int nReps);
	
	//class members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double vol;
	double r;
	double expiry;
	double barrier;

};
