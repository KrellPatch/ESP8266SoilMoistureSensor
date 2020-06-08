/*
 * ESP8266SoilMoistureSensor.cpp
 *
 *  Created on: 5 jun. 2020
 *      Author: mark
 */

#include "ESP8266SoilMoistureSensor.h"

ESP8266SoilMoistureSensor::ESP8266SoilMoistureSensor(uint8_t readPin, uint8_t powerPin) :
	_readPin {readPin},
	_powerPin {powerPin}
	_samples {10},
	_continuous {false},
	_minCalibration {5},
	_maxCalibration {650}, // Default value for 3.3V VCC, may be higher when using 5V
	_measurePercentage {false}
{}

ESP8266SoilMoistureSensor::ESP8266SoilMoistureSensor(uint8_t readPin) :
	ESP8266SoilMoistureSensor {readPin, 0}
{}

ESP8266SoilMoistureSensor::ESP8266SoilMoistureSensor() :
	ESM8266SoilMoistureSensor {0, 0}
{}

ESP8266SoilMoistureSensor::~ESP8266SoilMoistureSensor() {}

// Get a measurement from the sensor. Values are 0 to 200 CB
// where 0 is WET and 200 is extremely dry
int ESP8266SoilMoistureSensor::read() {
	int value = 0;

	// ToDo: Rethink the logic of continuous and powerPin

	// If not continuous, set powerPin high
	if(!_continuous && _powerPin) digitalWrite(_powerPin, HIGH);
	// measurements
	for(int i = 0; i < _samples; ++i) {
		value += analogRead(_readPin);
		// ToDO: need delay here?
	}
	// reset powerpin if required
	if(!_continuous && _powerPin) digitalWrite(_powerPin, LOW);

	// Take average reading and remap to CB value (wet-dry, 0-200)
	value /= _samples;

	if(_measurePercentage) {
		value = map(value, _minCalibration, _maxCalibration, 0, 100)
	} else {
		value = map(value, _maxCalibration, _minCalibration, 0, 200);
	}

	return value;
} // read()

// Setters and Getters

// Sate the number of samples taken to get a good reading. Default 10.
void 		ESP8266SoilMoistureSensor::setSamples(int samples) 								{ _samples = samples; }
int			ESP8266SoilMoistureSensor::samples() 															{ return _samples; }

// Read pin and power (VCC) pin numbers. Read pin should be Analog Read capable
// Power pin switches power to the sensors VCC input and is switched off after reading to save
// sensor lifetime. On=Off switching is controlled through the continuous() function. Set to false
// power is always on.
void 		ESP8266SoilMoistureSensor::setReadPin(uint8_t readPin) 						{	_readPin = readPin; }
uint8_t ESP8266SoilMoistureSensor::readPin() 															{ return _readPin; }
void 		ESP8266SoilMoistureSensor::setPowerPin(uint8_t powerPin) 					{ _powerPin = powerPin; }
uint8_t	ESP8266SoilMoistureSensor::powerPin() 														{ return _powerPin; }
void 		ESP8266SoilMoistureSensor::setContinuous(bool continuous) 				{ _continuous = continuous; }
bool 		ESP8266SoilMoistureSensor::continuous() 													{ return _continuous; }

// Calibration values: set the minimum and maximum value returned by your sensor
// This makes sure the lowest and highest values are consistently mapped to CP values
// Defaults 5 and 650
void 		ESP8266SoilMoistureSensor::setMinCalibration(int minCalibration) 	{	_minCalibration = minCalibration; }
int			ESP8266SoilMoistureSensor::minCalibration() 											{	return _minCalibration; }
void 		ESP8266SoilMoistureSensor::setMaxCalibration(int maxCalibration) 	{	_maxCalibration = maxCalibration; }
int			ESP8266SoilMoistureSensor::maxCalibration() 											{	return _maxCalibration; }

// Measurement unit; If set to true, read() returns values between 0-100
// If set to false (default), read90 returns CB value from 200-0
void		setMeasurePercentage(bool measurePercentage) {_measurePercentage = measurePercentage; }
bool		measurePercentage() { return _measurePercentage; }

