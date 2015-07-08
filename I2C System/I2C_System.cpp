#include "I2C_System.hpp"

void I2C_System::init() {
	Wire.begin();

	//set motor chips to output
	for (unsigned int i = 0; i < I2C_MOTOR_CHIP_COUNT; i++) {
		Wire.beginTransmission(I2C_Motor_Chips[i]);
			//set motor chip to be output
			Wire.write(0x03);
			Wire.write(0);
		Wire.endTransmission();
	}
}

void I2C_System::stepMotor(unsigned int motor, bool dir) {
	Wire.beginTransmission(I2C_Motors[motor].address);
		//read the current pin states
		Wire.write(0x01);
		unsigned int state = Wire.read();
		state | 0 << I2C_Motors[motor].ePin | 0 << I2C_Motors[motor].dPin | 0 << I2C_Motors[motor].sPin;

		//write the modified pin state to turn on motor
		state | 1 << I2C_Motors[motor].ePin | dir << I2C_Motors[motor].dPin | 1 << I2C_Motors[motor].sPin;
		Wire.write(0x01);
		Wire.write(state);

		//write modified pin state to turn off motor
		state | 0 << I2C_Motors[motor].ePin | dir << I2C_Motors[motor].dPin | 0 << I2C_Motors[motor].sPin;
		Wire.write(0x01);
		Wire.write(state);
	Wire.endTransmission();
}