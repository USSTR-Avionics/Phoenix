#include <unity.h>
#include "StateMachine.h"

void setUp(void)
{
	// set stuff up here
}

void tearDown(void)
{
	// clean stuff up here
}

void CycleStates()
{
	RA::StateMachine SM{};
	SensorData SD{};
	SD.m_BarometerVal = 3.5;

	TEST_ASSERT_FLOAT_WITHIN(0.1, 3.5, SD.m_BarometerVal);
	// inital state
	// TEST_ASSERT_EQUAL_UINT8(FlightState::eUnarmed, SM.GetState());

	// switched state
	// TEST_ASSERT_EQUAL_UINT8(FlightState::eGroundIdle, SM.Run(SD));
}

int main(int argc, char **argv)
{
	UNITY_BEGIN();
	RUN_TEST(CycleStates);
	return UNITY_END();
}
