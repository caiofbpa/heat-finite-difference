#include <cmath>
#include <mpi.h>
#include "HeatPropagationSimulator.cc"

class ParallelHeatPropagationSimulator :public HeatPropagationSimulator {
private:
	int limit = 0;

public:
	int getTotalProcesses(){
		int size;
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		return size;
	}

	int getProcessNumber(){
		int rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		return rank;
	}

	bool thisIsTheFirstProcess(){
		return 0 == getProcessNumber();
	}

	bool thereIsMoreThanOneProcess(){
		return 1 < getTotalProcesses();
	}

	void divideTemperatures(vector<double> temperatures){
		limit = ceil(temperatures.size() / getTotalProcesses());
		if(thisIsTheFirstProcess())
			this->initialTemperatures = vector<double>(temperatures.begin(), temperatures.begin() + (limit + 1));
		else
			this->initialTemperatures = vector<double>(temperatures.begin() + (limit - 1), temperatures.end());
	}

	void setInitialTemperatures(vector<double> temperatures){
		if(thereIsMoreThanOneProcess())
			divideTemperatures(temperatures);
		else
			this->initialTemperatures = temperatures;
	}

	void receiveTemperatures(){
		double temperatures[limit];
		MPI_Status status;
		MPI_Recv(&temperatures, limit, MPI_DOUBLE, 1, 111111, MPI_COMM_WORLD, &status);
		
		this->finalTemperatures[limit] = temperatures[0];
		for(int i = 1; i < limit; i++)
			this->finalTemperatures.push_back(temperatures[i]);
	}

	void sendTemperatures(){
		double temperatures[limit];
		for(int i = 1; i < finalTemperatures.size(); i++)
			temperatures[i - 1] = finalTemperatures[i];
		MPI_Send(&temperatures, limit, MPI_DOUBLE, 0, 111111, MPI_COMM_WORLD);
	}

	void updateFinalTemperatures(){
		if(thisIsTheFirstProcess())
			receiveTemperatures();
		else
			sendTemperatures();
	}

	void updateLastTemperatures(){
		MPI_Send(&finalTemperatures[limit - 1], 1, MPI_DOUBLE, 1, 111111, MPI_COMM_WORLD);
		MPI_Status status;
		MPI_Recv(&finalTemperatures[limit], 1, MPI_DOUBLE, 1, 111111, MPI_COMM_WORLD, &status);
	}

	void updateFirstTemperatures(){
		MPI_Status status;
		MPI_Recv(&finalTemperatures[0], 1, MPI_DOUBLE, 0, 111111, MPI_COMM_WORLD, &status);
		MPI_Send(&finalTemperatures[1], 1, MPI_DOUBLE, 0, 111111, MPI_COMM_WORLD);
	}

	void updateGhostCells(){
		if(thisIsTheFirstProcess())
			updateLastTemperatures();
		else
			updateFirstTemperatures();
	}

	void simulateIterations(int iterations){
		this->finalTemperatures = this->initialTemperatures;
		for(int i = 0; i < iterations; i++){
			finalTemperatures = simulateNextTemperatures(finalTemperatures);
			if(thereIsMoreThanOneProcess())
				updateGhostCells();
		}
		if(thereIsMoreThanOneProcess())
			updateFinalTemperatures();
	}
};