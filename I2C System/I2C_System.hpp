/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once
#include "I2C_System_Header.hpp"
#include "I2C_System_Config.h"
#include "I2C Objects.hpp"
#include "I2C_Defines.hpp"

class I2C_System {
public:
	static void init();
	static void stepMotor(unsigned int motor, bool dir);
private:
	static I2C_Object_Root* root;
};

