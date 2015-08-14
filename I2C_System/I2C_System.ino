#define ALT_ARDUINI_I2C
#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>

/*#ifndef ALT_ARDUINO_I2C
  #include <Wire.h>
#else*/
  #include "I2C.h"
//#endif

#include "I2C_Sys.h"

uint8_t datapass[1];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  I2C_System::init();
  I2C_SCAN

  Serial.print("Num Motors: ");
  Serial.println(I2C_System::numMotors());
  
  //datapass[0] = 0;
  //I2C_WRITE(I2C_TI_IOE_TCA9534_ADDRESS(1, 1, 1), 0x03, datapass, 1)
  
  //datapass[0] = 0xff;
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.println("TEST");
  //I2C_System::stepMotor(I2C_X_MOTOR,0);
  I2C_System::turnMotorOn(I2C_X_MOTOR,0);
  delay(100);
  I2C_System::turnMotorOff(I2C_X_MOTOR,0);

  //I2C_WRITE(I2C_TI_IOE_TCA9534_ADDRESS(1, 1, 1), 0x02, datapass, 1)
  //delay(500);
  //I2C_WRITE(I2C_TI_IOE_TCA9534_ADDRESS(1, 1, 1), 0x02, datapass, 1)
}


