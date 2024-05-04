#ifndef FLIGHT_COMPUTER_GLOBAL_H
#define FLIGHT_COMPUTER_GLOBAL_H

#include "Watchdog_t4.h"
#include "FRAM_t.h"
#include "StateMachine_t.h"
#include "Radio_t.h"

namespace RA::Global
{
	extern RA::Sensor_t Sensor;
	extern FRAM_t FRam;
	extern Radio_t Radio;
	extern StateMachine_t StateMachine;
	extern WDT_T4<WDT2> WatchDog;
}
#endif //FLIGHT_COMPUTER_GLOBAL_H
