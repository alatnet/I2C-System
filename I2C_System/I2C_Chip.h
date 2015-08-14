/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

#ifndef I2C_CHIP_H
#define I2C_CHIP_H

#define I2C_WRITE_RAW 0
#define I2C_WRITE_POLARITY 1

#define I2C_MODE_INPUT 0
#define I2C_MODE_OUTPUT 1

//abstract base class
class I2C_Chip {
public:
	virtual void init(uint8_t address, int mode) = 0;
	virtual unsigned int configuration(uint8_t address, uint8_t * data) = 0;
	virtual unsigned int read(uint8_t address, uint8_t * data) = 0;
	virtual void write(uint8_t address, uint8_t data, unsigned char type) = 0;
	virtual void write(uint8_t address, uint8_t * data, unsigned int _size, unsigned char type) = 0;
	virtual unsigned int getMaxSpeed() = 0;
};

#endif


