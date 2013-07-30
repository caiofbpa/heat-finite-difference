#include <gtest/gtest.h>
#include <vector>

class HeatFiniteDifferenceTestSuite : public testing::Test {
protected:

	double delta = .001;

};

std::vector<double> calculateNextTemperatures(std::vector<double> temperatures){
	double fourierNumber = 0.2;
	std::vector<double> nextTemperatures(temperatures);

	for(int i = 1; i < (temperatures.size()-1); i++){
		double leftNeighbour = temperatures[i - 1];
		double previousTemperature = temperatures[i];
		double rightNeighbour = temperatures[i + 1];
		nextTemperatures[i] = previousTemperature + fourierNumber * (rightNeighbour - (2 * previousTemperature) + leftNeighbour);
	}
	
	return nextTemperatures;
}

TEST_F(HeatFiniteDifferenceTestSuite, ZeroTemperatures_MiddleShouldStayAtZero){
	std::vector<double> temperatures(3);
	temperatures[0] = 0.0;
	temperatures[1] = 0.0;
	temperatures[2] = 0.0;
	std::vector<double> nextTemperatures = calculateNextTemperatures(temperatures);
	ASSERT_NEAR(0, nextTemperatures[1], delta);
}

TEST_F(HeatFiniteDifferenceTestSuite, EqualTemperatures_MiddleShouldStayAtSameTemperature){
	std::vector<double> temperatures(3);
	temperatures[0] = 1.0;
	temperatures[1] = 1.0;
	temperatures[2] = 1.0;
	std::vector<double> nextTemperatures = calculateNextTemperatures(temperatures);
	ASSERT_NEAR(1, nextTemperatures[1], delta);
}

TEST_F(HeatFiniteDifferenceTestSuite, GivenACoolNeighbour_MiddleTemperatureShouldCool){
	std::vector<double> temperatures(3);
	temperatures[0] = 20.0;
	temperatures[1] = 20.0;
	temperatures[2] = 0.0;
	std::vector<double> nextTemperatures = calculateNextTemperatures(temperatures);
	ASSERT_NEAR(16, nextTemperatures[1], delta);
}

TEST_F(HeatFiniteDifferenceTestSuite, GivenAHotNeighbour_MiddleTemperatureShouldHeat){
	std::vector<double> temperatures(3);
	temperatures[0] = 20.0;
	temperatures[1] = 20.0;
	temperatures[2] = 50.0;
	std::vector<double> nextTemperatures = calculateNextTemperatures(temperatures);
	ASSERT_NEAR(26, nextTemperatures[1], delta);
}

TEST_F(HeatFiniteDifferenceTestSuite, ThreeTemperatures_Integration_Case1){
	std::vector<double> temperatures(3);
	temperatures[0] = 24.802;
	temperatures[1] = 29.657;
	temperatures[2] = 34.604;
	std::vector<double> nextTemperatures = calculateNextTemperatures(temperatures);
	ASSERT_NEAR(29.676, nextTemperatures[1], delta);
}

TEST_F(HeatFiniteDifferenceTestSuite, ThreeTemperatures_Integration_Case2){
	std::vector<double> temperatures(3);
	temperatures[0] = 39.976;
	temperatures[1] = 44.986;
	temperatures[2] = 50.0;
	std::vector<double> nextTemperatures = calculateNextTemperatures(temperatures);
	ASSERT_NEAR(44.987, nextTemperatures[1], delta);
}

TEST_F(HeatFiniteDifferenceTestSuite, FourTemperatures_Integration_Case1){
	std::vector<double> temperatures(4);
	temperatures[0] = 20.0;
	temperatures[1] = 20.0;
	temperatures[2] = 16.0;
	temperatures[3] = 0.0;
	std::vector<double> nextTemperatures = calculateNextTemperatures(temperatures);
	ASSERT_NEAR(19.2, nextTemperatures[1], delta);
	ASSERT_NEAR(13.6, nextTemperatures[2], delta);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}