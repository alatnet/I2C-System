/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#include "I2C_Chip_Database.h"

#ifdef I2C_TI_IOE_TCA9534
	I2C_TI_IOE_TCA9534_Chip I2C_TI_IOE_TCA9534;
  
	void I2C_TI_IOE_TCA9534_Chip::init(uint8_t address, int mode) {
		uint8_t datapass[1];
		if (mode = I2C_MODE_INPUT) {
			datapass[0] =  1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 3 | 1 << 2 | 1 << 1 | 1 << 0;
			I2C_WRITE(address, 0x03, datapass, 1)
		} else {
			datapass[0] = 0;
			I2C_WRITE(address, 0x03, datapass, 1)
			//make sure the pins are off.
			datapass[0] = 0;
			I2C_WRITE(address, 0x01, datapass,1)
		}
	}

	unsigned int I2C_TI_IOE_TCA9534_Chip::configuration(uint8_t address, uint8_t * data) {
		I2C_READ(address,0x03,1,data)
		return 1;
	}

	unsigned int I2C_TI_IOE_TCA9534_Chip::read(uint8_t address, uint8_t * data) {
		I2C_READ(address,0x00,1,data)
		return 1;
	}

	void I2C_TI_IOE_TCA9534_Chip::write(uint8_t address, uint8_t data, unsigned char type) {
		uint8_t datapass[1];
		datapass[0] = data;
		if (type == I2C_WRITE_RAW) {
			I2C_WRITE(address, 0x01, datapass, 1)
		} else {
			I2C_WRITE(address, 0x02, datapass, 1)
		}
	}

	void I2C_TI_IOE_TCA9534_Chip::write(uint8_t address, uint8_t * data, unsigned int _size, unsigned char type) {
		uint8_t datapass[1];
		datapass[0] = data[0];
		if (type == I2C_WRITE_RAW) {
			I2C_WRITE(address, 0x01, datapass, 1)
		} else {
			I2C_WRITE(address, 0x02, datapass, 1)
		}
	}
#endif


