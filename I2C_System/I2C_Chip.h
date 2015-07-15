/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

#ifndef I2C_CHIP_H
#define I2C_CHIP_H

//abstract base class
class I2C_Chip {
public:
	virtual void init(int mode) = 0;
	virtual int configuration() = 0;
	virtual int read(int data) = 0;
	virtual void write(int data) = 0;
};

#endif