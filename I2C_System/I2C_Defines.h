/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

#ifndef I2C_DEFINES_H
#define I2C_DEFINES_H

#include "I2C_Objects.h"
#include <vector>

//DO NOT EDIT!!!
#define I2C_CONFIG_DECLARATION_NAME setupI2C
#define I2C_CONFIG_DECLARATION void I2C_CONFIG_DECLARATION_NAME(I2C_Object_Root* root, std::map<unsigned int, I2C_Motor*>* motors)
#define I2C_CONFIG_START \
	I2C_CONFIG_DECLARATION { \
	I2C_Object* currObj; \
	I2C_Multiplexer* currMultiplexer; \
	unsigned int currLane; \
	std::vector<I2C_Multiplexer*> prevMultiplexer;

#define I2C_CONFIG_END }

#define I2C_MOTOR_COMMON(node,type) \
	currObj->setParent(node); \
	I2C_System::addMotor(type, (I2C_Motor*)currObj); \
	node->addI2CObj(currObj, currLane);

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

/*#define I2C_MOTOR_PIN_SELECT(x) \
	(x*4)+0, (x*4)+1, (x*4)+2, (x*4)+3*/

#define I2C_ADDRESS(a,b,c,d,e,f,g) a<<6 | b<<5 | c<<4 | d<<3 | e<<2 | f<<1 | g
//~~Misc end

//~~Config Entries~~
#define I2C_MOTOR(node, type, address, chip, ePin, sPin, dPin, rPin) \
	currObj = new I2C_Motor(address, &chip, ePin, sPin, dPin, rPin); \
	I2C_MOTOR_COMMON(node,type)

#define I2C_MOTOR(node, type, address, chip, pinSelect) \
	currObj = new I2C_Motor(address, &chip, (pinSelect*4)+0, (pinSelect*4)+1, (pinSelect*4)+2, (pinSelect*4)+3); \
	I2C_MOTOR_COMMON(node,type)

//TODO add this into the code
#define I2C_ENDSTOP(node, type, address, chip, pin)
#define I2C_TEMP_SENSOR(node, type, address, chip, pin)
#define I2C_HEATER(node, type, address, chip, pin)
#define I2C_SERVO(node, type, address, chip, pin)

#define I2C_MULTIPLEXER_START(node, address, chip) \
	prevMultiplexer.push_back(currMultiplexer); \
	currMultiplexer = new I2C_Multiplexer(address, *chip); \
	currMultiplexer->setParent(node); \
	node->addI2CObj(currMultiplexer, currLane);

#define I2C_MULTIPLEXER_END \
	if (prevMultiplexer.size() != 0){ \
		currMultiplexer = prevMultiplexer.back(); \
		prevMultiplexer.pop_back(); \
	} else currMultiplexer = NULL;
//~~Config Entries End~~

#endif