#include <cmath>
#include "HeatPropagationSimulator.cc"
#include "MPIWrapper.cc"

#define GHOST_REGION_TAG 111110
#define FINAL_TEMPERATURES_TAG 111111

class ParallelHeatPropagationSimulator :public HeatPropagationSimulator {
private:
	int limit = 0;
	int ghostRegionSize = 1;
	MPIWrapper* mpi = new MPIWrapper();

public:

	void setMPIWrapper(MPIWrapper* mpi){
		this-> mpi = mpi;
	}

	void setGhostRegionSize(int size){
		ghostRegionSize = size;
	}

	void divideTemperatures(vector<double> temperatures){
		limit = ceil(temperatures.size() / mpi->getTotalProcesses());
		if(mpi->thisIsTheFirstProcess())
			this->initialTemperatures = vector<double>(temperatures.begin(), temperatures.begin() + (limit + ghostRegionSize));
		else if(mpi->thisIsTheLastProcess())
			this->initialTemperatures = vector<double>(temperatures.end() - (limit + ghostRegionSize), temperatures.end());
		else
			this->initialTemperatures = vector<double>(temperatures.begin() + (limit * mpi->getProcessNumber() - ghostRegionSize), temperatures.begin() + (limit * mpi->getProcessNumber() + limit + ghostRegionSize));
	}

	void setInitialTemperatures(vector<double> temperatures){
		if(mpi->thereIsMoreThanOneProcess())
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
		for(int i = mpi->getNextProcessNumber(); i < mpi->getTotalProcesses(); i++)
			receiveTemperaturesFromProcess(i);
	}

	void sendTemperaturesToFirstProcess(){
		MPI_Send(&finalTemperatures[ghostRegionSize], limit, MPI_DOUBLE, 0, FINAL_TEMPERATURES_TAG, MPI_COMM_WORLD);
	}

	void updateFinalTemperatures(){
		if(mpi->thisIsTheFirstProcess())
			receiveTemperaturesFromAllOtherProcesses();
		else
			sendTemperaturesToFirstProcess();
	}

	void updateRightGhostRegion(){
		MPI_Send(&finalTemperatures[finalTemperatures.size() - (2 * ghostRegionSize)], ghostRegionSize, MPI_DOUBLE, mpi->getNextProcessNumber(), GHOST_REGION_TAG, MPI_COMM_WORLD);
		MPI_Status status;
		MPI_Recv(&finalTemperatures[finalTemperatures.size() - ghostRegionSize], ghostRegionSize, MPI_DOUBLE, mpi->getNextProcessNumber(), GHOST_REGION_TAG, MPI_COMM_WORLD, &status);
	}

	void updateLeftGhostRegion(){
		MPI_Status status;
		MPI_Recv(&finalTemperatures[0], ghostRegionSize, MPI_DOUBLE, mpi->getPreviousProcessNumber(), GHOST_REGION_TAG, MPI_COMM_WORLD, &status);
		MPI_Send(&finalTemperatures[ghostRegionSize], ghostRegionSize, MPI_DOUBLE, mpi->getPreviousProcessNumber(), GHOST_REGION_TAG, MPI_COMM_WORLD);
	}

	void updateBothGhostRegions(){
		updateLeftGhostRegion();
		updateRightGhostRegion();
	}

	void updateGhostRegions(){
		if(mpi->thisIsTheFirstProcess())
			updateRightGhostRegion();
		else if (mpi->thisIsTheLastProcess())
			updateLeftGhostRegion();
		else
			updateBothGhostRegions();
	}

	void updateGhostRegionsIfNecessary(){
		if(mpi->thereIsMoreThanOneProcess()) updateGhostRegions();
	}

	void updateFinalTemperaturesIfNecessary(){
		if(mpi->thereIsMoreThanOneProcess()) updateFinalTemperatures();
	}

	void simulateIterations(int iterations){
		this->finalTemperatures = this->initialTemperatures;
		for(int i = 0; i < iterations; i++){
			finalTemperatures = simulateNextTemperatures(finalTemperatures);
			updateGhostRegionsIfNecessary();
		}
		updateFinalTemperaturesIfNecessary();
	}
};