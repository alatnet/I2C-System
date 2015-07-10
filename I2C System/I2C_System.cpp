/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#include "I2C_System.hpp"

void I2C_System::init() {
	//start up the i2c system
	Wire.begin();

	//create the root node for the i2c system
	I2C_System::root = new I2C_Object_Root();

	//read configuration and add all i2c devices to root node
	setupI2C(I2C_System::root);
	
	//Initialize all the objects!
	I2C_System::root->init();
}

void I2C_System::stepMotor(unsigned int motor, bool dir) {
}