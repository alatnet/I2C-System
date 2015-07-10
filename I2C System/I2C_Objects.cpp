/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#include "I2C Objects.hpp"

void I2C_Object_Root::init() {
	for (int i = 0; i < this->objs.size(); i++) this->objs.at(i)->init();
}

void I2C_Motor::init() {
	Wire.beginTransmission(this->address);
	//set motor chip to be output
		Wire.write(0x03);
		Wire.write(0);
	Wire.endTransmission();
}

//TODO fix this thing to ONLY change the pins on this motor.
void I2C_Motor::step(bool dir) {
	this->parent->referToParent(this->address);

	Wire.beginTransmission(this->address);
		//read the current pin states
		Wire.write(0x00);
		unsigned int state = Wire.read();
		//state &= 0 << I2C_Motors[motor].ePin | 0 << I2C_Motors[motor].dPin | 0 << I2C_Motors[motor].sPin;

		//write the modified pin state to turn on motor
		state |= 1 << this->ePin | dir << this->dPin | 1 << this->sPin | 0 << this->rPin;
		Wire.write(0x01);
		Wire.write(state);

		//write modified pin state to turn off motor
		state |= 0 << this->ePin | dir << this->dPin | 0 << this->sPin | 0 << this->rPin;
		Wire.write(0x01);
		Wire.write(state);
	Wire.endTransmission();
}

void I2C_Multiplexer::init() {
	I2C_Object* obj = NULL;
	for (int i = 0; i < this->objs.size(); i++) {
		I2C_Multiplex_Node n = this->objs.at(i);

		Wire.beginTransmission(this->address);
			//switch to the correct lane
		Wire.endTransmission();

		n.obj->init();
	}
}

void I2C_Multiplexer::addI2CObj(I2C_Object* obj, unsigned int lane) {
	I2C_Multiplex_Node n;
	n.obj = obj;
	n.lane = lane;
	objs.push_back(n);
}

void I2C_Multiplexer::referToParent(unsigned char address) {
	this->parent->referToParent(this->address);

	//find which lane the adddress is on

	Wire.beginTransmission(this->address);
		//switch to the correct lane
	Wire.endTransmission();
}