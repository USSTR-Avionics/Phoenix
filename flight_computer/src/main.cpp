#include "Global.h"

#include "StateMachine.h"
#include <Watchdog_t4.h>
#include <cstdint>

#include "Utils/Functions.h"

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
RA::Radio* Radio;
} // namespace RA::Global::IO

StateMachine StateMachine;
/* WDT_T4<WDT2> WatchDog; */

void WatchDogInterrupt()
{
    Serial.println("WatchDog bit you!!");
    StateMachine.GoState<InFlight>();
    // WatchDog.feed();
}

void setup()
{
    pinMode(20, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(18, OUTPUT);

    // Radio must be created here, or board crashes
    RA::Global::IO::Radio = new RA::Radio {0, 0};

    // watch dog
    // WatchDog.begin({// jump to callback
    //                 .trigger  = 10.0,
    //                 // board shutdown
    //                 .timeout  = 20.0,
    //                 .pin      = 13,
    //                 .callback = WatchDogInterrupt});
    // ==============

    Serial.begin(9600);
    while (!Serial)
        delay(100); // wait for native usb

    // check StateMachine
    // if (!StateMachine.Ready())
    // {
    //     Serial.println("BaseState machine could not allocate memory pool");
    // }
    RA::Global::IO::Sensor.Setup();

    // CHANGE THIS NUMBER
    if (!RA::Global::IO::FRam.Init(0x50))
    {
        Serial.println("Failed to init FRam at addr");
    }

    // auto tim = millis();
}

void loop()
{
    Serial.println(to_string(StateMachine.Run()));
    // WatchDog.feed();

    // #ifdef TEENSY_OPT_DEBUG
    // Serial.println("DebugMacroWorks");
    // #endif
    // StateMachine.Run(Sensors);
}
