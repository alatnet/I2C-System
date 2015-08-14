/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

#ifndef I2C_OBJECTS_H
#define I2C_OBJECTS_H

#include "I2C_Platform.h"
#include <map>
#include "I2C_Defines.h"
#include "I2C_Chip.h"

//abstract base class
class I2C_Object {
public:
	virtual void referToParent(I2C_Object* obj) = 0;
	virtual void setParent(I2C_Object* p) = 0;
	virtual void addI2CObj(I2C_Object* obj, unsigned int i) = 0;
	virtual void init() = 0;
	virtual void destroy() = 0;
	virtual unsigned char getAddress() = 0;
};

class I2C_Object_Root : public I2C_Object {
public:
	void referToParent(I2C_Object* obj) {};
	void setParent(I2C_Object* p) {};
	void addI2CObj(I2C_Object* obj, unsigned int i) { objs[obj->getAddress()] = obj; }
	void init();
	void destroy();
	unsigned char getAddress() { return 128; } //root address is 128 since the max number of addresses are from 0 to 127.
private:
	//std::vector<I2C_Object*> objs; //hash table it
	std::map<unsigned char, I2C_Object*> objs; //have it as unsigned char as the max devices allowed are from 0 to 127.  save space by having it as unsigned char which is from 0 to 255.
};

class I2C_Motor : public I2C_Object {
public:
	I2C_Motor(unsigned char address, I2C_Chip* chip, unsigned int ePin, unsigned int sPin, unsigned int dPin, unsigned int rPin);
	void step(bool dir); //refer to parent then step motor.
	void turnOn(bool dir);
	void turnOff(bool dir);
  void reset(bool on) { this->_reset = on; }
	void referToParent(I2C_Object* obj) {} //do nothing, we are the lowest device
	void setParent(I2C_Object* p) { this->parent = p; }
	void addI2CObj(I2C_Object* obj, unsigned int i) {} //dont need it
	void init();
	void destroy() {}
	unsigned char getAddress() { return this->address; }
private:
	unsigned char address, pins[4];
	I2C_Chip* chip;
	I2C_Object* parent;
	//unsigned char address;
  unsigned int dPin,rPin;
  bool _reset;

  void setDpin(bool dir);
  void setRpin(bool on);
};

class I2C_Multiplexer : public I2C_Object {
public:
	I2C_Multiplexer(unsigned char address, I2C_Chip* chip) : address(address), chip(chip) {}
	void addI2CObj(I2C_Object* obj, unsigned int lane) { objs[obj] = lane; }
	void referToParent(I2C_Object* obj); //refer to parent then switch to the right lane
	void setParent(I2C_Object* p) { this->parent = p; }
	void init();
	void destroy();
	unsigned char getAddress() { return this->address; }
private:
	I2C_Chip* chip;
	unsigned char address;
	I2C_Object* parent;
	std::map<I2C_Object*, unsigned int> objs;
};

/*
Theory, since there will be multiple devices and possibly multiplexers, this system will ensure that the correct device being controlled is switched to the correct lanes in the multiplexer.

Example:
R
+M1
|+D1
+D2

D2 is directly connected to master I2C so it doesnt refer to any parent for lane switching.
D1 is connected to a multiplexer so it needs to request to the multiplexer to change to the correct lane before doing any I2C action.
M1 is a multiplexer that recieves lane change requests via "referToParent" function.
*/

/*
Notes.
Using an unsigned char data type for i2c addresses ensures that we are using the least amount of space we can since an unsigned char is 0 to 255 and i2c addresses range from 0 to 127.
*/

#endif


