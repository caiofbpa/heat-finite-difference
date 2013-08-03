#include "gtest/gtest.h"
#include <vector>
#include "../src/HeatPropagationSimulator.cc"

using namespace std;

string getOutputFromStream(FILE* stream){
	char buffer[512];
	string output;
    while(fgets(buffer, sizeof(buffer), stream) != NULL)
        output += buffer;
    return output;
}

string executeCommand(string command){
	FILE* stream = popen(command.c_str(), "r");
	string output = getOutputFromStream(stream);
	pclose(stream);
	return output;
}

TEST(ParallelHeatFiniteDifferenceTestSuite, ZeroTemperature_SteadyState_AllTemperaturesShouldStayTheSame){
	string output = executeCommand("bin/main.bin 0 0 0 1");
    ASSERT_EQ("0.000 0.000 0.000 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SameTemperature_SteadyState_AllTemperaturesShouldStayTheSame){
	string output = executeCommand("bin/main.bin 1 1 1 1");
    ASSERT_EQ("1.000 1.000 1.000 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, GivenACoolNeighbour_MiddleTemperatureShouldCool){
	string output = executeCommand("bin/main.bin 20 20 0 1");
    ASSERT_EQ("20.000 16.000 0.000 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, GivenAHotNeighbour_MiddleTemperatureShouldHeat){
	string output = executeCommand("bin/main.bin 20 20 50 1");
    ASSERT_EQ("20.000 26.000 50.000 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, ThreeTemperatures_Integration_Case1){
	string output = executeCommand("bin/main.bin 24.802 29.657 34.604 1");
    ASSERT_EQ("24.802 29.675 34.604 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, ThreeTemperatures_Integration_Case2){
	string output = executeCommand("bin/main.bin 39.976 44.986 50 1");
    ASSERT_EQ("39.976 44.987 50.000 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, FourTemperatures_Integration_Case1){
	string output = executeCommand("bin/main.bin 20 20 16 0 1");
    ASSERT_EQ("20.000 19.200 13.600 0.000 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, FourTemperatures_Integration_Case2){
	string output = executeCommand("bin/main.bin 38.4 30 22 26 1");
    ASSERT_EQ("38.400 30.080 24.400 26.000 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SevenTemperatures_Integration){
	string output = executeCommand("bin/main.bin 20 50 40 30 20 10 50 1");
    ASSERT_EQ("20.000 42.000 40.000 30.000 20.000 20.000 50.000 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SevenAsymmetricTemperatures_Integration_AfterLongTime){
	string output = executeCommand("bin/main.bin 20 50 40 30 20 10 50 99");
    ASSERT_EQ("20.000 24.987 29.977 34.973 39.977 44.987 50.000 \n", output);
}

TEST(ParallelHeatFiniteDifferenceTestSuite, SevenSymmetricTemperatures_Integration_AfterLongTime){
	string output = executeCommand("bin/main.bin 0 20 20 20 20 20 20 20 20 20 0 100");
    ASSERT_EQ("0.000 1.081 2.055 2.829 3.326 3.497 3.326 2.829 2.055 1.081 0.000 \n", output);
}