# University of Saskatchewan Space Design Team: Avionics
# Setup
PlatformIO (VSCode recommended)  

## Things you need to get started
- [ ] VSCode / editor of choice
- [ ] platformIO extension  
- [ ] git


## Next Steps

1. Fork the codebase  
    a. Visit the link and fork the code base to your own profle by simply clicking fork  
    b. Clone your own fork to your local machine  
    c. Add the upstream repo to get latest changes  
    d. Run this command which enables you to get the latest changes from master  
    `git remote add upstream https://github.com/USSTR-Avionics/Avionics-code.git`  

    [troubleshooting] if you get an error saying https protocol not supported, simply erase the https:// from the pasted url and rewrite it in, there is a 
    hidden character that gets pasted (sneaky!) on Windows.  

2. Navigate to Extensions on VSCode and install "PlatoformIO IDE"  
    [note] restarting VSCode may be required and an internet connection is required!  

3. Select the "PIO Home" tab in VSCode > "Import Existing Project" > Navigate to the directory where the codebase was cloned >   
    open "CPP_flight_computer_code" > Scroll down to reveal the "Import Project" > Select board as "Teensy 4.1"  

4. At the bottom click on the checkbox to build the codebase
5. [If you are not using VSCode](https://docs.platformio.org/en/latest/integration/ide/)

run `pio run -t compiledb` if you need the latest compilation_commands.json file for DAP interface(s).


## BUILDING

### Using the terminal
`pio run` while in the directory where platform.ini is located

### Using VSCode and PlatoformIO
Click on the :heavy_check_mark: on the bottom bar in VSCode to compile


# Contributing

1. Make sure you have all the remote changes  
    `git pull`  
    `git fetch --all`  
    `git pull upstream master`   
    `git pull upstream dev`  
    `git fetch upstream master`  
    `git fetch upstream dev`  

2. Open up a Pull Request with an appropriate title and explanantion of code changes

> "Your git commits should tell us WHY and not WHAT, the code tells us what was changed you should
tell us why it was changed"


# Documentation

Documentation is not expected for code, as long as variables, methods, and files are resonably named and follow the naming standards laid out in READMEs.\
This is because we believe code is the best documentation as it never gets outdated, because if it gets outdated it doesn't compile anymore. Hence, will always remain up to date.
However, provide documentation wherever relevant

Javadoc style of comments are strongly recommended, but only after that function has been stabilised. Don't write documentation while developing.

```
/**
 * @brief      writes an u8 to the given FRAM address
 * @param      what    The u8 to be written
 * @param      where   The address where it is to be written
 * @return     int     0 on success; 1 on failure
*/

int write_to_fram(uint8_t what, uint8_t where)
{
    // a black box
}

```

# Coding Style Guidelines

These are suggestions
> NOTE: most of the linting is handled by clang-format-15

## Naming things
- **DO NOT PREFIX VARIABLES WITH `_` OR `__`, THEY ARE USUALLY RESERVED. MIGHT BREAK CODE**
- [Try to adopt Hungarian notation for complex types for easier readibility](https://en.wikipedia.org/wiki/Hungarian_notation)
```
// b for bool
bool bHasCrashed = false;

// p, pointer
Sensor* pSensor = Sensor.getSensor();

// e, enum
enum A { eType1, eType2 };

// 2 abbrivations side by side (ABR, FSM) with type T
T ABR_FSM_Var;

// do not go over board
varchar(30) a_crszkvc30LastNameCol // a constant reference argument, holding the contents of a database
                                    column LastName of type varchar(30)

```
### Variables

- Pascal case preferred
```
size_t TimesCrashed = 0;
float CurrentAltitude = -128;
```
- Prefer [fixed width integer types](https://en.cppreference.com/w/cpp/types/integer)
```
int32_t Counter = 1;
uint32_t Counter = 0;
uint8_t Byte = 0b0;
float Temperature = 20.f; // note 20.0 is a double
```

- Every variable should be initialized with a value to prevent undefined behaviour!

- Macros must be upper case

```
    #define A_CONST 100
```
- Class member variables should have prefix `m_` for member
```
class A
{
public:
private:
    int m_Size = 0;
};
```

### Functions
- Preferred style : pascal cased function name with C style brackets
```
void Function()
{
    // stuff
}
```
- Pass by reference when it makes sense
```
// copy of a is being made (copy elision exists, but...)
void Function1(int a){}

// gets the reference of a, but if you modify a, it will modify it everywhere
void Function2(int& a){}

// const makes it unmodifiable, but no copy
void Function3(const int& a){}
```
### Classes
- Classes are private by default
- Put your public functions that will be used first 
```
class A
{
public:
    A();
    void SetTemperature(int Temperature);
    
private:
    float m_Temperature;
    int m_Size;
};
```
- Keep class functions pascal case
- Try not to implement any of the class functions inside header file
### Header files

These are broad guidelines and **NOT** rules, break them if it doesn't make sense

We classify headers into 4 types

1. Package
    A set of functions that serve a common function, eg: a statistics package
    prefixed with a "Package_"

2. Debug
    Functions associated with easy debugging, eg: I2C Scanner, these are only
    activated or in use when a directive or variable is enabled, prefixed with
    a "Debug_"

3. Sensor
    Functions that serve as a wrapper/API for sensors, sensors include
    peripherals like memory and sensors like acceleration. tldr; anything that
    has a hardware component that the flight computer interacts with is a 
    sensor, prefixed with a "Sensor_"

4. Organisational/Misc
    Some headers are just for storing default variables or macros and fall
    under this categories, need not be prefixed.

**NOTE:** Other naming scheme maybe applied if it makes sense, for example, the 
    header file containing the enum definition for the statemachine is called
    Statemachine_t.h as the _t suffix denotes type by convention.

### Include Guards
To prevent multiple includes of the same file that results in linker error, use include guards
```
File : StateMachine.h

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// Type 1
#ifndef STATEMACHINE_H // if not defined
#define STATEMACHINE_H // define

#include <abc>
#include "def"

class StateMachine{};

#endif
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Type 2
#pragma once

#include <abc>
#include "def"

class StateMachine{};
```
Note : Type 2 is not guaranteed to work, it depends on the compiler. But it works on most of the compilers.
### Source files

They should be named similar to their respective header files that expose the API function calls

Should also adhere to the header file(s) naming convention

---
<p align="center"> <img src = https://i.imgur.com/jnRxNR3.png> </img> </p>
