/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

#ifndef I2C_PLATFORM_H
#define I2C_PLATFORM_H

#define I2C_SPEED_STANDARD 100  //100kbps
#define I2C_SPEED_FULL 400  //400kbps
#define I2C_SPEED_FAST 1000 //1mbps
#define I2C_SPEED_HIGH 3200 //3.2mbps

//edit this file to add in new i2c platforms

//make sure we are compiling for arduino
#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
	#define ARDUINO_I2C
#endif

//define common functions for I2C
//use this to make I2C System cross platform
#ifdef ARDUINO_I2C //arduino i2c platform
	#define I2C_SPEED_LIMIT I2C_SPEED_FULL
	#include <StandardCplusplus.h>
	#include <system_configuration.h>
	#include <unwind-cxx.h>
	#include <utility.h>

	/*#ifndef ALT_ARDUINO_I2C
		#include <Wire.h>
		#define I2C_INIT Wire.begin();
		#define I2C_DESTROY
		#define I2C_WRITE(address, reg, data, numbytes) \
			Wire.beginTransmission(address); \
			Wire.write(reg); \
			Wire.endTransmission(); \
			Wire.beginTransmission(address); \
			if (numbytes==1) Wire.write(data[0]); \
			else for (unsigned int i=0;i<numbytes;i++) Wire.write(data[i]); \
			Wire.endTransmission();
		#define I2C_READ(address, reg, numbytes, data) \
			Wire.beginTransmission(address); \
			Wire.write(reg); \
			Wire.endTransmission(); \
			Wire.requestFrom(address,numbytes); \
			unsigned int currBytes; \
			while(Wire.available() && currBytes < numbytes){ \
				data[currBytes] = Wire.read(); \
				currBytes++; \
			} \
			while (Wire.available()){}
		#define I2C_SCAN

		//defines used in configuration
		#define I2C_SET_SPEED(spd)
		#define I2C_TIMEOUT(_time)
		#define I2C_PULLUP(pull)
	#else*/
		#include "I2C.h"
		#define I2C_INIT I2c.begin();
		#define I2C_DESTROY I2c.end();
		#define I2C_WRITE(address, reg, data, numbytes) I2c.write(address, reg, data, numbytes);
		#define I2C_READ(address, reg, numbytes, data) I2c.read(address, reg, numbytes, data);
		#define I2C_SCAN I2c.scan();

		//defines used in configuration
		#define I2C_SET_SPEED(spd) \
			if (spd == I2C_SPEED_STANDARD) I2c.setSpeed(0); \
			else if (spd == I2C_SPEED_FULL) I2c.setSpeed(1); \
			else if (spd == I2C_SPEED_FAST) I2c.setSpeed(1); \
			else if (spd == I2C_SPEED_HIGH) I2c.setSpeed(1);
		#define I2C_TIMEOUT(_time) I2c.timeOut(_time);
		#define I2C_PULLUP(pull) I2c.pullup(pull);
	//#endif
#else
	#define I2C_INIT
	#define I2C_DESTROY
	#define I2C_WRITE(address, reg, data, numbytes)
	#define I2C_READ(address,reg,numbytes,data)
	#define I2C_SCAN

	//defines used in configuration
	#define I2C_SET_SPEED(spd)
	#define I2C_TIMEOUT(_time)
	#define I2C_PULLUP(pull)
#endif

#endif


