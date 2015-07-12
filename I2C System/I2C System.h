/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once
#include "I2C System Header.h"
#include "I2C Platform.h"
#include "I2C Defines.h"
#include "I2C Objects.h"
#include "I2C System Config.h"

class I2C_System {
public:
	static void init();
	static void destroy();
	static void stepMotor(unsigned int motor, bool dir);
private:
	static I2C_Object_Root* root;
};

