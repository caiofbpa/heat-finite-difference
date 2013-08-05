#include "gtest/gtest.h"
#include <vector>
#include <thread>
#include "../src/HeatPropagationSimulator.cc"

using namespace std;

string initialTemperatures;
int iterations;
string expectedTemperatures;

string getOutputFromStream(FILE* stream){
	char buffer[512];
	string output;
    while(fgets(buffer, sizeof(buffer), stream) != NULL)
        output += buffer;
    return output;
}

string executeCommand(char* command){
	FILE* stream = popen(command, "r");
	string output = getOutputFromStream(stream);
	pclose(stream);
	return output;
}

int getNumberOfCoresAvailable(){
	if(0 == thread::hardware_concurrency())
		return 1;
	else
		return thread::hardware_concurrency();
}

void assertTemperaturesAreEqualToExpectedWhenExecutedInNCores(int cores){
	char buffer[512];
	sprintf(buffer, "mpirun -n %d bin/main.bin %s %d", cores, initialTemperatures.c_str(), iterations);
	string actualTemperatures = executeCommand(buffer);
	ASSERT_EQ(expectedTemperatures, actualTemperatures) << "When running with " << cores << " cores";
}

void assertTemperaturesAreEqualToExpectedWhenExecutedInMultipleCores(){
	int cores = getNumberOfCoresAvailable();
	for(int i = 1; i <= cores; i++){
		assertTemperaturesAreEqualToExpectedWhenExecutedInNCores(i);
	}
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures){
	initialTemperatures = "1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000";
	iterations = 1;
	expectedTemperatures = "1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 ";
    assertTemperaturesAreEqualToExpectedWhenExecutedInMultipleCores();
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations){
	initialTemperatures = "1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000";
	iterations = 99;
	expectedTemperatures = "1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 ";
    assertTemperaturesAreEqualToExpectedWhenExecutedInMultipleCores();
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures){
	initialTemperatures = "10 20 30 40 50 60 70 80 90 100 110 120";
	iterations = 1;
	expectedTemperatures = "10.000 20.000 30.000 40.000 50.000 60.000 70.000 80.000 90.000 100.000 110.000 120.000 ";
    assertTemperaturesAreEqualToExpectedWhenExecutedInMultipleCores();
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations){
	initialTemperatures = "10 20 30 40 50 60 70 80 90 100 110 120";
	iterations = 99;
	expectedTemperatures = "10.000 20.000 30.000 40.000 50.000 60.000 70.000 80.000 90.000 100.000 110.000 120.000 ";
    assertTemperaturesAreEqualToExpectedWhenExecutedInMultipleCores();
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_Asymmetric){
	initialTemperatures = "20 100 90 80 70 60 50 40 30 20 10 50";
	iterations = 1;
	expectedTemperatures = "20.000 82.000 90.000 80.000 70.000 60.000 50.000 40.000 30.000 20.000 20.000 50.000 ";
    assertTemperaturesAreEqualToExpectedWhenExecutedInMultipleCores();
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_Asymmetric_ManyIterations){
	initialTemperatures = "20 100 90 80 70 60 50 40 30 20 10 50";
	iterations = 99;
	expectedTemperatures = "20.000 24.177 28.228 32.040 35.524 38.623 41.313 43.607 45.547 47.199 48.651 50.000 ";
    assertTemperaturesAreEqualToExpectedWhenExecutedInMultipleCores();
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_Symmetric_ManyIterations){
	initialTemperatures = "0 50 50 50 50 50 50 50 50 50 50 0";
	iterations = 100;
	expectedTemperatures = "0.000 3.478 6.674 9.329 11.229 12.219 12.219 11.229 9.329 6.674 3.478 0.000 ";
    assertTemperaturesAreEqualToExpectedWhenExecutedInMultipleCores();
}