/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

#ifndef I2C_CHIP_DATABASE_H
#define I2C_CHIP_DATABASE_H

#include "I2C_Platform.h"
#include "I2C_Defines.h"
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
IOE - I/O Extender - used for motors, endstops, servos, and possibly heating devices and fans
M - Multiplexer - used to attach more devices
AD - Analog to Digital - used for temperature sensors
DA - Digital to Analog - used for heating devices and fans (using a digital pot)

Aditional types can be added but types above CANNOT be changed.

Chips also must follow the same define format for class format but appended with "_Chip" at the end.
They also MUST have a global variable defined using the chip define as it's variable name.
*/

#ifdef I2C_TI_IOE_TCA9534
//ADDRESS: 0100XXX
	#undef I2C_TI_IOE_TCA9534
	#define I2C_TI_IOE_TCA9534 i2c_ti_ioe_tca9534
	#define I2C_TI_IOE_TCA9534_ADDRESS(a,b,c) I2C_ADDRESS(0,1,0,0,a,b,c)

	class I2C_TI_IOE_TCA9534_Chip : public I2C_Chip {
	public:
		void init(uint8_t address, int mode);
		unsigned int configuration(uint8_t address, uint8_t * data);
		unsigned int read(uint8_t address, uint8_t * data);
		void write(uint8_t address, uint8_t data, unsigned char type);
		void write(uint8_t address, uint8_t * data, unsigned int _size, unsigned char type);
		unsigned int getMaxSpeed() { return I2C_SPEED_FULL;  }
	};

	extern I2C_TI_IOE_TCA9534_Chip I2C_TI_IOE_TCA9534;
#endif

#endif


