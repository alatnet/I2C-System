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

I2C_Motor::I2C_Motor(unsigned char address, I2C_Chip* chip, unsigned int ePin, unsigned int sPin, unsigned int dPin, unsigned int rPin) {
	this->address = address;
	this->chip = chip;

	//define the pins.
	if (ePin >= 0 && ePin <= 7) this->pins[0] |= 1 << ePin;	//0-7
	else if (ePin >= 8 && ePin <= 15) this->pins[1] |= 1 << ePin;	//8-15
	else if (ePin >= 16 && ePin <= 23) this->pins[2] |= 1 << ePin;	//16-23
	else if (ePin >= 24 && ePin <= 31) this->pins[3] |= 1 << ePin;	//24-31

	if (sPin >= 0 && sPin <= 7) this->pins[0] |= 1 << sPin;	//0-7
	else if (sPin >= 8 && sPin <= 15) this->pins[1] |= 1 << sPin;	//8-15
	else if (sPin >= 16 && sPin <= 23) this->pins[2] |= 1 << sPin;	//16-23
	else if (sPin >= 24 && sPin <= 31) this->pins[3] |= 1 << sPin;	//24-31

	if (dPin >= 0 && dPin <= 7) this->pins[0] |= 1 << dPin;	//0-7
	else if (dPin >= 8 && dPin <= 15) this->pins[1] |= 1 << dPin;	//8-15
	else if (dPin >= 16 && dPin <= 23) this->pins[2] |= 1 << dPin;	//16-23
	else if (dPin >= 24 && dPin <= 31) this->pins[3] |= 1 << dPin;	//24-31

	if (rPin >= 0 && rPin <= 7) this->pins[0] |= 1 << rPin;	//0-7
	else if (rPin >= 8 && rPin <= 15) this->pins[1] |= 1 << rPin;	//8-15
	else if (rPin >= 16 && rPin <= 23) this->pins[2] |= 1 << rPin;	//16-23
	else if (rPin >= 24 && rPin <= 31) this->pins[3] |= 1 << rPin;	//24-31
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
		//write the modified pin state to turn on motor
		this->chip->write(pins, 4, I2C_WRITE_POLARITY);
		//write modified pin state to turn off motor
		this->chip->write(pins, 4, I2C_WRITE_POLARITY);
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

