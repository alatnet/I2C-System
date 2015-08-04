#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>

#include <Wire.h>

#include "I2C_Sys.h"

void setup() {
  // put your setup code here, to run once:
  I2C_System::init();
}

void loop() {
  // put your main code here, to run repeatedly:
  I2C_System::stepMotor(I2C_X_MOTOR,0);
}

