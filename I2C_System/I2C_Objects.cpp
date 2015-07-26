/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#include "I2C_Objects.h"

void I2C_Object_Root::init() {
	for (std::map<unsigned char, I2C_Object*>::iterator iterator = this->objs.begin(); iterator != this->objs.end(); iterator++) iterator->second->init();
}

void I2C_Object_Root::destroy() {
	std::map<unsigned char, I2C_Object*>::iterator iterator;
	while (!this->objs.empty()) {
		iterator = this->objs.end();
		iterator--;
		iterator->second->destroy();
		delete iterator->second;
		this->objs.erase(iterator);
	}
}

void I2C_Motor::init() {
	this->parent->referToParent(this);

	I2C_BEGIN(this->address);
		//set motor chip to be output
		this->chip->init(I2C_MODE_OUTPUT);
	I2C_END;
}

void I2C_Motor::step(bool dir) {
	this->parent->referToParent(this);

	I2C_BEGIN(this->address);
		//read the current pin states
		//unsigned int state = this->chip->read(0);
		unsigned int state = 1 << this->ePin | dir << this->dPin | 1 << this->sPin | 1 << this->rPin;

		//state &= 0 << I2C_Motors[motor].ePin | 0 << I2C_Motors[motor].dPin | 0 << I2C_Motors[motor].sPin;

		//write the modified pin state to turn on motor
		//state |= 1 << this->ePin | dir << this->dPin | 1 << this->sPin | 0 << this->rPin;
		this->chip->write(state, I2C_WRITE_POLARITY);

		//write modified pin state to turn off motor
		//state |= 0 << this->ePin | dir << this->dPin | 0 << this->sPin | 0 << this->rPin;
		this->chip->write(state, I2C_WRITE_POLARITY);
	I2C_END;
}

void I2C_Multiplexer::init() {
	this->parent->referToParent(this);

	this->chip->init(I2C_MODE_OUTPUT);

	for (std::map<I2C_Object*, unsigned int>::iterator iterator = this->objs.begin(); iterator != this->objs.end(); iterator++) {

		I2C_BEGIN(this->address);
			//switch to the correct lane
			this->chip->write(iterator->second, I2C_WRITE_RAW);
		I2C_END;

		iterator->first->init();
	}
}

void I2C_Multiplexer::destroy() {
	std::map<I2C_Object*, unsigned int>::iterator iterator;
	while (!this->objs.empty()) {
		iterator = this->objs.end();
		iterator--;
		iterator->first->destroy();
		delete iterator->first;
		this->objs.erase(iterator);
	}
}

void I2C_Multiplexer::referToParent(I2C_Object* obj) {
	this->parent->referToParent(this);

	//check to see if the address exists in our hash table
	std::map<I2C_Object*, unsigned int>::const_iterator it = objs.find(obj);
	if (it == objs.end()) return;

	I2C_BEGIN(this->address);
		//switch to the correct lane
		this->chip->write(it->second, I2C_WRITE_RAW);
	I2C_END;
}