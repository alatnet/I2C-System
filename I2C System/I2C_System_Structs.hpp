struct I2C_SYSTEM_MOTOR {
	unsigned short address;
	unsigned int ePin, sPin, dPin, rPin;
};

#define I2C_X_MOTOR 0
#define I2C_Y_MOTOR 1
#define I2C_Z_MOTOR 2
#define I2C_E_MOTOR(x) 3+x

#define I2C_NUM_MOTORS(x) \
	unsigned const int I2C_MOTOR_COUNT = x; \
	const I2C_SYSTEM_MOTOR I2C_Motors[x] = {

#define I2C_NUM_MOTORS_END };

#define I2C_MOTOR_PIN_SELECT(x) \
	0+(x*4), 1+(x*4), 2+(x*4), 3+(x*4)


#define I2C_MOTOR_CHIPS(x) \
	unsigned const int I2C_MOTOR_CHIP_COUNT = x; \
	unsigned const short I2C_Motor_Chips[x] = {

#define I2C_MOTOR_CHIPS_END };