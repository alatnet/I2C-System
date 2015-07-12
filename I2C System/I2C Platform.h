/*
Created by Alexander Karl Moldenhauer, July 9 2015.
*/
#pragma once

//edit this file to add in new i2c platforms

//make sure we are compiling for arduino
#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
#define ARDUINO_I2C
#endif

//define common functions for I2C
//use this to make I2C System cross platform
#ifdef ARDUINO_I2C //arduino i2c platform
#define I2C_INIT Wire.begin()
#define I2C_DESTROY
#define I2C_BEGIN(address) Wire.beginTransmission(address)
#define I2C_END Wire.endTransmission()
#define I2C_WRITE(data) Wire.write(data)
#define I2C_READ Wire.read()
#else
#define I2C_INIT
#define I2C_DESTROY
#define I2C_BEGIN(address)
#define I2C_END
#define I2C_WRITE(data)
#define I2C_READ NULL
#endif