#pragma once


//this varable should enable many of the testing/debugging elements of the code
constexpr bool TESTMODE = true;
// this variable only applies if TESTMODE is true, it generates synthetic Data for all the sensors
constexpr bool USE_SYNTHETIC_DATA = true;


#include "BMI088.h"
BMI088 BMI(Wire, 10, 9);