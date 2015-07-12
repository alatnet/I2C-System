/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once
#include "I2C System Header.h"
#include "I2C Defines.h"
#include "I2C Platform.h"
#include "I2C Chip.h"
#include "I2C System Config.h"

/*
The chip database is used to add in what chips do specific to what action taken.
Add in chips that require a specific way of reading or writing data here.
*/

/*
Chips must follow this format for defining new chips:
I2C_<manufacture>_<type>_<chip>

Types are as followed:
IOE - I/O Extender
M - Multiplexer
AD - Analog to Digital
DA - Digital to Analog

Aditional types can be added but types above CANNOT be changed.

Chips also must follow the same define format for class format but appended with "_Chip" at the end.
They also MUST have a global variable defined using the chip define as it's variable name.
*/

#ifdef I2C_TI_IOE_TCA9534
class I2C_TI_IOE_TCA9534_Chip : I2C_Chip {
public:
	void init(int mode);
	int configuration();
	int read(int data);
	void write(int data);
};

I2C_TI_IOE_TCA9534_Chip I2C_TI_IOE_TCA9534;
#endif