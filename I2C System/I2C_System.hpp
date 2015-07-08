#pragma once
#include "I2C_System_Header.hpp"
#include "I2C_System_Config.h"

class I2C_System {
public:
	static void init();
	static void stepMotor(unsigned int motor, bool dir);
};

