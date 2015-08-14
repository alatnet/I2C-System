/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

#ifndef I2C_SYSTEM_H
#define I2C_SYSTEM_H

#include "I2C_Platform.h"
#include <map>
#include "I2C_Defines.h"
#include "I2C_Objects.h"
#include "I2C_System_Config.h"

class I2C_System {
public:
	static void init();
	static void destroy();
	
	//3d printer functions
	static void stepMotor(unsigned int motor, bool dir);
	static void turnMotorOn(unsigned int motor, bool dir);
	static void turnMotorOff(unsigned int motor, bool dir);
	static bool checkEndstop(unsigned int endstop) {}
	static int checkTemp(unsigned int temp) {}
	static void setHeater(unsigned int heater, int temp) {}
	static void setServo(unsigned int servo, unsigned int angle) {}

	//add functions
	static void addMotor(unsigned int motorNum, I2C_Motor* motor);
	static void addEndStop(unsigned int endstopNum, I2C_Object* endstop) {}
	static void addTemp(unsigned int tempNum, I2C_Object* temp) {}
	static void addHeader(unsigned int heaterNum, I2C_Object* heater) {}
	static void addServo(unsigned int servoNum, I2C_Object* servo) {}

  static unsigned int numMotors() { return I2C_System::motors->size(); }
private:
	static I2C_Object_Root* root;
	static std::map<unsigned int, I2C_Motor*>* motors;
	static std::map<unsigned int, I2C_Object*>* endstops;
	static std::map<unsigned int, I2C_Object*>* temps;
	static std::map<unsigned int, I2C_Object*>* heaters;
	static std::map<unsigned int, I2C_Object*>* servo;
};

#endif

