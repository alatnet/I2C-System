/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#include "I2C_System.h"

void I2C_System::init() {
	//start up the i2c system
	I2C_INIT;

	//create the root node for the i2c system
	I2C_System::root = new I2C_Object_Root();
	I2C_System::motors = new std::map<unsigned int, I2C_Motor*>();

	//read configuration and add all i2c devices to root node
	I2C_CONFIG_DECLARATION_NAME(I2C_System::root, I2C_System::motors);

	if (I2C_System::motors->empty()) delete I2C_System::motors; //no motors so free up space;

	//Initialize all the objects!
	I2C_System::root->init();
}

void I2C_System::destroy() {
	I2C_System::root->destroy();

	delete I2C_System::root;
	if (!I2C_System::motors->empty()) delete I2C_System::motors;

	I2C_DESTROY;
}

void I2C_System::stepMotor(unsigned int motor, bool dir) {
	std::map<unsigned int, I2C_Motor*>::const_iterator it = I2C_System::motors->find(motor);
	if (it == I2C_System::motors->end()) return;
	it->second->step(dir);
}

void I2C_System::addMotor(unsigned int motorNum, I2C_Motor* motor) {
	std::map<unsigned int, I2C_Motor*>::const_iterator it = I2C_System::motors->find(motorNum); //if the motor hasnt been assigned.
	if (it == I2C_System::motors->end()) I2C_System::motors->insert(std::pair<unsigned int, I2C_Motor*>(motorNum,motor)); //assign the motor.
}