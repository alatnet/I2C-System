/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#include "I2C_Chip_Database.h"

#ifdef I2C_TI_IOE_TCA9534
  I2C_TI_IOE_TCA9534_Chip I2C_TI_IOE_TCA9534;
  
	void I2C_TI_IOE_TCA9534_Chip::init(int mode) {
		I2C_WRITE(0x03);
		if (mode = I2C_MODE_INPUT) I2C_WRITE(0);
		else {
			I2C_WRITE(1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 3 | 1 << 2 | 1 << 1 | 1 << 0);
			//make sure the pins are off.
			I2C_WRITE(0x02);
			I2C_WRITE(0);
		}
	}

	int I2C_TI_IOE_TCA9534_Chip::configuration() {
		I2C_WRITE(0x03);
		return I2C_READ;
	}

	int I2C_TI_IOE_TCA9534_Chip::read(int data) {
		I2C_WRITE(0x00);
		return I2C_READ;
	}

	void I2C_TI_IOE_TCA9534_Chip::write(int data, unsigned char type) {
		if (type == I2C_WRITE_RAW) I2C_WRITE(0x01);
		else I2C_WRITE(0x02);
		I2C_WRITE(data);
	}

	void I2C_TI_IOE_TCA9534_Chip::write(unsigned char data[], unsigned int size, unsigned char type) {
		if (type == I2C_WRITE_RAW) I2C_WRITE(0x01);
		else I2C_WRITE(0x02);
		I2C_WRITE(data[0]);
	}
#endif

