#include "Global.h"

namespace RA::Global::IO
{
// RA::Sensors RA::Global::IO::Sensors{};
/**
 * Construct sensors
 * @param ThermocouplePin SCLK, CS, MISO
 * @param BmiPin Accel addr, Gyo addr
 * @param KxAccelPin KxAccelPin
 */
RA::Sensors Sensor {
    {18, 4, 19},
    {18, 18},
    18
};
FRAM FRam {1, 32000};
RA::Radio Radio {0, 0};
} // namespace RA::Global::IO
