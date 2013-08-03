#include "gtest/gtest.h"
#include <vector>
#include "../src/HeatPropagationSimulator.cc"

using namespace std;

double delta = .001;
HeatPropagationSimulator *simulator = new HeatPropagationSimulator();

void assertVectorsHaveEqualValues(vector<double> expected, vector<double> actual){
	for(int i = 0; i < expected.size(); i++)
		ASSERT_NEAR(expected[i], actual[i], delta);
}

TEST(HeatFiniteDifferenceTestSuite, ZeroTemperature_SteadyState_AllTemperaturesShouldStayTheSame){
	simulator->setInitialTemperatures({0.0, 0.0, 0.0});
	simulator->simulateIterations(1);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({0.0, 0.0, 0.0}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, SameTemperature_SteadyState_AllTemperaturesShouldStayTheSame){
	simulator->setInitialTemperatures({1.0, 1.0, 1.0});
	simulator->simulateIterations(1);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({1.0, 1.0, 1.0}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, GivenACoolNeighbour_MiddleTemperatureShouldCool){
	simulator->setInitialTemperatures({20.0, 20.0, 0.0});
	simulator->simulateIterations(1);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({20.0, 16.0, 0.0}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, GivenAHotNeighbour_MiddleTemperatureShouldHeat){
	simulator->setInitialTemperatures({20.0, 20.0, 50.0});
	simulator->simulateIterations(1);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({20.0, 26.0, 50.0}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, ThreeTemperatures_Integration_Case1){
	simulator->setInitialTemperatures({24.802, 29.657, 34.604});
	simulator->simulateIterations(1);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({24.802, 29.676, 34.604}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, ThreeTemperatures_Integration_Case2){
	simulator->setInitialTemperatures({39.976, 44.986, 50.0});
	simulator->simulateIterations(1);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({39.976, 44.987, 50.0}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, FourTemperatures_Integration_Case1){
	simulator->setInitialTemperatures({20.0, 20.0, 16.0, 0.0});
	simulator->simulateIterations(1);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({20.0, 19.2, 13.6, 0.0}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, FourTemperatures_Integration_Case2){
	simulator->setInitialTemperatures({38.4, 30.0, 22.0, 26.0});
	simulator->simulateIterations(1);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({38.4, 30.08, 24.4, 26.0}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, SevenTemperatures_Integration){
	simulator->setInitialTemperatures({20.0, 50.0, 40.0, 30.0, 20.0, 10.0, 50.0});
	simulator->simulateIterations(1);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({20.0, 42.0, 40.0, 30.0, 20.0, 20.0, 50.0}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, SevenAsymmetricTemperatures_Integration_AfterLongTime){
	simulator->setInitialTemperatures({20.0, 50.0, 40.0, 30.0, 20.0, 10.0, 50.0});
	simulator->simulateIterations(99);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({20.0, 24.987, 29.977, 34.973, 39.977, 44.987, 50.0}, finalTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, SevenSymmetricTemperatures_Integration_AfterLongTime){
	simulator->setInitialTemperatures({0.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 0.0});
	simulator->simulateIterations(100);
	vector<double> finalTemperatures = simulator->getFinalTemperatures();
	assertVectorsHaveEqualValues({0.0, 1.081, 2.055, 2.829, 3.326, 3.497, 3.326, 2.829, 2.055, 1.081, 0.0}, finalTemperatures);
}