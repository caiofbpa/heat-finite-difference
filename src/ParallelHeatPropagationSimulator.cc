#include <cmath>
#include <mpi.h>
#include "HeatPropagationSimulator.cc"

#define GHOST_REGION_TAG 111110
#define FINAL_TEMPERATURES_TAG 111111

class ParallelHeatPropagationSimulator :public HeatPropagationSimulator {
private:
	int limit = 0;
	int ghostRegionSize = 1;

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

	int getNextProcessNumber(){
		return getProcessNumber() + 1;
	}

	int getPreviousProcessNumber(){
		return getProcessNumber() - 1;
	}

	bool thisIsTheFirstProcess(){
		return 0 == getProcessNumber();
	}

	bool thisIsTheLastProcess(){
		return getProcessNumber() == (getTotalProcesses() - 1);
	}

	bool thereIsMoreThanOneProcess(){
		return 1 < getTotalProcesses();
	}

	void divideTemperatures(vector<double> temperatures){
		limit = ceil(temperatures.size() / getTotalProcesses());
		if(thisIsTheFirstProcess())
			this->initialTemperatures = vector<double>(temperatures.begin(), temperatures.begin() + (limit + ghostRegionSize));
		else if(thisIsTheLastProcess())
			this->initialTemperatures = vector<double>(temperatures.end() - (limit + ghostRegionSize), temperatures.end());
		else
			this->initialTemperatures = vector<double>(temperatures.begin() + (limit * getProcessNumber() - ghostRegionSize), temperatures.begin() + (limit * getProcessNumber() + limit + ghostRegionSize));
	}

	void setInitialTemperatures(vector<double> temperatures){
		if(thereIsMoreThanOneProcess())
			divideTemperatures(temperatures);
		else
			this->initialTemperatures = temperatures;
	}

	void receiveTemperaturesFromProcess(int processNumber){
		double temperatures[limit];
		MPI_Status status;
		MPI_Recv(&temperatures, limit, MPI_DOUBLE, processNumber, FINAL_TEMPERATURES_TAG, MPI_COMM_WORLD, &status);
		for(int i = 0; i < limit; i++)
			this->finalTemperatures.push_back(temperatures[i]);
	}

	void receiveTemperaturesFromAllOtherProcesses(){
		for(int i = 0; i < ghostRegionSize; i++)
			this->finalTemperatures.pop_back();
		for(int i = getNextProcessNumber(); i < getTotalProcesses(); i++)
			receiveTemperaturesFromProcess(i);
	}

	void sendTemperaturesToFirstProcess(){
		double temperatures[limit];
		for(int i = ghostRegionSize; i < limit + ghostRegionSize; i++)
			temperatures[i - ghostRegionSize] = finalTemperatures[i];
		MPI_Send(&temperatures, limit, MPI_DOUBLE, 0, FINAL_TEMPERATURES_TAG, MPI_COMM_WORLD);
	}

	void updateFinalTemperatures(){
		if(thisIsTheFirstProcess())
			receiveTemperaturesFromAllOtherProcesses();
		else
			sendTemperaturesToFirstProcess();
	}

	void updateRightGhostRegion(){
		MPI_Send(&finalTemperatures[(finalTemperatures.size() - 1) - ghostRegionSize], ghostRegionSize, MPI_DOUBLE, getNextProcessNumber(), GHOST_REGION_TAG, MPI_COMM_WORLD);
		MPI_Status status;
		MPI_Recv(&finalTemperatures[(finalTemperatures.size() - 1)], ghostRegionSize, MPI_DOUBLE, getNextProcessNumber(), GHOST_REGION_TAG, MPI_COMM_WORLD, &status);
	}

	void updateLeftGhostRegion(){
		MPI_Status status;
		MPI_Recv(&finalTemperatures[0], ghostRegionSize, MPI_DOUBLE, getPreviousProcessNumber(), GHOST_REGION_TAG, MPI_COMM_WORLD, &status);
		MPI_Send(&finalTemperatures[0 + ghostRegionSize], ghostRegionSize, MPI_DOUBLE, getPreviousProcessNumber(), GHOST_REGION_TAG, MPI_COMM_WORLD);
	}

	void updateBothGhostRegions(){
		updateLeftGhostRegion();
		updateRightGhostRegion();
	}

	void updateGhostRegions(){
		if(thisIsTheFirstProcess())
			updateRightGhostRegion();
		else if (thisIsTheLastProcess())
			updateLeftGhostRegion();
		else
			updateBothGhostRegions();
	}

	void simulateIterations(int iterations){
		this->finalTemperatures = this->initialTemperatures;
		for(int i = 0; i < iterations; i++){
			finalTemperatures = simulateNextTemperatures(finalTemperatures);
			if(thereIsMoreThanOneProcess())
				updateGhostRegions();
		}
		if(thereIsMoreThanOneProcess())
			updateFinalTemperatures();
	}
};