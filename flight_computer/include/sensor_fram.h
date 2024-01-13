#ifndef SENSOR_FRAM_H
#define SENSOR_FRAM_H

#include <stdint.h>

#define FRAM_MAX_ADDRESS  0x7FE0
#define FRAM_MIN_ADDRESS  0x00
#define FRAM_INIT_ADDRESS 0x10

// actual funcs
int init_fram();

// ! These should not be used directly, use the package_fram.h API instead
int write_to_fram(uint8_t, uint16_t);
int read_from_fram(int);

#endif // SENSOR_FRAM_H
