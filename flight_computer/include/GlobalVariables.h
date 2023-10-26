#pragma once
#include "Utils/MemoryPool.h"
#include "States/Unarmed.h"
#include "States/GroundIdle.h"
#include "States/PoweredFlight.h"
#include "States/UnpoweredFlight.h"
#include "States/BallisticDescent.h"
#include "States/MainChute.h"
#include "States/Land.h"


//this varable should enable many of the testing/debugging elements of the code
constexpr bool TESTMODE = true;
// this variable only applies if TESTMODE is true, it generates synthetic Data for all the sensors
constexpr bool USE_SYNTHETIC_DATA = true;

static UA::MemoryPool<Unarmed, GroundIdle, PoweredFlight, UnpoweredFlight, BallisticDescent, MainChute, Land> StatePool;

#include <variant>
extern std::variant<Unarmed, GroundIdle, PoweredFlight, UnpoweredFlight, BallisticDescent, MainChute, Land> v;