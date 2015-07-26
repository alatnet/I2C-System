/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

#ifndef I2C_SYSTEM_H
#define I2C_SYSTEM_H

#include <map>
#include "I2C_Platform.h"
#include "I2C_Defines.h"
#include "I2C_Objects.h"
#include "I2C_System_Config.h"

class I2C_System {
public:
	static void init();
	static void destroy();
	static void stepMotor(unsigned int motor, bool dir);
	static void addMotor(unsigned int motorNum, I2C_Motor* motor);
private:
	static I2C_Object_Root* root;
	static std::map<unsigned int, I2C_Motor*>* motors;
	static std::map<unsigned int, I2C_Object*>* endstops;
	static std::map<unsigned int, I2C_Object*>* temps;
	static std::map<unsigned int, I2C_Object*>* heaters;
};

#endif