#include <stdio.h>
#include <stdlib.h>
#include "HeatPropagationSimulator.cc"

using namespace std;

int main(int argc, char* argv[]){
	int lastArgumentIndex = argc -1;
	HeatPropagationSimulator* simulator = new HeatPropagationSimulator();
	
	vector<double> initialTemperatures;
	for(int i = 1; i < lastArgumentIndex; i++)
		initialTemperatures.push_back(atof(argv[i]));

	simulator->setInitialTemperatures(initialTemperatures);
	simulator->simulateIterations(atoi(argv[lastArgumentIndex]));
	
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	for(int i = 0; i < finalTemperatures.size(); i++)
		printf("%.3f ", finalTemperatures[i]);

	printf("\n");
	return 0;
}