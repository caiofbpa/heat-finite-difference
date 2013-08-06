#include <mpi.h>

class MPIWrapper {
private:
	int totalProcesses;
	int processNumber;
public:
	void initialise(){
		MPI_Init(NULL, NULL);
	}

	int getTotalProcesses(){
		if(! totalProcesses)
			MPI_Comm_size(MPI_COMM_WORLD, &totalProcesses);
		return totalProcesses;
	}

	int getProcessNumber(){
		if(! processNumber)
			MPI_Comm_rank(MPI_COMM_WORLD, &processNumber);
		return processNumber;
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

	void finalise(){
		MPI_Finalize();
	}
};