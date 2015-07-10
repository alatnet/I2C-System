/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/

#pragma once
#include "I2C Objects.hpp"

//DO NOT EDIT!!!
#define I2C_CONFIG_DECLARATION void setupI2C(I2C_Object_Root* root)
#define I2C_CONFIG_START \
	I2C_CONFIG_DECLARATION { \
	I2C_Object* currObj = NULL; \
	I2C_Multiplexer* currMultiplexer = NULL; \
	unsigned int currLane = 0; \
	std::vector<I2C_Multiplexer*> prevMultiplexer;

#define I2C_CONFIG_END }

//~~nodes~~
#define I2C_ROOT root
#define I2C_MULTIPLEXER currMultiplexer
//~~nodes End~~

//~~types~~~
//motors
#define I2C_X_MOTOR 0
#define I2C_Y_MOTOR 1
#define I2C_Z_MOTOR 2
#define I2C_E_MOTOR(x) 3+x

//endstops
#define I2C_X_ENDSTOP_MIN 0
#define I2C_X_ENDSTOP_MAX 1
#define I2C_Y_ENDSTOP_MIN 2
#define I2C_Y_ENDSTOP_MAX 3
#define I2C_Z_ENDSTOP_MIN 4
#define I2C_Z_ENDSTOP_MAX 5

//temp sensors
#define I2C_HEATBED_TEMP 0
#define I2C_EXTRUDER_TEMP(x) x+1

//heaters
#define I2C_HEATBED_HEATER 0
#define I2C_EXTRUDER_HEATER(x) x+1
//~~types end~~~

//~~Misc~~
#define I2C_MULTIPLEXER_LANE(lane) currLane = lane;

#define I2C_MOTOR_PIN_SELECT(x) \
	(x*4)+0, (x*4)+1, (x*4)+2, (x*4)+3

#define I2C_ADDRESS(a,b,c,d,e,f,g) a<<6 | b<<5 | c<<4 | d<<3 | e<<2 | f<<1 | g
//~~Misc end

//~~Config Entries~~
//TODO apparently this causes an "expeced an expression" error. this needs to be fixed...
#define I2C_MOTOR(node, type, address, ePin, sPin, dPin, rPin) \
	currObj = new I2C_Motor(address, ePin, sPin, dPin, rPin); \
	currObj->setParent(node); \
	node->addI2CObj(currObj,currLane); \
	currMotor = NULL;

//TODO add this into the code
#define I2C_ENDSTOP(node, type, address, pin)
#define I2C_TEMP_SENSOR(node, type, address, pin)
#define I2C_HEATER(node,address,pin)

#define I2C_MULTIPLEXER_START(node, address) \
	prevMultiplexer.push_back(currMultiplexer); \
	currMultiplexer = new I2C_Multiplexer(address); \
	currMultiplexer->setParent(node); \
	node->addI2CObj(currMultiplexer,currLane);

#define I2C_MULTIPLEXER_END \
	if (prevMultiplexer.size() != 0){ \
		currMultiplexer = prevMultiplexer.back(); \
		prevMultiplexer.pop_back(); \
	} else { \
		currMultiplexer = NULL; \
	}
//~~Config Entries End~~