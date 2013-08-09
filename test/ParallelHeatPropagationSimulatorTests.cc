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

void assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(int cores, int ghostRegionSize){
	char buffer[512];
	sprintf(buffer, "mpirun -n %d bin/main.bin %s -i %d -g %d", cores, initialTemperatures.c_str(), iterations, ghostRegionSize);
	string actualTemperatures = executeCommand(buffer);
	ASSERT_EQ(expectedTemperatures, actualTemperatures);
}

void setup_SteadyState_SameTemperatures(){
	initialTemperatures = "1 1 1 1 1 1 1 1 1 1 1 1";
	expectedTemperatures = "1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000 1.000";
}

void setup_SteadyState_SameTemperatures_OneIteration(){
	setup_SteadyState_SameTemperatures();
	iterations = 1;
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_OneProcess_GhostRegionSizeOne){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_OneProcess_GhostRegionSizeTwo){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_OneProcess_GhostRegionSizeThree){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_OneProcess_GhostRegionSizeFour){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_TwoProcesses_GhostRegionSizeOne){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_TwoProcesses_GhostRegionSizeTwo){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_TwoProcesses_GhostRegionSizeThree){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_TwoProcesses_GhostRegionSizeFour){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_ThreeProcesses_GhostRegionSizeOne){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_ThreeProcesses_GhostRegionSizeTwo){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_ThreeProcesses_GhostRegionSizeThree){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_ThreeProcesses_GhostRegionSizeFour){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_FourProcesses_GhostRegionSizeOne){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_FourProcesses_GhostRegionSizeTwo){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_FourProcesses_GhostRegionSizeThree){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_OneIteration_FourProcesses_GhostRegionSizeFour){
	setup_SteadyState_SameTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 4);
}

void setup_SteadyState_SameTemperatures_NinetyNineIterations(){
	setup_SteadyState_SameTemperatures();
	iterations = 99;
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_OneProcess_GhostRegionSizeOne){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_OneProcess_GhostRegionSizeTwo){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_OneProcess_GhostRegionSizeThree){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_OneProcess_GhostRegionSizeFour){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_TwoProcesses_GhostRegionSizeOne){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_TwoProcesses_GhostRegionSizeTwo){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_TwoProcesses_GhostRegionSizeThree){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_TwoProcesses_GhostRegionSizeFour){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_ThreeProcesses_GhostRegionSizeOne){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_ThreeProcesses_GhostRegionSizeTwo){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_ThreeProcesses_GhostRegionSizeThree){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_ThreeProcesses_GhostRegionSizeFour){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_FourProcesses_GhostRegionSizeOne){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_FourProcesses_GhostRegionSizeTwo){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_FourProcesses_GhostRegionSizeThree){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_SameTemperatures_ManyIterations_FourProcesses_GhostRegionSizeFour){
	setup_SteadyState_SameTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 4);
}

void setup_SteadyState_DifferentTemperatures(){
	initialTemperatures = "10 20 30 40 50 60 70 80 90 100 110 120";
	expectedTemperatures = "10.000 20.000 30.000 40.000 50.000 60.000 70.000 80.000 90.000 100.000 110.000 120.000";
}

void setup_SteadyState_DifferentTemperatures_OneIteration(){
	setup_SteadyState_DifferentTemperatures();
	iterations = 1;
}


TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_OneProcess_GhostRegionSizeOne){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_OneProcess_GhostRegionSizeTwo){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_OneProcess_GhostRegionSizeThree){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_OneProcess_GhostRegionSizeFour){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_TwoProcesses_GhostRegionSizeOne){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_TwoProcesses_GhostRegionSizeTwo){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_TwoProcesses_GhostRegionSizeThree){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_TwoProcesses_GhostRegionSizeFour){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_ThreeProcesses_GhostRegionSizeOne){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_ThreeProcesses_GhostRegionSizeTwo){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_ThreeProcesses_GhostRegionSizeThree){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_ThreeProcesses_GhostRegionSizeFour){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_FourProcesses_GhostRegionSizeOne){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_FourProcesses_GhostRegionSizeTwo){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_FourProcesses_GhostRegionSizeThree){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_OneIteration_FourProcesses_GhostRegionSizeFour){
	setup_SteadyState_DifferentTemperatures_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 4);
}

void setup_SteadyState_DifferentTemperatures_NinetyNineIterations(){
	setup_SteadyState_DifferentTemperatures();
	iterations = 99;
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_OneProcess_GhostRegionSizeOne){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_OneProcess_GhostRegionSizeTwo){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_OneProcess_GhostRegionSizeThree){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_OneProcess_GhostRegionSizeFour){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_TwoProcesses_GhostRegionSizeOne){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_TwoProcesses_GhostRegionSizeTwo){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_TwoProcesses_GhostRegionSizeThree){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_TwoProcesses_GhostRegionSizeFour){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_ThreeProcesses_GhostRegionSizeOne){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
	assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_ThreeProcesses_GhostRegionSizeTwo){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
	assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_ThreeProcesses_GhostRegionSizeThree){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
	assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_ThreeProcesses_GhostRegionSizeFour){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
	assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_FourProcesses_GhostRegionSizeOne){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_FourProcesses_GhostRegionSizeTwo){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_FourProcesses_GhostRegionSizeThree){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SteadyState_DifferentTemperatures_ManyIterations_FourProcesses_GhostRegionSizeFour){
	setup_SteadyState_DifferentTemperatures_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 4);
}

void setup_Integration(){
	initialTemperatures = "20 100 90 80 70 60 50 40 30 20 10 50";
}

void setup_Integration_OneIteration(){
	setup_Integration();
	iterations = 1;
	expectedTemperatures = "20.000 82.000 90.000 80.000 70.000 60.000 50.000 40.000 30.000 20.000 20.000 50.000";
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_OneProcess_GhostRegionSizeOne){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_OneProcess_GhostRegionSizeTwo){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_OneProcess_GhostRegionSizeThree){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_OneProcess_GhostRegionSizeFour){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_TwoProcesses_GhostRegionSizeOne){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_TwoProcesses_GhostRegionSizeTwo){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_TwoProcesses_GhostRegionSizeThree){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_TwoProcesses_GhostRegionSizeFour){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_ThreeProcesses_GhostRegionSizeOne){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_ThreeProcesses_GhostRegionSizeTwo){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_ThreeProcesses_GhostRegionSizeThree){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_ThreeProcesses_GhostRegionSizeFour){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_FourProcesses_GhostRegionSizeOne){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_FourProcesses_GhostRegionSizeTwo){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_FourProcesses_GhostRegionSizeThree){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_OneIteration_FourProcesses_GhostRegionSizeFour){
	setup_Integration_OneIteration();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 4);
}

void setup_Integration_NinetyNineIterations(){
	setup_Integration();
	iterations = 99;
	expectedTemperatures = "20.000 24.177 28.228 32.040 35.524 38.623 41.313 43.607 45.547 47.199 48.651 50.000";
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_OneProcess_GhostRegionSizeOne){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_OneProcess_GhostRegionSizeTwo){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_OneProcess_GhostRegionSizeThree){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_OneProcess_GhostRegionSizeFour){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(1, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_TwoProcesses_GhostRegionSizeOne){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_TwoProcesses_GhostRegionSizeTwo){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_TwoProcesses_GhostRegionSizeThree){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_TwoProcesses_GhostRegionSizeFour){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(2, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_ThreeProcesses_GhostRegionSizeOne){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_ThreeProcesses_GhostRegionSizeTwo){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_ThreeProcesses_GhostRegionSizeThree){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_ThreeProcesses_GhostRegionSizeFour){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(3, 4);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_FourProcesses_GhostRegionSizeOne){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 1);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_FourProcesses_GhostRegionSizeTwo){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 2);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_FourProcesses_GhostRegionSizeThree){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 3);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, Integration_ManyIterations_FourProcesses_GhostRegionSizeFour){
	setup_Integration_NinetyNineIterations();
    assertTemperaturesAreEqualToExpectedWhenExecutedInCoresWithGhostRegionSize(4, 4);
}