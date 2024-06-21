#ifndef FLIGHT_COMPUTER_GLOBAL_H
#define FLIGHT_COMPUTER_GLOBAL_H

#include "FRAM.h"
#include "Sensors.h"
#include "Radio.h"

namespace RA::Global::IO
{
// RA::Sensors RA::Global::IO::Sensors{};
/**
 * Construct sensors
 * @param ThermocouplePin SCLK, CS, MISO
 * @param BmiPin Accel addr, Gyo addr
 * @param KxAccelPin KxAccelPin
 */
extern RA::Sensors Sensor;
extern FRAM FRam;
extern RA::Radio* Radio;
} // namespace RA::Global::IO
#endif // FLIGHT_COMPUTER_GLOBAL_H
