#include <gtest/gtest.h>
#include <vector>

using namespace std;

double delta = .001;

double simulateNextTemperature(double leftNeighbour, double previousTemperature, double rightNeighbour){
	double fourierNumber = 0.2;
	double nextTemperature = previousTemperature + fourierNumber * (rightNeighbour - (2 * previousTemperature) + leftNeighbour);
	return nextTemperature;
}

vector<double> simulateNextTemperatures(vector<double> temperatures){
	vector<double> nextTemperatures(temperatures);
	for(int i = 1; i < (temperatures.size() - 1); i++)
		nextTemperatures[i] = simulateNextTemperature(temperatures[i - 1], temperatures[i], temperatures[i + 1]);
	return nextTemperatures;
}

vector<double> simulateTemperaturesAfterTime(vector<double> temperatures, int seconds){
	for(int i = 0; i < seconds; i++)
		temperatures = simulateNextTemperatures(temperatures);
	return temperatures;
}

void assertVectorsHaveEqualValues(vector<double> expected, vector<double> actual){
	for(int i = 0; i < expected.size(); i++)
		ASSERT_NEAR(expected[i], actual[i], delta);
}

TEST(HeatFiniteDifferenceTestSuite, ZeroTemperature_SteadyState_AllTemperaturesShouldStayTheSame){
	double initial[] = {0.0, 0.0, 0.0};
	double expected[] = {0.0, 0.0, 0.0};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 1);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, SameTemperature_SteadyState_AllTemperaturesShouldStayTheSame){
	double initial[] = {1.0, 1.0, 1.0};
	double expected[] = {1.0, 1.0, 1.0};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 1);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, GivenACoolNeighbour_MiddleTemperatureShouldCool){
	double initial[] = {20.0, 20.0, 0.0};
	double expected[] = {20.0, 16.0, 0.0};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 1);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, GivenAHotNeighbour_MiddleTemperatureShouldHeat){
	double initial[] = {20.0, 20.0, 50.0};
	double expected[] = {20.0, 26.0, 50.0};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 1);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, ThreeTemperatures_Integration_Case1){
	double initial[] = {24.802, 29.657, 34.604};
	double expected[] = {24.802, 29.676, 34.604};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 1);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, ThreeTemperatures_Integration_Case2){
	double initial[] = {39.976, 44.986, 50.0};
	double expected[] = {39.976, 44.987, 50.0};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 1);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, FourTemperatures_Integration_Case1){
	double initial[] = {20.0, 20.0, 16.0, 0.0};
	double expected[] = {20.0, 19.2, 13.6, 0.0};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 1);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, FourTemperatures_Integration_Case2){
	double initial[] = {38.4, 30.0, 22.0, 26.0};
	double expected[] = {38.4, 30.08, 24.4, 26.0};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 1);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, SevenTemperatures_Integration){
	double initial[] = {20.0, 50.0, 40.0, 30.0, 20.0, 10.0, 50.0};
	double expected[] = {20.0, 42.0, 40.0, 30.0, 20.0, 20.0, 50.0};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 1);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

TEST(HeatFiniteDifferenceTestSuite, SevenTemperatures_Integration_AfterLongTime){
	double initial[] = {20.0, 50.0, 40.0, 30.0, 20.0, 10.0, 50.0};
	double expected[] = {20.0, 24.987, 29.977, 34.973, 39.977, 44.987, 50.0};
	vector<double> temperatures (initial, initial + sizeof(initial) / sizeof(initial[0]));
	vector<double> expectedTemperatures (expected, expected + sizeof(expected) / sizeof(expected[0]));
	vector<double> nextTemperatures = simulateTemperaturesAfterTime(temperatures, 99);
	assertVectorsHaveEqualValues(expectedTemperatures, nextTemperatures);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}