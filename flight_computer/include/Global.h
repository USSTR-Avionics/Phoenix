#ifndef FLIGHT_COMPUTER_GLOBAL_H
#define FLIGHT_COMPUTER_GLOBAL_H

#include "FRAM.h"
#include "Sensors.h"
#include "Radio.h"

namespace RA::Global::IO
{
	extern RA::Sensors Sensor;
	extern FRAM FRam;
	extern RA::Radio Radio;
}
#endif //FLIGHT_COMPUTER_GLOBAL_H
