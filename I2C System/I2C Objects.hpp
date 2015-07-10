/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once
#include "I2C_System_Header.hpp"

//abstract base class
class I2C_Object {
public:
	virtual void referToParent(unsigned char address) = 0;
	virtual void setParent(I2C_Object* p) = 0;
	virtual void addI2CObj(I2C_Object* obj, unsigned int i) = 0;
	virtual void init() = 0;
	virtual unsigned char getAddress() = 0;
};

class I2C_Object_Root : public I2C_Object {
public:
	void referToParent(unsigned char address) {};
	void setParent(I2C_Object* p) {};
	void addI2CObj(I2C_Object* obj, unsigned int i) { objs.push_back(obj); }
	void init();
	unsigned char getAddress() { return 128; } //root address is 128 since the max number of addresses are from 0 to 127.
private:
	std::vector<I2C_Object*> objs; //hash table it
};

class I2C_Motor : public I2C_Object {
public:
	I2C_Motor(unsigned char address, unsigned int ePin, unsigned int sPin, unsigned int dPin, unsigned int rPin) : address(address), ePin(ePin), sPin(sPin), dPin(dPin), rPin(rPin) {}
	void step(bool dir); //refer to parent then step motor.
	void referToParent(unsigned char address) {} //do nothing, we are the lowest device
	void setParent(I2C_Object* p) { this->parent = p; }
	void addI2CObj(I2C_Object* obj, unsigned int i) {} //dont need it
	void init();
	unsigned char getAddress() { return this->address; }
private:
	I2C_Object* parent;
	unsigned char address;
	unsigned int ePin, sPin, dPin, rPin;
};

struct I2C_Multiplex_Node {
	I2C_Object* obj;
	unsigned int lane;
};

class I2C_Multiplexer : public I2C_Object {
public:
	I2C_Multiplexer(unsigned char address) : address(address) {}
	void addI2CObj(I2C_Object* obj, unsigned int lane);
	void referToParent(unsigned char address); //refer to parent then switch to the right lane
	void setParent(I2C_Object* p) { this->parent = p; }
	void init();
	unsigned char getAddress() { return this->address; }
private:
	unsigned char address;
	I2C_Object* parent;
	std::vector<I2C_Multiplex_Node> objs; //hash table it
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