#include <stdio.h>
#include <stdlib.h>
#include "ParallelHeatPropagationSimulator.cc"

using namespace std;

void printTemperatures(vector<double> temperatures){
	for(int i = 0; i < temperatures.size(); i++)
		printf("%.3f ", temperatures[i]);
}

vector<double> parseVectorFromArguments(int argc, char* argv[]){
	vector<double> v;
	for(int i = 1; i < (argc - 1); i++)
		v.push_back(atof(argv[i]));
	return v;
}

int parseNumberOfIterationsFromArguments(int argc, char* argv[]){
	return atoi(argv[argc - 1]);
}

int main(int argc, char* argv[]){
	MPIWrapper* mpi = new MPIWrapper();
	mpi->initialise();
	
	ParallelHeatPropagationSimulator* simulator = new ParallelHeatPropagationSimulator();

	
	vector<double> initialTemperatures = parseVectorFromArguments(argc, argv);
	int iterations = parseNumberOfIterationsFromArguments(argc, argv);

	simulator->setInitialTemperatures(initialTemperatures);
	simulator->simulateIterations(iterations);
	
	if(0 == mpi->getProcessNumber()){
		vector<double> finalTemperatures = simulator->getFinalTemperatures();
		printTemperatures(finalTemperatures);
	}

	mpi->finalise();
	return 0;
}