#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <iostream>
#include "ParallelHeatPropagationSimulator.cc"

using namespace std;

void printTemperatures(vector<double> temperatures){
	printf("%.3f", temperatures[0]);
	for(int i = 1; i < temperatures.size(); i++)
		printf(" %.3f", temperatures[i]);
}

int main(int argc, char* argv[]){

	int iterations = 1;
	int ghostRegionSize = 1;
	vector<double> initialTemperatures;

	while(optind < argc) {
		int c;
		while((c = getopt(argc, argv, "hi::g::")) != -1) {
			switch(c) {
				case 'h':
				case '?': {
					cout << "usage: main.bin <initial temperatures separated by space> -i <iterations> -g <ghost region size>" << endl;
					return EXIT_SUCCESS;
				} break;
				case 'i': {
					iterations = atoi(optarg);
				} break;
				case 'g': {
					ghostRegionSize = atoi(optarg);
				} break;
				default: {
					cout << "Unknown option '" << c << "'." << endl;
				} break;
			};
		};

		if(optind < argc) {
			char *aux;
			const char *arg = argv[optind++];
			double d = strtod(arg, &aux);
			if(*aux) {
				cout << "Given value (" << arg << ") is not a double." << endl;
			} else initialTemperatures.push_back(d);
		};
	};

	MPIWrapper* mpi = new MPIWrapper();
	mpi->initialise();
	
	ParallelHeatPropagationSimulator* simulator = new ParallelHeatPropagationSimulator();

	simulator->setInitialTemperatures(initialTemperatures);
	simulator->simulateIterations(iterations);
	
	if(0 == mpi->getProcessNumber()){
		vector<double> finalTemperatures = simulator->getFinalTemperatures();
		printTemperatures(finalTemperatures);
	}

	mpi->finalise();
	return 0;
}