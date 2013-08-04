#include <vector>

using namespace std;

class HeatPropagationSimulator {
protected:
	vector<double> initialTemperatures, finalTemperatures;

	double simulateNextTemperature(double leftNeighbour, double previousTemperature, double rightNeighbour){
		double fourierNumber = 0.2;
		double nextTemperature = previousTemperature + fourierNumber * (rightNeighbour - (2 * previousTemperature) + leftNeighbour);
		return nextTemperature;
	}

	vector<double> simulateNextTemperatures(vector<double> temperatures){
		vector<double> nextTemperatures(temperatures);
		for(int i = 1; i < (temperatures.size() - 1); i++)
			nextTemperatures[i] = simulateNextTemperature(temperatures[i - 1], temperatures[i], temperatures[i + 1]);
		return nextTemperatures;
	}

public:
	virtual void setInitialTemperatures(vector<double> temperatures){
		this->initialTemperatures = temperatures;
	}

	vector<double> getFinalTemperatures(){
		return this->finalTemperatures;
	}

	virtual void simulateIterations(int iterations){
		this->finalTemperatures = this->initialTemperatures;
		for(int i = 0; i < iterations; i++)
			finalTemperatures = simulateNextTemperatures(finalTemperatures);
	}
};