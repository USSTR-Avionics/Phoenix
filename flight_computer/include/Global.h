#ifndef FLIGHT_COMPUTER_GLOBAL_H
#define FLIGHT_COMPUTER_GLOBAL_H

#include "FRAM_t.h"
#include "Sensor_t.h"
#include "Radio_t.h"

namespace RA::Global::IO
{
	extern RA::Sensor_t Sensor;
	extern FRAM_t FRam;
	extern Radio_t Radio;
}
#endif //FLIGHT_COMPUTER_GLOBAL_H
