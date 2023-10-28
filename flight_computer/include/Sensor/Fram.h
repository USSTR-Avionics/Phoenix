//
// Created by TDKua on 2023/10/24.
//

#ifndef FLIGHT_COMPUTER_FRAM_H
#define FLIGHT_COMPUTER_FRAM_H

#include <stdint.h>

#define FRAM_MAX_ADDRESS  0x7FE0
#define FRAM_MIN_ADDRESS  0x00
#define FRAM_INIT_ADDRESS 0x10

// actual funcs
int InitFram();

// ! These should not be used directly, use the package_fram.h API instead
int FramWrite(uint8_t, uint16_t);
int FramRead(int);

#endif //FLIGHT_COMPUTER_FRAM_H
