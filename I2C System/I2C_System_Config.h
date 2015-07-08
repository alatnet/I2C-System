#include "I2C_System_Structs.hpp"

//define the addresses that are motor chips
I2C_MOTOR_CHIPS(2)
	0,
	1
I2C_MOTOR_CHIPS_END

//set motors
I2C_NUM_MOTORS(4)
	{ 0, I2C_MOTOR_PIN_SELECT(0) }, //X Motor
	{ 0, I2C_MOTOR_PIN_SELECT(1) }, //Y Motor
	{ 1, I2C_MOTOR_PIN_SELECT(0) }, //Z Motor
	{ 1, I2C_MOTOR_PIN_SELECT(1) }  //E0 Motor
//	{ address, pins}
//	{ address, ePin, sPin, dPin, rPin }
I2C_NUM_MOTORS_END