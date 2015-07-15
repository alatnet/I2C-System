/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#include "I2C_Objects.h"

void I2C_Object_Root::init() {
	for (int i = 0; i < this->objs.size(); i++) this->objs.at(i)->init();
}

void I2C_Object_Root::destroy() {
	while (this->objs.size() != 0) {
		I2C_Object *obj  = this->objs.back();
		this->objs.pop_back();
		obj->destroy();
		delete obj;
	}
}

void I2C_Motor::init() {
	this->parent->referToParent(this->address);

	I2C_BEGIN(this->address);
		//set motor chip to be output
		this->chip->init(0);
	I2C_END;
}

//TODO fix this thing to ONLY change the pins on this motor.
void I2C_Motor::step(bool dir) {
	this->parent->referToParent(this->address);

	I2C_BEGIN(this->address);
		//read the current pin states
		unsigned int state = this->chip->read(0);

		//state &= 0 << I2C_Motors[motor].ePin | 0 << I2C_Motors[motor].dPin | 0 << I2C_Motors[motor].sPin;

		//write the modified pin state to turn on motor
		//state |= 1 << this->ePin | dir << this->dPin | 1 << this->sPin | 0 << this->rPin;
		this->chip->write(state);

		//write modified pin state to turn off motor
		state |= 0 << this->ePin | dir << this->dPin | 0 << this->sPin | 0 << this->rPin;
		this->chip->write(state);
	I2C_END;
}

void I2C_Multiplexer::init() {
	this->parent->referToParent(this->address);

	this->chip->init(0);

	for (int i = 0; i < this->objs.size(); i++) {
		I2C_Multiplex_Node n = this->objs.at(i);

		I2C_BEGIN(this->address);
			//switch to the correct lane
			this->chip->write(n.lane);
		I2C_END;

		n.obj->init();
	}
}

void I2C_Multiplexer::destroy() {
	while (this->objs.size() != 0) {
		I2C_Multiplex_Node n = this->objs.back();
		this->objs.pop_back();
		n.obj->destroy();
		delete n.obj;
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
	I2C_Multiplex_Node n;

	I2C_BEGIN(this->address);
		//switch to the correct lane
		this->chip->write(n.lane);
	I2C_END;
}