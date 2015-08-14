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
	this->dPin = dPin;

	if (rPin >= 0 && rPin <= 7) this->pins[0] |= 1 << rPin;	//0-7
	else if (rPin >= 8 && rPin <= 15) this->pins[1] |= 1 << rPin;	//8-15
	else if (rPin >= 16 && rPin <= 23) this->pins[2] |= 1 << rPin;	//16-23
	else if (rPin >= 24 && rPin <= 31) this->pins[3] |= 1 << rPin;	//24-31
}

void I2C_Motor::init() {
	this->parent->referToParent(this);
	//set motor chip to be output
	this->chip->init(this->address,I2C_MODE_OUTPUT);
}

void I2C_Motor::step(bool dir) {
	this->parent->referToParent(this);

	uint8_t data[4], otherPins[4], outputPins[4];
	this->chip->read(this->address,data); //read which pins are on and off.

	//make sure that the dir pin is being either enabled or disabled.
	if (this->dPin >= 0 && this->dPin <= 7) this->pins[0] &= ((dir << this->dPin)&0xff); //0-7
	else if (this->dPin >= 8 && this->dPin <= 15) this->pins[1] &= ((dir << this->dPin)&0xff); //8-15
	else if (this->dPin >= 16 && this->dPin <= 23) this->pins[2] &= ((dir << this->dPin)&0xff);  //16-23
	else if (this->dPin >= 24 && this->dPin <= 31) this->pins[3] &= ((dir << this->dPin)&0xff);  //24-31

	//configure to set ONLY the pins we want on and off.
	for(int i=0;i<4;i++){
		otherPins[i] = data[i] & ~pins[i];
		outputPins[i] = otherPins[i] | pins[i];
	}
  
	this->chip->write(this->address,outputPins,4,I2C_WRITE_RAW);
	//delay(_delay);
	this->chip->write(this->address,otherPins,4,I2C_WRITE_RAW);
}

void I2C_Motor::turnOn(bool dir){
	this->parent->referToParent(this);

	uint8_t data[4], otherPins[4], outputPins[4];
	this->chip->read(this->address,data); //read which pins are on and off.

	//make sure that the dir pin is being either enabled or disabled.
	if (this->dPin >= 0 && this->dPin <= 7) this->pins[0] &= ((dir << this->dPin)&0xff); //0-7
	else if (this->dPin >= 8 && this->dPin <= 15) this->pins[1] &= ((dir << this->dPin)&0xff); //8-15
	else if (this->dPin >= 16 && this->dPin <= 23) this->pins[2] &= ((dir << this->dPin)&0xff);  //16-23
	else if (this->dPin >= 24 && this->dPin <= 31) this->pins[3] &= ((dir << this->dPin)&0xff);  //24-31

	//configure to set ONLY the pins we want on.
	for(int i=0;i<4;i++){
		otherPins[i] = data[i] & ~pins[i];
		outputPins[i] = otherPins[i] | pins[i];
	}
  
	this->chip->write(this->address,outputPins,4,I2C_WRITE_RAW);
}

void I2C_Motor::turnOff(bool dir){
	this->parent->referToParent(this);

	uint8_t data[4], otherPins[4];
	this->chip->read(this->address,data); //read which pins are on and off.

	//make sure that the dir pin is being either enabled or disabled.
	if (this->dPin >= 0 && this->dPin <= 7) this->pins[0] &= ((dir << this->dPin)&0xff); //0-7
	else if (this->dPin >= 8 && this->dPin <= 15) this->pins[1] &= ((dir << this->dPin)&0xff); //8-15
	else if (this->dPin >= 16 && this->dPin <= 23) this->pins[2] &= ((dir << this->dPin)&0xff);  //16-23
	else if (this->dPin >= 24 && this->dPin <= 31) this->pins[3] &= ((dir << this->dPin)&0xff);  //24-31

	//configure to set ONLY the pins we want off.
	for(int i=0;i<4;i++) otherPins[i] = data[i] & ~pins[i];
  
	this->chip->write(this->address,otherPins,4,I2C_WRITE_RAW);
}

void I2C_Multiplexer::init() {
	this->parent->referToParent(this);

	this->chip->init(this->address, I2C_MODE_OUTPUT);

	for (std::map<I2C_Object*, unsigned int>::iterator iterator = this->objs.begin(); iterator != this->objs.end(); iterator++) {
		//switch to the correct lane
		this->chip->write(this->address, iterator->second, I2C_WRITE_RAW);
		
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

	//switch to the correct lane
	this->chip->write(this->address, it->second, I2C_WRITE_RAW);
}


