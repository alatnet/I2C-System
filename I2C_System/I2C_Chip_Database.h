/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

#ifndef I2C_CHIP_DATABASE_H
#define I2C_CHIP_DATABASE_H

#include "I2C_Defines.h"
#include "I2C_Platform.h"
#include "I2C_Chip.h"
#include "I2C_System_Config.h"

/*
The chip database is used to add in what chips do specific to what action taken.
Add in chips that require a specific way of reading or writing data here.
*/

/*
Chips must follow this format for defining new chips:
I2C_<manufacture>_<type>_<chip>

Types are as followed:
IOE - I/O Extender - used for motors, endstops, servos, and possibly heating devices
M - Multiplexer - used to attach more devices
AD - Analog to Digital - used for temperature sensors
DA - Digital to Analog - used for heating devices (using a digital pot)

Aditional types can be added but types above CANNOT be changed.

Chips also must follow the same define format for class format but appended with "_Chip" at the end.
They also MUST have a global variable defined using the chip define as it's variable name.
*/

#ifdef I2C_TI_IOE_TCA9534
	#undef I2C_TI_IOE_TCA9534
	#define I2C_TI_IOE_TCA9534 i2c_ti_ioe_tca9534

	class I2C_TI_IOE_TCA9534_Chip : public I2C_Chip {
	public:
		void init(int mode);
		int configuration();
		int read(int data);
		void write(int data, unsigned char type);
	};

	extern I2C_TI_IOE_TCA9534_Chip I2C_TI_IOE_TCA9534;
#endif

#endif