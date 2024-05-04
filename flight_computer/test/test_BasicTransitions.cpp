#include "StateMachine_t.h"
#include "DataStructures.h"
#include "unity.h"


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
	StateMachine_t SM;
	SensorData SD{};
	SD.m_Bmp.Barometer = 3.5f;

	TEST_ASSERT_FLOAT_WITHIN(0.1, 3.5, SD.m_Bmp.Barometer);
	// inital state
	TEST_ASSERT_EQUAL_UINT8(FlightState::eUnarmed, SM.GetState());

	// switched state
	// TEST_ASSERT_EQUAL_UINT8(FlightState::eGroundIdle, SM.Run(SD));
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(CycleStates);
	return UNITY_END();
}
